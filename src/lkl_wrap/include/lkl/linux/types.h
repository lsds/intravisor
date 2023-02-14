/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_TYPES_H
#define _LKL_LINUX_TYPES_H

#include <lkl/asm/types.h>

#ifndef __ASSEMBLY__

#include <lkl/linux/posix_types.h>


/*
 * Below are truly Linux-specific types that should never collide with
 * any application/library that wants linux/types.h.
 */

#ifdef __CHECKER__
#define __lkl__bitwise__ __attribute__((bitwise))
#else
#define __lkl__bitwise__
#endif
#define __lkl__bitwise __lkl__bitwise__

typedef __lkl__u16 __lkl__bitwise __lkl__le16;
typedef __lkl__u16 __lkl__bitwise __lkl__be16;
typedef __lkl__u32 __lkl__bitwise __lkl__le32;
typedef __lkl__u32 __lkl__bitwise __lkl__be32;
typedef __lkl__u64 __lkl__bitwise __lkl__le64;
typedef __lkl__u64 __lkl__bitwise __lkl__be64;

typedef __lkl__u16 __lkl__bitwise __lkl__sum16;
typedef __lkl__u32 __lkl__bitwise __lkl__wsum;

/*
 * aligned_u64 should be used in defining kernel<->userspace ABIs to avoid
 * common 32/64-bit compat problems.
 * 64-bit values align to 4-byte boundaries on x86_32 (and possibly other
 * architectures) and to 8-byte boundaries on 64-bit architectures.  The new
 * aligned_64 type enforces 8-byte alignment so that structs containing
 * aligned_64 values have the same alignment on 32-bit and 64-bit architectures.
 * No conversions are necessary between 32-bit user-space and a 64-bit kernel.
 */
#define __lkl__aligned_u64 __lkl__u64 __attribute__((aligned(8)))
#define __lkl__aligned_be64 __lkl__be64 __attribute__((aligned(8)))
#define __lkl__aligned_le64 __lkl__le64 __attribute__((aligned(8)))

#ifdef __CHECK_POLL
typedef unsigned __lkl__bitwise __lkl__poll_t;
#else
typedef unsigned __lkl__poll_t;
#endif

#endif /*  __ASSEMBLY__ */
#endif /* _LKL_LINUX_TYPES_H */
