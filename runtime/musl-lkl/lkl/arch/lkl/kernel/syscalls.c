#include <linux/stat.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/jhash.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/net.h>
#include <linux/task_work.h>
#include <linux/syscalls.h>
#include <linux/kthread.h>
#include <linux/platform_device.h>
#include <asm/host_ops.h>
#include <asm/syscalls.h>
#include <asm/syscalls_32.h>
#include <asm/cpu.h>
#include <asm/sched.h>

static asmlinkage long sys_virtio_mmio_device_add(long base, long size,
						  unsigned int irq);

typedef long (*syscall_handler_t)(long arg1, ...);

#undef __SYSCALL
#define __SYSCALL(nr, sym) [nr] = (syscall_handler_t)sym,

syscall_handler_t syscall_table[__NR_syscalls] = {
	[0 ... __NR_syscalls - 1] =  (syscall_handler_t)sys_ni_syscall,
#include <asm/unistd.h>

#if __BITS_PER_LONG == 32
#include <asm/unistd_32.h>
#endif
};

static long run_syscall(long no, long *params)
{
	long ret;

	if (no < 0 || no >= __NR_syscalls)
		return -ENOSYS;

	ret = syscall_table[no](params[0], params[1], params[2], params[3],
				params[4], params[5]);

	task_work_run();

	return ret;
}


#define CLONE_FLAGS (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_THREAD |	\
		     CLONE_SIGHAND | SIGCHLD)

static int host_task_id;
static struct task_struct *host0;

static int new_host_task(struct task_struct **task)
{
	pid_t pid;

	switch_to_host_task(host0);

	pid = kernel_thread(host_task_stub, NULL, CLONE_FLAGS);
	if (pid < 0)
		return pid;

	rcu_read_lock();
	*task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_read_unlock();

	host_task_id++;

	snprintf((*task)->comm, sizeof((*task)->comm), "host%d", host_task_id);

	return 0;
}
static void exit_task(void)
{
	do_exit(0);
}

static void del_host_task(void *arg)
{
	struct task_struct *task = (struct task_struct *)arg;
	struct thread_info *ti = task_thread_info(task);

	if (lkl_cpu_get() < 0)
		return;

	switch_to_host_task(task);
	host_task_id--;
	set_ti_thread_flag(ti, TIF_SCHED_JB);
	set_ti_thread_flag(ti, TIF_NO_TERMINATION);
	lkl_ops->jmp_buf_set(&ti->sched_jb, exit_task);
}

static struct lkl_tls_key *task_key;

long lkl_syscall(long no, long *params)
{
	struct task_struct *task = host0;
	struct thread_info *ti;
	long ret;

extern void d_jump(void);
//d_jump();
//d_jump();

	ret = lkl_cpu_get();
	if (ret < 0)
		return ret;

	if (lkl_ops->tls_get) {
		task = lkl_ops->tls_get(task_key);
		if (!task) {
			ret = new_host_task(&task);
			if (ret)
				goto out;
			lkl_ops->tls_set(task_key, task);
		}
	}

	ti = task_thread_info(task);
	/*
	 * Store the return address so that it can be used in clone and similar
	 * calls.  In conventional arch ports, this would happen for free because
	 * the system call would capture the register state of the callee.
	 */
	ti->syscall_ret = __builtin_return_address(0);


	switch_to_host_task(task);

	ret = run_syscall(no, params);

	ti->syscall_ret = 0;
	task_work_run();

	if (ti->cloned_child)
	{
		struct task_struct *child = ti->cloned_child;
		struct thread_info *child_ti = task_thread_info(child);
		/*
		 * Calling `switch_to_host_task` will set the child task's
		 * `tid` field to the current host thread. This is normally
		 * what we want (binding the task to the thread that enters the
		 * syscall) but in this case it will result in two tasks
		 * pointing to the same thread.  This is normally fine because
		 * the field will be reset to the correct value on the next
		 * syscall. If; however, LKL shuts down before the child thread
		 * makes a syscall, the thread will be freed twice.  We need to
		 * make sure that `child->tid` has the correct value on return
		 * from this function, so we cache the (correct) current value
		 * and reset it at the end.
		 */
		lkl_thread_t child_tid = child_ti->tid;
		ti->cloned_child = NULL;
		/*
		 * We can't change the scheduler state of a task that isn't
		 * running, so switch to the task and then mark it as
		 * uninteruptible.
		 */
		switch_to_host_task(child);
		child->state = TASK_UNINTERRUPTIBLE;
		/*
		 * Reset the host thread associated with the task child before
		 * scheduling task. In current LKL, it is safe to do this after
		 * the switch call, but that will not be the case if LKL gains
		 * SMP kernel support.  Doing it this way around should ensure
		 * that the task cannot reenter the kernel until we switch away
		 * from it.
		 */
		child_ti->tid = child_tid;
		/* Switch back to the calling task before we return. */
		switch_to_host_task(task);
	}

	/* capture the signals pending while we still have the cpu lock */
//	move_signals_to_task();


	if (no == __NR_reboot) {
		thread_sched_jb();
		return ret;
	}

out:
//	send_current_signals(NULL);
	lkl_cpu_put();

	return ret;
}

