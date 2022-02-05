/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_SWAB_H
#define _LKL_ASM_GENERIC_SWAB_H

#include <lkl/asm/bitsperlong.h>

/*
 * 32 bit architectures typically (but not always) want to
 * set __LKL__SWAB_64_THRU_32__. In user space, this is only
 * valid if the compiler supports 64 bit data types.
 */

#if __LKL__BITS_PER_LONG == 32
#if defined(__GNUC__) && !defined(__STRICT_ANSI__) || defined(__LKL__KERNEL__)
#define __LKL__SWAB_64_THRU_32__
#endif
#endif

#endif /* _LKL_ASM_GENERIC_SWAB_H */
