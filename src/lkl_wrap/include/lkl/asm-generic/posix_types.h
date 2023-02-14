/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_POSIX_TYPES_H
#define __LKL__ASM_GENERIC_POSIX_TYPES_H

#include <lkl/asm/bitsperlong.h>
/*
 * This file is generally used by user-level software, so you need to
 * be a little careful about namespace pollution etc.
 *
 * First the types that are often defined in different ways across
 * architectures, so that you can override them.
 */

#ifndef __lkl__kernel_long_t
typedef long		__lkl__kernel_long_t;
typedef unsigned long	__lkl__kernel_ulong_t;
#endif

#ifndef __lkl__kernel_ino_t
typedef __lkl__kernel_ulong_t __lkl__kernel_ino_t;
#endif

#ifndef __lkl__kernel_mode_t
typedef unsigned int	__lkl__kernel_mode_t;
#endif

#ifndef __lkl__kernel_pid_t
typedef int		__lkl__kernel_pid_t;
#endif

#ifndef __lkl__kernel_ipc_pid_t
typedef int		__lkl__kernel_ipc_pid_t;
#endif

#ifndef __lkl__kernel_uid_t
typedef unsigned int	__lkl__kernel_uid_t;
typedef unsigned int	__lkl__kernel_gid_t;
#endif

#ifndef __lkl__kernel_suseconds_t
typedef __lkl__kernel_long_t		__lkl__kernel_suseconds_t;
#endif

#ifndef __lkl__kernel_daddr_t
typedef int		__lkl__kernel_daddr_t;
#endif

#ifndef __lkl__kernel_uid32_t
typedef unsigned int	__lkl__kernel_uid32_t;
typedef unsigned int	__lkl__kernel_gid32_t;
#endif

#ifndef __lkl__kernel_old_uid_t
typedef __lkl__kernel_uid_t	__lkl__kernel_old_uid_t;
typedef __lkl__kernel_gid_t	__lkl__kernel_old_gid_t;
#endif

#ifndef __lkl__kernel_old_dev_t
typedef unsigned int	__lkl__kernel_old_dev_t;
#endif

/*
 * Most 32 bit architectures use "unsigned int" lkl_size_t,
 * and all 64 bit architectures use "unsigned long" lkl_size_t.
 */
#ifndef __lkl__kernel_size_t
#if __LKL__BITS_PER_LONG != 64
typedef unsigned int	__lkl__kernel_size_t;
typedef int		__lkl__kernel_ssize_t;
typedef int		__lkl__kernel_ptrdiff_t;
#else
typedef __lkl__kernel_ulong_t __lkl__kernel_size_t;
typedef __lkl__kernel_long_t	__lkl__kernel_ssize_t;
typedef __lkl__kernel_long_t	__lkl__kernel_ptrdiff_t;
#endif
#endif

#ifndef __lkl__kernel_fsid_t
typedef struct {
	int	val[2];
} __lkl__kernel_fsid_t;
#endif

/*
 * anything below here should be completely generic
 */
typedef __lkl__kernel_long_t	__lkl__kernel_off_t;
typedef long long	__lkl__kernel_loff_t;
typedef __lkl__kernel_long_t	__lkl__kernel_time_t;
typedef __lkl__kernel_long_t	__lkl__kernel_clock_t;
typedef int		__lkl__kernel_timer_t;
typedef int		__lkl__kernel_clockid_t;
typedef char *		__lkl__kernel_caddr_t;
typedef unsigned short	__lkl__kernel_uid16_t;
typedef unsigned short	__lkl__kernel_gid16_t;

#endif /* __LKL__ASM_GENERIC_POSIX_TYPES_H */
