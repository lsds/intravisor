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
#include <asm/signal.h>

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

	return ret;
}

syscall_handler_t lkl_replace_syscall(int no, syscall_handler_t replacement)
{
	syscall_handler_t old;

	if (no < 0 || no >= __NR_syscalls)
		return NULL;

	old = syscall_table[no];
	syscall_table[no] = replacement;

	return old;
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
	if (pid < 0) {
		LKL_TRACE("kernel_thread() failed (pid=%i)\n", pid);
		return pid;
	}

	rcu_read_lock();
	*task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_read_unlock();

	host_task_id++;

	snprintf((*task)->comm, sizeof((*task)->comm), "host%d", host_task_id);

	LKL_TRACE("allocated (task=%p/%s) pid=%i\n", *task, (*task)->comm, pid);

	return 0;
}
static void exit_task(void)
{
	LKL_TRACE("enter\n");
	do_exit(0);
}

static void del_host_task(void *arg)
{
	struct task_struct *task = (struct task_struct *)arg;
	struct thread_info *ti = task_thread_info(task);

	LKL_TRACE("enter (task=%p/%s ti=%p)\n", task, task->comm, ti);

	if (lkl_cpu_get() < 0) {
		LKL_TRACE("could not get CPU\n");
		return;
	}

	switch_to_host_task(task);
	host_task_id--;
	set_ti_thread_flag(ti, TIF_SCHED_JB);
	set_ti_thread_flag(ti, TIF_NO_TERMINATION);

	lkl_ops->jmp_buf_set(&ti->sched_jb, exit_task);
}

struct lkl_tls_key *task_key;

/* Record the exit status after shutdown */
_Atomic(int) lkl_exit_status;

/* Record received signal after shutdown */
_Atomic(int) lkl_received_signal;

/* Use this to record an ongoing LKL shutdown */
_Atomic(bool) lkl_shutdown = false;

static struct task_struct *idle_host_task;

/* Returns the task_struct associated with the current lthread */
struct task_struct* lkl_get_current_task_struct(void)
{
	return lkl_ops->tls_get(task_key);
}

