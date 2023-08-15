/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/* const.h: Macros for dealing with constants.  */

#ifndef _LKL_LINUX_CONST_H
#define _LKL_LINUX_CONST_H

/* Some constant macros are used in both assembler and
 * C code.  Therefore we cannot annotate them always with
 * 'UL' and other type specifiers unilaterally.  We
 * use the following macros to deal with this.
 *
 * Similarly, _LKL_AT() will cast an expression with a type in C, but
 * leave it unchanged in asm.
 */

#ifdef __ASSEMBLY__
#define _LKL_AC(X,Y)	X
#define _LKL_AT(T,X)	X
#else
#define __LKL__AC(X,Y)	(X##Y)
#define _LKL_AC(X,Y)	__LKL__AC(X,Y)
#define _LKL_AT(T,X)	((T)(X))
#endif

#define _LKL_UL(x)		(_LKL_AC(x, UL))
#define _LKL_ULL(x)		(_LKL_AC(x, ULL))

#define _LKL_BITUL(x)	(_LKL_UL(1) << (x))
#define _LKL_BITULL(x)	(_LKL_ULL(1) << (x))

#define __LKL__ALIGN_KERNEL(x, a)		__LKL__ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __LKL__ALIGN_KERNEL_MASK(x, mask)	(((x) + (mask)) & ~(mask))

#define __LKL__KERNEL_DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#endif /* _LKL_LINUX_CONST_H */