static struct task_struct *idle_host_task;

/* called from idle, don't failed, don't block */
void wakeup_idle_host_task(void)
{
	if (!need_resched() && idle_host_task)
		wake_up_process(idle_host_task);
}

static int idle_host_task_loop(void *unused)
{
	struct thread_info *ti = task_thread_info(current);

	snprintf(current->comm, sizeof(current->comm), "idle_host_task");
	set_thread_flag(TIF_HOST_THREAD);
	idle_host_task = current;

	for (;;) {
//		move_signals_to_task();
		lkl_cpu_put();
		lkl_ops->sem_down(ti->sched_sem);
		if (idle_host_task == NULL) {
			lkl_ops->thread_exit();
			return 0;
		}
		schedule_tail(ti->prev_sched);
	}
}

int syscalls_init(void)
{
	snprintf(current->comm, sizeof(current->comm), "init");
	set_thread_flag(TIF_HOST_THREAD);
	host0 = current;

	if (lkl_ops->tls_alloc) {
		task_key = lkl_ops->tls_alloc(del_host_task);
		if (!task_key)
			return -1;
	}

	if (kernel_thread(idle_host_task_loop, NULL, CLONE_FLAGS) < 0) {
		if (lkl_ops->tls_free)
			lkl_ops->tls_free(task_key);
		return -1;
	}

	return 0;
}

/*
 * This function create a new kernel task, host0, which acts as the parent
 * for all dynamically created hosts tasks when handling syscalls. It does
 * not inherit the pid from init, and therefore can receive arbitrary
 * signals.
 *
 * The function must be called from a context that holds the LKL CPU lock.
 *
 */
int host0_init(void)
{
	pid_t pid;
	struct task_struct* task;

	/* Clone host task with new pid */
	pid = kernel_thread(host_task_stub, NULL, CLONE_FLAGS & ~CLONE_THREAD);
	if (pid < 0) {
		lkl_printf("kernel_thread(host0) failed (pid=%i)\n", pid);
		return pid;
	}

	rcu_read_lock();
	task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_read_unlock();

	switch_to_host_task(task);

	snprintf(task->comm, sizeof(task->comm), "host0");
	set_thread_flag(TIF_HOST_THREAD);

	lkl_printf("host0 allocated (task=%p/%s) pid=%i\n", task, task->comm, pid);

	host0 = current;

	return 0;
}


void syscalls_cleanup(void)
{
	if (idle_host_task) {
		struct thread_info *ti = task_thread_info(idle_host_task);

		idle_host_task = NULL;
		lkl_ops->sem_up(ti->sched_sem);
		lkl_ops->thread_join(ti->tid);
	}

	if (lkl_ops->tls_free)
		lkl_ops->tls_free(task_key);
}

SYSCALL_DEFINE3(virtio_mmio_device_add, long, base, long, size, unsigned int,
		irq)
{
	struct platform_device *pdev;
	int ret;

	struct resource res[] = {
		[0] = {
		       .start = base,
		       .end = base + size - 1,
		       .flags = IORESOURCE_MEM,
		       },
		[1] = {
		       .start = irq,
		       .end = irq,
		       .flags = IORESOURCE_IRQ,
		       },
	};

	pdev = platform_device_alloc("virtio-mmio", PLATFORM_DEVID_AUTO);
	if (!pdev) {
		dev_err(&pdev->dev, "%s: Unable to device alloc for virtio-mmio\n", __func__);
		return -ENOMEM;
	}

	ret = platform_device_add_resources(pdev, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(&pdev->dev, "%s: Unable to add resources for %s%d\n", __func__, pdev->name, pdev->id);
		goto exit_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "%s: Unable to add %s%d\n", __func__, pdev->name, pdev->id);
		goto exit_release_pdev;
	}

	return pdev->id;

exit_release_pdev:
	platform_device_del(pdev);
exit_device_put:
	platform_device_put(pdev);

	return ret;
}
