/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_KERNEL_H
#define _LKL_LINUX_KERNEL_H

#include <lkl/linux/sysinfo.h>

/*
 * 'kernel.h' contains some often-used function prototypes etc
 */
#define __LKL__ALIGN_KERNEL(x, a)		__LKL__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __LKL__ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))

#define __LKL__KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#endif /* _LKL_LINUX_KERNEL_H */