long lkl_syscall(long no, long *params)
{
	struct task_struct *task = host0;
	struct thread_info *ti;
	long ret;

	LKL_TRACE(
		"enter (no=%li current=%s host0->TIF host0->TIF_SIGPENDING=%i)\n",
		no, current->comm, test_tsk_thread_flag(task, TIF_HOST_THREAD),
		test_tsk_thread_flag(task, TIF_SIGPENDING));

	/**
	 * If there is an ongoing shutdown, we assume that the caller (the idle
	 * host task) already holds the CPU lock.
	 */
	if (lkl_shutdown) {

		/**
		 * Only permit the idle host task to issue system calls now, because
		 * it is invoking the shutdown sequence.
		 */
		if (current != idle_host_task) {
			LKL_TRACE(
				"Ignoring userspace syscall (current->comm=%s allowed=%s)\n",
				current->comm, idle_host_task->comm);
			return -ENOTSUPP;
		}

		ret = run_syscall(no, params);
		task_work_run();

		/*
		 * Do NOT send signals now. That mechanism relies on lkl_cpu_get/put
		 * which is disabled for shutdown.
		 * 
		 * Otherwise it would be like:
		 * 
		 * move_signals_to_task();
		 * send_current_signals(NULL);
		 */

		if (no == __NR_reboot) {
			thread_sched_jb();
		}

		LKL_TRACE("Shutdown syscall=%li done\n", no);
		return ret;
	}

	ret = lkl_cpu_get();
	if (ret < 0) {

		/*
		 * If we fail to get the LKL CPU here with an error, it likely indicates that we are
		 * shutting down, and we can no longer handle syscalls. Since this will never
		 * succeed, exit the current thread.
		 */

		task = lkl_get_current_task_struct();
		LKL_TRACE(
			"lkl_cpu_get() failed -- bailing (no=%li ret=%li task=%s host0=%p host_task_id=%i)\n",
			no, ret, task ? task->comm : "NULL", host0,
			host_task_id);

		lkl_ops->thread_exit();

		/* This should not return. */
		BUG();
		return ret;
	}

	if (lkl_ops->tls_get) {
		task = lkl_get_current_task_struct();
		if (!task) {
			ret = new_host_task(&task);
			if (ret) {
				LKL_TRACE("new_host_task() failed (ret=%li)\n", ret);
				goto out;
			}
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

	LKL_TRACE("switching to host task (no=%li task=%s current=%s)\n", no,
		  task->comm, current->comm);

	switch_to_host_task(task);

	LKL_TRACE("calling run_syscall() (no=%li task=%s current=%s)\n", no,
		  task->comm, current->comm);

	ret = run_syscall(no, params);

	LKL_TRACE("returned from run_syscall() (no=%li task=%s current=%s)\n",
		  no, task->comm, current->comm);

	/*
	 * Zero the return address so that nothing accidentally sees a stale value.
	 */
	ti->syscall_ret = 0;
	task_work_run();

	/*
	 * If we have created a new host task, make sure that it isn't on the
	 * scheduler queue when we return.  LKL expects that the only tasks driven
	 * by the Linux scheduler are kernel threads.  If releasing the CPU lock
	 * entirely and there are runnable tasks, `lkl_cpu_put` may run the
	 * scheduler and not release the lock.  The scheduler hands the CPU lock to
	 * the next running thread and `lkl_cpu_put` expects this to be the idle
	 * host task (which then releases the lock).  If host tasks are scheduled,
	 * they will be left running (and owning the CPU lock) and `lkl_cpu_put`
	 * will return without anything having released the lock.  LKL will then
	 * deadlock on the next system call.
	 */
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
	move_signals_to_task();

	if (no == __NR_reboot) {
		thread_sched_jb();
		return ret;
	}

out:
	/* run any signal handlers expected to run on this thread */
	send_current_signals(NULL);
	lkl_cpu_put();
	
	LKL_TRACE("done (no=%li task=%s current=%s ret=%i)\n", no,
		  task ? task->comm : "NULL", current->comm, ret);
	return ret;
}

extern _Atomic(int) lkl_exit_status;
extern _Atomic(int) lkl_received_signal;
extern _Atomic(bool) lkl_shutdown;

/* called from idle, don't failed, don't block */
void wakeup_idle_host_task(void)
{
	if (!need_resched() && idle_host_task)
		wake_up_process(idle_host_task);
}

static int idle_host_task_loop(void *unused)
{
	struct thread_info *ti = task_thread_info(current);

	LKL_TRACE("enter\n");

	snprintf(current->comm, sizeof(current->comm), "idle_host_task");
	set_thread_flag(TIF_HOST_THREAD);
	idle_host_task = current;

	for (;;) {
		/*
			any pending signals, capture them in lists per task
			so we can send them to the appropriate task later
		*/
		move_signals_to_task();

		lkl_cpu_put();

		/* 
		 * This mirrors some of the logic in __switch_to that transfers ownership of the CPU lock between
		 * threads when they are context switched. This is not quite the same code because in __switch_to it
		 * transfers the lock to the next LKL thread, whereas this code is transferring owership implicitly
		 * to whichever thread does a syscall again (or back to itself if the timer interrupt fires and
		 * successfully acquires the CPU lock).
		 */

		lkl_ops->sem_down(ti->sched_sem);

		if (lkl_shutdown) {

			/**
			 * Notify the host of the shutdown.
			 *
			 * Note that we are not releasing the CPU lock here, which allows
			 * the termination code to do syscalls directly.
			 */
			lkl_ops->terminate(lkl_exit_status, lkl_received_signal);

			lkl_ops->thread_exit();
			return 0;
		}

		schedule_tail(ti->prev_sched);
	}
}

int syscalls_init(void)
{
	LKL_TRACE("enter\n");

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

	LKL_TRACE("enter()\n");

	/* Clone host task with new pid */
	pid = kernel_thread(host_task_stub, NULL, CLONE_FLAGS & ~CLONE_THREAD);
	if (pid < 0) {
		LKL_TRACE("kernel_thread(host0) failed (pid=%i)\n", pid);
		return pid;
	}

	rcu_read_lock();
	task = find_task_by_pid_ns(pid, &init_pid_ns);
	rcu_read_unlock();

	switch_to_host_task(task);

	snprintf(task->comm, sizeof(task->comm), "host0");
	set_thread_flag(TIF_HOST_THREAD);

	LKL_TRACE("host0 allocated (task=%p/%s) pid=%i\n", task, task->comm, pid);

	host0 = current;

	return 0;
}

void syscalls_cleanup(void)
{
	LKL_TRACE("enter\n");

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
