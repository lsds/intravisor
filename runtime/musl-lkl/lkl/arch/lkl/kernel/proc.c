
#include <asm/host_ops.h>
#include <linux/printk.h>
#include <linux/seq_file.h>
#include <linux/slab.h>

#ifdef CONFIG_PROC_FS

static char *cpuinfo_buf;
static unsigned int cpuinfo_len;

static int show_cpuinfo(struct seq_file *m, void *v)
{
	loff_t *spos = v;

	if (*spos >= cpuinfo_len)
		return 0;

	seq_putc(m, cpuinfo_buf[*spos]);

	return 0;
}

static void *c_start(struct seq_file *m, loff_t *pos)
{
	unsigned int buf_size;
	loff_t *spos;

	if (cpuinfo_buf == NULL) {

		/* How big is the buffer that we need? */
		cpuinfo_len = lkl_ops->cpuinfo_get(NULL, 0);
		buf_size = cpuinfo_len + 1;

		cpuinfo_buf = kmalloc(buf_size, GFP_KERNEL);
		if (cpuinfo_buf == NULL) {
			printk("cpuinfo: Not enough memory (%u bytes needed)\n", buf_size);
			return NULL;
		}

		/* Print cpuinfo to the buffer we have allocated */
		cpuinfo_len = lkl_ops->cpuinfo_get(cpuinfo_buf, buf_size);
	}

	spos = kmalloc(sizeof(loff_t), GFP_KERNEL);
	if (spos == NULL) {
		printk("cpuinfo: Not enough memory (%lu bytes needed)\n",
				sizeof(loff_t));
		return NULL;
	}

	if (*pos >= cpuinfo_len)
		return NULL;

	*spos = *pos;
	return spos;
}

static void *c_next(struct seq_file *m, void *v, loff_t *pos)
{
	loff_t *spos = v;

	*spos = *spos + 1;
	*pos = *spos;

	if (*spos >= cpuinfo_len)
		return NULL;

	return spos;
}

static void c_stop(struct seq_file *m, void *v)
{
	kfree(v);
}

const struct seq_operations cpuinfo_op = {
	.start	= c_start,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

#endif
