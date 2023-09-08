#include <linux/kallsyms.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <asm/ptrace.h>
#include <asm/host_ops.h>

#ifdef CONFIG_PRINTK
void dump_stack(void)
{
	unsigned long dummy;
	unsigned long *stack = &dummy;
	unsigned long addr;

	pr_info("Call Trace:\n");
	while (((long)stack & (THREAD_SIZE - 1)) != 0) {
		addr = *stack;
		if (__kernel_text_address(addr)) {
			pr_info("%p:  [<%08lx>] %pS", stack, addr,
				(void *)addr);
			pr_cont("\n");
		}
		stack++;
	}
	pr_info("\n");
}
#endif

void show_regs(struct pt_regs *regs)
{
}

