#include <linux/binfmts.h>
#include <linux/init.h>
#include <linux/init_task.h>
#include <linux/personality.h>
#include <linux/reboot.h>
#include <linux/fs.h>
#include <linux/start_kernel.h>
#include <linux/syscalls.h>
#include <linux/tick.h>
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

static char *cmd_line_ptr __initdata = boot_command_line;
static int cmd_line_len __initdata = COMMAND_LINE_SIZE;

static __init void cmd_line_append_va(const char *fmt, va_list ap)
{
	int ret;

	ret = vsnprintf(cmd_line_ptr, cmd_line_len, fmt, ap);

	if (ret > 0) {
		cmd_line_ptr += ret;
		cmd_line_len -= ret;
	}
}

static inline __init void cmd_line_append(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	cmd_line_append_va(fmt, ap);
	va_end(ap);
}

int __init lkl_start_kernel(struct lkl_host_operations *ops,
			const char *fmt, ...)
{
	int ret;

	lkl_ops = ops;

	va_list ap;

	cmd_line_append("%s ", CONFIG_BUILTIN_CMDLINE);

	va_start(ap, fmt);
	cmd_line_append_va(fmt, ap);
	va_end(ap);

	if (lkl_ops->virtio_devices)
		cmd_line_append("%s", lkl_ops->virtio_devices);

	memcpy(cmd_line, boot_command_line, COMMAND_LINE_SIZE);

	init_sem = lkl_ops->sem_alloc(0);
	if (!init_sem)
		return -ENOMEM;

	ret = lkl_cpu_init();
	if (ret)
		goto out_free_init_sem;

	ret = lkl_ops->thread_create(lkl_run_kernel, NULL);
	if (!ret) {
		ret = -ENOMEM;
		goto out_free_init_sem;
	}

	lkl_ops->sem_down(init_sem);
	lkl_ops->sem_free(init_sem);
	current_thread_info()->tid = lkl_ops->thread_self();
	lkl_cpu_change_owner(current_thread_info()->tid);

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
	if (err < 0)
		return err;

	is_running = false;

	lkl_cpu_wait_shutdown();

	syscalls_cleanup();
	threads_cleanup();
	/* Shutdown the clockevents source. */
	tick_suspend_local();
	free_mem();
	lkl_ops->thread_join(current_thread_info()->tid);

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

	ret = begin_new_exec(bprm);
	if (ret)
		return ret;
	set_personality(PER_LINUX);
	setup_new_exec(bprm);

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

	// Pad '/init' to make sure it's 8 bytes, otherwise KASan would
	// emit an error. The kernel's strncpy implementation attempts to read
	// 8 bytes at once and, thus, triggers KASan violation for the 6-byte
	// string.
	fd = sys_open("/init\0\0", O_CREAT, 0700);
	WARN_ON(fd < 0);
	sys_close(fd);

	register_binfmt(&lkl_run_init_binfmt);

	return 0;
}
late_initcall(fs_setup);