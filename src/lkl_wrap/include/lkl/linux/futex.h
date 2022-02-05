/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_FUTEX_H
#define _LKL_LINUX_FUTEX_H


#include <lkl/linux/types.h>

/* Second argument to futex syscall */


#define LKL_FUTEX_WAIT		0
#define LKL_FUTEX_WAKE		1
#define LKL_FUTEX_FD		2
#define LKL_FUTEX_REQUEUE		3
#define LKL_FUTEX_CMP_REQUEUE	4
#define LKL_FUTEX_WAKE_OP		5
#define LKL_FUTEX_LOCK_PI		6
#define LKL_FUTEX_UNLOCK_PI		7
#define LKL_FUTEX_TRYLOCK_PI	8
#define LKL_FUTEX_WAIT_BITSET	9
#define LKL_FUTEX_WAKE_BITSET	10
#define LKL_FUTEX_WAIT_REQUEUE_PI	11
#define LKL_FUTEX_CMP_REQUEUE_PI	12

#define LKL_FUTEX_PRIVATE_FLAG	128
#define LKL_FUTEX_CLOCK_REALTIME	256
#define LKL_FUTEX_CMD_MASK		~(LKL_FUTEX_PRIVATE_FLAG | LKL_FUTEX_CLOCK_REALTIME)

#define LKL_FUTEX_WAIT_PRIVATE	(LKL_FUTEX_WAIT | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_WAKE_PRIVATE	(LKL_FUTEX_WAKE | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_REQUEUE_PRIVATE	(LKL_FUTEX_REQUEUE | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_CMP_REQUEUE_PRIVATE (LKL_FUTEX_CMP_REQUEUE | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_WAKE_OP_PRIVATE	(LKL_FUTEX_WAKE_OP | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_LOCK_PI_PRIVATE	(LKL_FUTEX_LOCK_PI | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_UNLOCK_PI_PRIVATE	(LKL_FUTEX_UNLOCK_PI | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_TRYLOCK_PI_PRIVATE (LKL_FUTEX_TRYLOCK_PI | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_WAIT_BITSET_PRIVATE	(LKL_FUTEX_WAIT_BITSET | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_WAKE_BITSET_PRIVATE	(LKL_FUTEX_WAKE_BITSET | LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_WAIT_REQUEUE_PI_PRIVATE	(LKL_FUTEX_WAIT_REQUEUE_PI | \
					 LKL_FUTEX_PRIVATE_FLAG)
#define LKL_FUTEX_CMP_REQUEUE_PI_PRIVATE	(LKL_FUTEX_CMP_REQUEUE_PI | \
					 LKL_FUTEX_PRIVATE_FLAG)

/*
 * Support for robust futexes: the kernel cleans up held futexes at
 * thread exit time.
 */

/*
 * Per-lock list entry - embedded in user-space locks, somewhere close
 * to the futex field. (Note: user-space uses a double-linked list to
 * achieve O(1) list add and remove, but the kernel only needs to know
 * about the forward link)
 *
 * NOTE: this structure is part of the syscall ABI, and must not be
 * changed.
 */
struct lkl_robust_list {
	struct lkl_robust_list *next;
};

/*
 * Per-thread list head:
 *
 * NOTE: this structure is part of the syscall ABI, and must only be
 * changed if the change is first communicated with the glibc folks.
 * (When an incompatible change is done, we'll increase the structure
 *  size, which glibc will detect)
 */
struct lkl_robust_list_head {
	/*
	 * The head of the list. Points back to itself if empty:
	 */
	struct lkl_robust_list list;

	/*
	 * This relative offset is set by user-space, it gives the kernel
	 * the relative position of the futex field to examine. This way
	 * we keep userspace flexible, to freely shape its data-structure,
	 * without hardcoding any particular offset into the kernel:
	 */
	long futex_offset;

	/*
	 * The death of the thread may race with userspace setting
	 * up a lock's links. So to handle this race, userspace first
	 * sets this field to the address of the to-be-taken lock,
	 * then does the lock acquire, and then adds itself to the
	 * list, and then clears this field. Hence the kernel will
	 * always have full knowledge of all locks that the thread
	 * _might_ have taken. We check the owner TID in any case,
	 * so only truly owned locks will be handled.
	 */
	struct lkl_robust_list *list_op_pending;
};

/*
 * Are there any waiters for this robust futex:
 */
#define LKL_FUTEX_WAITERS		0x80000000

/*
 * The kernel signals via this bit that a thread holding a futex
 * has exited without unlocking the futex. The kernel also does
 * a LKL_FUTEX_WAKE on such futexes, after setting the bit, to wake
 * up any possible waiters:
 */
#define LKL_FUTEX_OWNER_DIED	0x40000000

/*
 * The rest of the robust-futex field is for the TID:
 */
#define LKL_FUTEX_TID_MASK		0x3fffffff

/*
 * This limit protects against a deliberately circular list.
 * (Not worth introducing an rlimit for it)
 */
#define LKL_ROBUST_LIST_LIMIT	2048

/*
 * bitset with all bits set for the FUTEX_xxx_BITSET OPs to request a
 * match of any bit.
 */
#define LKL_FUTEX_BITSET_MATCH_ANY	0xffffffff


#define LKL_FUTEX_OP_SET		0	/* *(int *)UADDR2 = OPARG; */
#define LKL_FUTEX_OP_ADD		1	/* *(int *)UADDR2 += OPARG; */
#define LKL_FUTEX_OP_OR		2	/* *(int *)UADDR2 |= OPARG; */
#define LKL_FUTEX_OP_ANDN		3	/* *(int *)UADDR2 &= ~OPARG; */
#define LKL_FUTEX_OP_XOR		4	/* *(int *)UADDR2 ^= OPARG; */

#define LKL_FUTEX_OP_OPARG_SHIFT	8	/* Use (1 << OPARG) instead of OPARG.  */

#define LKL_FUTEX_OP_CMP_EQ		0	/* if (oldval == CMPARG) wake */
#define LKL_FUTEX_OP_CMP_NE		1	/* if (oldval != CMPARG) wake */
#define LKL_FUTEX_OP_CMP_LT		2	/* if (oldval < CMPARG) wake */
#define LKL_FUTEX_OP_CMP_LE		3	/* if (oldval <= CMPARG) wake */
#define LKL_FUTEX_OP_CMP_GT		4	/* if (oldval > CMPARG) wake */
#define LKL_FUTEX_OP_CMP_GE		5	/* if (oldval >= CMPARG) wake */

/* LKL_FUTEX_WAKE_OP will perform atomically
   int oldval = *(int *)UADDR2;
   *(int *)UADDR2 = oldval OP OPARG;
   if (oldval CMP CMPARG)
     wake UADDR2;  */

#define LKL_FUTEX_OP(op, oparg, cmp, cmparg) \
  (((op & 0xf) << 28) | ((cmp & 0xf) << 24)		\
   | ((oparg & 0xfff) << 12) | (cmparg & 0xfff))

#endif /* _LKL_LINUX_FUTEX_H */
