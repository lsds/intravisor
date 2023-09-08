#include <linux/moduleloader.h>
#include <linux/binfmts.h>
#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/personality.h>
#include <linux/reboot.h>
#include <linux/fs.h>
#include <linux/start_kernel.h>
#include <linux/syscalls.h>
#include <linux/platform_device.h>
#include <linux/tick.h>
#include <linux/virtio_console.h>
#include <asm/host_ops.h>
#include <asm/irq.h>
#include <asm/unistd.h>
#include <asm/syscalls.h>
#include <asm/cpu.h>

struct lkl_host_operations *lkl_ops;
static char cmd_line[COMMAND_LINE_SIZE];
static void *init_sem;
static int is_running;
void (*pm_power_off)(void) = NULL;
static unsigned long mem_size = 64 * 1024 * 1024;

#ifdef CONFIG_VIRTIO_CONSOLE
/* In the early stage of bootup when virtio console driver is not ready
 * then arch needs to provide a mechanism for printing the early console
 * messages. LKL will use the print (callback) registered during bootup.
 * Check description of print cb provided by host for detailed information
 */
static int lkl_early_put_chars(u32 vtermno, const char *buf, int count)
{
	if (lkl_ops->print)
		lkl_ops->print(buf, count);
	return 0;
}
#endif

/* Default DMA mask, this will be updated during initialization */
static u64 _lkl_dma_mask = 0xffffffffUL;

/* Assign memory for dma_mask. Overide weak interface defined
 * in the base platfrom driver */
void arch_setup_pdev_archdata(struct platform_device *pdev)
{
    pdev->dev.dma_mask = &_lkl_dma_mask;
}

long lkl_panic_blink(int state)
{
	lkl_ops->panic();
	return 0;
}

static int __init setup_mem_size(char *str)
{
	mem_size = memparse(str, NULL);
	return 0;
}
early_param("mem", setup_mem_size);

void __init setup_arch(char **cl)
{
	*cl = cmd_line;
	panic_blink = lkl_panic_blink;
	parse_early_param();
	bootmem_init(mem_size);
}

static void __init lkl_run_kernel(void *arg)
{
	threads_init();
	lkl_cpu_get();
	start_kernel();
}

int __init lkl_start_kernel(struct lkl_host_operations *ops,
			const char *fmt, ...)
{
	va_list ap;
	int ret;

	lkl_ops = ops;

	va_start(ap, fmt);
	ret = vsnprintf(boot_command_line, COMMAND_LINE_SIZE, fmt, ap);
	va_end(ap);

	if (ops->virtio_devices)
		strscpy(boot_command_line + ret, ops->virtio_devices,
			COMMAND_LINE_SIZE - ret);

	memcpy(cmd_line, boot_command_line, COMMAND_LINE_SIZE);

	init_sem = lkl_ops->sem_alloc(0);
	if (!init_sem)
		return -ENOMEM;

	ret = lkl_cpu_init();
	if (ret)
		goto out_free_init_sem;

#ifdef CONFIG_VIRTIO_CONSOLE
	virtio_cons_early_init(lkl_early_put_chars);
#endif

	ret = lkl_ops->thread_create(lkl_run_kernel, NULL);
	if (!ret) {
		ret = -ENOMEM;
		goto out_free_init_sem;
	}

	lkl_ops->sem_down(init_sem);
	lkl_ops->sem_free(init_sem);
	current_thread_info()->tid = lkl_ops->thread_self();
	lkl_cpu_change_owner(current_thread_info()->tid);

	/* Create parent host task for system calls with new pid */
	host0_init();

	lkl_cpu_put();
	is_running = 1;

	return 0;

out_free_init_sem:
	lkl_ops->sem_free(init_sem);

	return ret;
}

int lkl_is_running(void)
{
	return is_running;
}

void machine_halt(void)
{
	/* 
	 * All lkl_cpu_shutdown does is set cpu.shutdown_gate to MAX_THREADS
	 * as a flag. It does return and so machine_halt will return too.
	 */
	
	lkl_cpu_shutdown();
}

void machine_power_off(void)
{
	machine_halt();
}

void machine_restart(char *unused)
{
	machine_halt();
}

long lkl_sys_halt(void)
{
	long err;
	long params[6] = {LINUX_REBOOT_MAGIC1,
		LINUX_REBOOT_MAGIC2, LINUX_REBOOT_CMD_RESTART, };

	err = lkl_syscall(__NR_reboot, params);

	/*
		This code does get run even though machine_halt (above)
		is called.
	*/

	if (err < 0) {
		LKL_TRACE("sys_reboot failed (err=%i)\n", err);
		return err;
	}

	is_running = false;

	/**
	 * TODO: We may have cloned host threads that did not terminate,
	 * and prevent us from shutting down the LKL CPU.
	 *
	 * As a workaround, we do not shutdown all threads.
	 */

	//lkl_cpu_wait_shutdown();

	//syscalls_cleanup();

	// threads_cleanup();
	/* Shutdown the clockevents source. */
	//tick_suspend_local();
	//free_mem();
	//lkl_ops->thread_join(current_thread_info()->tid);

	return 0;
}


static int lkl_run_init(struct linux_binprm *bprm);

static struct linux_binfmt lkl_run_init_binfmt = {
	.module		= THIS_MODULE,
	.load_binary	= lkl_run_init,
};

static int lkl_run_init(struct linux_binprm *bprm)
{
	int ret;

	if (strcmp("/init", bprm->filename) != 0)
		return -EINVAL;

	ret = flush_old_exec(bprm);
	if (ret)
		return ret;
	set_personality(PER_LINUX);
	setup_new_exec(bprm);
	install_exec_creds(bprm);

	set_binfmt(&lkl_run_init_binfmt);

	init_pid_ns.child_reaper = 0;

	syscalls_init();

	lkl_ops->sem_up(init_sem);
	lkl_ops->thread_exit();

	return 0;
}


/* skip mounting the "real" rootfs. ramfs is good enough. */
static int __init fs_setup(void)
{
	int fd;

	fd = sys_open("/init", O_CREAT, 0700);
	WARN_ON(fd < 0);
	sys_close(fd);

	register_binfmt(&lkl_run_init_binfmt);

	return 0;
}
late_initcall(fs_setup);
