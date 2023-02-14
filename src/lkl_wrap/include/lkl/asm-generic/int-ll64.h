/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * asm-generic/int-ll64.h
 *
 * Integer declarations for architectures which use "long long"
 * for 64-bit types.
 */

#ifndef _LKL_ASM_GENERIC_INT_LL64_H
#define _LKL_ASM_GENERIC_INT_LL64_H

#include <lkl/asm/bitsperlong.h>

#ifndef __ASSEMBLY__
/*
 * __xx is ok: it doesn't pollute the POSIX namespace. Use these in the
 * header files exported to user space
 */

typedef __signed__ char __lkl__s8;
typedef unsigned char __lkl__u8;

typedef __signed__ short __lkl__s16;
typedef unsigned short __lkl__u16;

typedef __signed__ int __lkl__s32;
typedef unsigned int __lkl__u32;

#ifdef __GNUC__
__extension__ typedef __signed__ long long __lkl__s64;
__extension__ typedef unsigned long long __lkl__u64;
#else
typedef __signed__ long long __lkl__s64;
typedef unsigned long long __lkl__u64;
#endif

#endif /* __ASSEMBLY__ */


#endif /* _LKL_ASM_GENERIC_INT_LL64_H */
