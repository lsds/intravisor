// SPDX-License-Identifier: GPL-2.0
#include <asm/x86/cpu_device_id.h>
#include <asm/x86/cpufeature.h>
#include <asm/x86/intel-family.h>

#include <linux/cpu.h>
#include <linux/export.h>
#include <linux/slab.h>

struct cpuinfo_x86 boot_cpu_data = {0};
EXPORT_SYMBOL(boot_cpu_data);

u64 boot_cpu_xfeature_mask = 0;
EXPORT_SYMBOL(boot_cpu_xfeature_mask);

void kernel_fpu_begin(void);
void kernel_fpu_end(void);

bool irq_fpu_usable(void)
{
        return 1;
}
EXPORT_SYMBOL(irq_fpu_usable);

/**
 * x86_match_cpu - match current CPU again an array of x86_cpu_ids
 * @match: Pointer to array of x86_cpu_ids. Last entry terminated with
 *         {}.
 *
 * Return the entry if the current CPU matches the entries in the
 * passed x86_cpu_id match table. Otherwise NULL.  The match table
 * contains vendor (X86_VENDOR_*), family, model and feature bits or
 * respective wildcard entries.
 *
 * A typical table entry would be to match a specific CPU
 * { X86_VENDOR_INTEL, 6, 0x12 }
 * or to match a specific CPU feature
 * { X86_FEATURE_MATCH(X86_FEATURE_FOOBAR) }
 *
 * Fields can be wildcarded with %X86_VENDOR_ANY, %X86_FAMILY_ANY,
 * %X86_MODEL_ANY, %X86_FEATURE_ANY or 0 (except for vendor)
 *
 * Arrays used to match for this should also be declared using
 * MODULE_DEVICE_TABLE(x86cpu, ...)
 *
 * This always matches against the boot cpu, assuming models and features are
 * consistent over all CPUs.
 */
const struct x86_cpu_id *x86_match_cpu(const struct x86_cpu_id *match)
{
	const struct x86_cpu_id *m;
	struct cpuinfo_x86 *c = &boot_cpu_data;

	for (m = match; m->vendor | m->family | m->model | m->feature; m++) {
		if (m->vendor != X86_VENDOR_ANY && c->x86_vendor != m->vendor)
			continue;
		if (m->family != X86_FAMILY_ANY && c->x86 != m->family)
			continue;
		if (m->model != X86_MODEL_ANY && c->x86_model != m->model)
			continue;
		if (m->feature != X86_FEATURE_ANY && !cpu_has(c, m->feature))
			continue;
		return m;
	}
	return NULL;
}
EXPORT_SYMBOL(x86_match_cpu);

void kernel_fpu_begin(void) {}
EXPORT_SYMBOL(kernel_fpu_begin);
void kernel_fpu_end(void) {}
EXPORT_SYMBOL(kernel_fpu_end);


/*
 * Return whether the system supports a given xfeature.
 *
 * Also return the name of the (most advanced) feature that the caller requested:
 */
int cpu_has_xfeatures(u64 xfeatures_needed, const char **feature_name)
{
	return !(xfeatures_needed & ~boot_cpu_xfeature_mask);
}
EXPORT_SYMBOL_GPL(cpu_has_xfeatures);
