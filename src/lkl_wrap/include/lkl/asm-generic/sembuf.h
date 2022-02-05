/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_SEMBUF_H
#define __LKL__ASM_GENERIC_SEMBUF_H

#include <lkl/asm/bitsperlong.h>

/*
 * The semid64_ds structure for x86 architecture.
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * semid64_ds was originally meant to be architecture specific, but
 * everyone just ended up making identical copies without specific
 * optimizations, so we may just as well all use the same one.
 *
 * 64 bit architectures typically define a 64 bit __lkl__kernel_time_t,
 * so they do not need the first two padding words.
 * On big-endian systems, the padding is in the wrong place.
 *
 * Pad space is left for:
 * - 64-bit lkl_time_t to solve y2038 problem
 * - 2 miscellaneous 32-bit values
 */
struct lkl_semid64_ds {
	struct lkl_ipc64_perm sem_perm;	/* permissions .. see ipc.h */
	__lkl__kernel_time_t	sem_otime;	/* last semop time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long	__unused1;
#endif
	__lkl__kernel_time_t	sem_ctime;	/* last change time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long	__unused2;
#endif
	unsigned long	sem_nsems;	/* no. of semaphores in array */
	unsigned long	__unused3;
	unsigned long	__unused4;
};

#endif /* __LKL__ASM_GENERIC_SEMBUF_H */
