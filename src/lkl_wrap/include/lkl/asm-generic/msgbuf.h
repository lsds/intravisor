/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_MSGBUF_H
#define __LKL__ASM_GENERIC_MSGBUF_H

#include <lkl/asm/bitsperlong.h>
/*
 * generic msqid64_ds structure.
 *
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * msqid64_ds was originally meant to be architecture specific, but
 * everyone just ended up making identical copies without specific
 * optimizations, so we may just as well all use the same one.
 *
 * 64 bit architectures typically define a 64 bit __lkl__kernel_time_t,
 * so they do not need the first three padding words.
 * On big-endian systems, the padding is in the wrong place.
 *
 * Pad space is left for:
 * - 64-bit lkl_time_t to solve y2038 problem
 * - 2 miscellaneous 32-bit values
 */

struct lkl_msqid64_ds {
	struct lkl_ipc64_perm msg_perm;
	__lkl__kernel_time_t msg_stime;	/* last msgsnd time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long	__unused1;
#endif
	__lkl__kernel_time_t msg_rtime;	/* last msgrcv time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long	__unused2;
#endif
	__lkl__kernel_time_t msg_ctime;	/* last change time */
#if __LKL__BITS_PER_LONG != 64
	unsigned long	__unused3;
#endif
	__lkl__kernel_ulong_t msg_cbytes;	/* current number of bytes on queue */
	__lkl__kernel_ulong_t msg_qnum;	/* number of messages in queue */
	__lkl__kernel_ulong_t msg_qbytes;	/* max number of bytes on queue */
	__lkl__kernel_pid_t msg_lspid;	/* pid of last msgsnd */
	__lkl__kernel_pid_t msg_lrpid;	/* last receive pid */
	__lkl__kernel_ulong_t __unused4;
	__lkl__kernel_ulong_t __unused5;
};

#endif /* __LKL__ASM_GENERIC_MSGBUF_H */
