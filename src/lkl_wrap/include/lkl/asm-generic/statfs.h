/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_GENERIC_STATFS_H
#define _LKL_GENERIC_STATFS_H

#include <lkl/linux/types.h>


/*
 * Most 64-bit platforms use 'long', while most 32-bit platforms use '__lkl__u32'.
 * Yes, they differ in signedness as well as size.
 * Special cases can override it for themselves -- except for S390x, which
 * is just a little too special for us. And MIPS, which I'm not touching
 * with a 10' pole.
 */
#ifndef __lkl__statfs_word
#if __LKL__BITS_PER_LONG == 64
#define __lkl__statfs_word __lkl__kernel_long_t
#else
#define __lkl__statfs_word __lkl__u32
#endif
#endif

struct lkl_statfs {
	__lkl__statfs_word f_type;
	__lkl__statfs_word f_bsize;
	__lkl__statfs_word f_blocks;
	__lkl__statfs_word f_bfree;
	__lkl__statfs_word f_bavail;
	__lkl__statfs_word f_files;
	__lkl__statfs_word f_ffree;
	__lkl__kernel_fsid_t f_fsid;
	__lkl__statfs_word f_namelen;
	__lkl__statfs_word f_frsize;
	__lkl__statfs_word f_flags;
	__lkl__statfs_word f_spare[4];
};

/*
 * ARM needs to avoid the 32-bit padding at the end, for consistency
 * between EABI and OABI 
 */
#ifndef LKL_ARCH_PACK_STATFS64
#define LKL_ARCH_PACK_STATFS64
#endif

struct lkl_statfs64 {
	__lkl__statfs_word f_type;
	__lkl__statfs_word f_bsize;
	__lkl__u64 f_blocks;
	__lkl__u64 f_bfree;
	__lkl__u64 f_bavail;
	__lkl__u64 f_files;
	__lkl__u64 f_ffree;
	__lkl__kernel_fsid_t f_fsid;
	__lkl__statfs_word f_namelen;
	__lkl__statfs_word f_frsize;
	__lkl__statfs_word f_flags;
	__lkl__statfs_word f_spare[4];
} LKL_ARCH_PACK_STATFS64;

/* 
 * IA64 and x86_64 need to avoid the 32-bit padding at the end,
 * to be compatible with the i386 ABI
 */
#ifndef LKL_ARCH_PACK_COMPAT_STATFS64
#define LKL_ARCH_PACK_COMPAT_STATFS64
#endif

struct lkl_compat_statfs64 {
	__lkl__u32 f_type;
	__lkl__u32 f_bsize;
	__lkl__u64 f_blocks;
	__lkl__u64 f_bfree;
	__lkl__u64 f_bavail;
	__lkl__u64 f_files;
	__lkl__u64 f_ffree;
	__lkl__kernel_fsid_t f_fsid;
	__lkl__u32 f_namelen;
	__lkl__u32 f_frsize;
	__lkl__u32 f_flags;
	__lkl__u32 f_spare[4];
} LKL_ARCH_PACK_COMPAT_STATFS64;

#endif /* _LKL_GENERIC_STATFS_H */
