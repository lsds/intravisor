/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_SHMBUF_H
#define __LKL__ASM_GENERIC_SHMBUF_H

#include <lkl/asm/bitsperlong.h>

/*
 * The shmid64_ds structure for x86 architecture.
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * shmid64_ds was originally meant to be architecture specific, but
 * everyone just ended up making identical copies without specific
 * optimizations, so we may just as well all use the same one.
 *
 * 64 bit architectures typically define a 64 bit __lkl__kernel_time_t,
 * so they do not need the first two padding words.
 * On big-endian systems, the padding is in the wrong place.
 *
 *
 * Pad space is left for:
 * - 64-bit lkl_time_t to solve y2038 problem
 * - 2 miscellaneous 32-bit values
 */

struct lkl_shmid64_ds {
	struct lkl_ipc64_perm	shm_perm;	/* operation perms */
	lkl_size_t			shm_segsz;	/* size of segment (bytes) */
	__lkl__kernel_time_t		shm_atime;	/* last attach time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long		__unused1;
#endif
	__lkl__kernel_time_t		shm_dtime;	/* last detach time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long		__unused2;
#endif
	__lkl__kernel_time_t		shm_ctime;	/* last change time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long		__unused3;
#endif
	__lkl__kernel_pid_t		shm_cpid;	/* pid of creator */
	__lkl__kernel_pid_t		shm_lpid;	/* pid of last operator */
	__lkl__kernel_ulong_t	shm_nattch;	/* no. of current attaches */
	__lkl__kernel_ulong_t	__unused4;
	__lkl__kernel_ulong_t	__unused5;
};

struct lkl_shminfo64 {
	__lkl__kernel_ulong_t	shmmax;
	__lkl__kernel_ulong_t	shmmin;
	__lkl__kernel_ulong_t	shmmni;
	__lkl__kernel_ulong_t	shmseg;
	__lkl__kernel_ulong_t	shmall;
	__lkl__kernel_ulong_t	__unused1;
	__lkl__kernel_ulong_t	__unused2;
	__lkl__kernel_ulong_t	__unused3;
	__lkl__kernel_ulong_t	__unused4;
};

#endif /* __LKL__ASM_GENERIC_SHMBUF_H */
