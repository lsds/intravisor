/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_RESOURCE_H
#define _LKL_LINUX_RESOURCE_H

#include <lkl/linux/time.h>
#include <lkl/linux/types.h>

/*
 * Resource control/accounting header file for linux
 */

/*
 * Definition of struct lkl_rusage taken from BSD 4.3 Reno
 * 
 * We don't support all of these yet, but we might as well have them....
 * Otherwise, each time we add new items, programs which depend on this
 * structure will lose.  This reduces the chances of that happening.
 */
#define	LKL_RUSAGE_SELF	0
#define	LKL_RUSAGE_CHILDREN	(-1)
#define LKL_RUSAGE_BOTH	(-2)		/* sys_wait4() uses this */
#define	LKL_RUSAGE_THREAD	1		/* only the calling thread */

struct	lkl_rusage {
	struct lkl_timeval ru_utime;	/* user time used */
	struct lkl_timeval ru_stime;	/* system time used */
	__lkl__kernel_long_t	ru_maxrss;	/* maximum resident set size */
	__lkl__kernel_long_t	ru_ixrss;	/* integral shared memory size */
	__lkl__kernel_long_t	ru_idrss;	/* integral unshared data size */
	__lkl__kernel_long_t	ru_isrss;	/* integral unshared stack size */
	__lkl__kernel_long_t	ru_minflt;	/* page reclaims */
	__lkl__kernel_long_t	ru_majflt;	/* page faults */
	__lkl__kernel_long_t	ru_nswap;	/* swaps */
	__lkl__kernel_long_t	ru_inblock;	/* block input operations */
	__lkl__kernel_long_t	ru_oublock;	/* block output operations */
	__lkl__kernel_long_t	ru_msgsnd;	/* messages sent */
	__lkl__kernel_long_t	ru_msgrcv;	/* messages received */
	__lkl__kernel_long_t	ru_nsignals;	/* signals received */
	__lkl__kernel_long_t	ru_nvcsw;	/* voluntary context switches */
	__lkl__kernel_long_t	ru_nivcsw;	/* involuntary " */
};

struct lkl_rlimit {
	__lkl__kernel_ulong_t	rlim_cur;
	__lkl__kernel_ulong_t	rlim_max;
};

#define LKL_RLIM64_INFINITY		(~0ULL)

struct lkl_rlimit64 {
	__lkl__u64 rlim_cur;
	__lkl__u64 rlim_max;
};

#define	LKL_PRIO_MIN	(-20)
#define	LKL_PRIO_MAX	20

#define	LKL_PRIO_PROCESS	0
#define	LKL_PRIO_PGRP	1
#define	LKL_PRIO_USER	2

/*
 * Limit the stack by to some sane default: root can always
 * increase this limit if needed..  8MB seems reasonable.
 */
#define _LKL_STK_LIM	(8*1024*1024)

/*
 * GPG2 wants 64kB of mlocked memory, to make sure pass phrases
 * and other sensitive information are never written to disk.
 */
#define LKL_MLOCK_LIMIT	((PAGE_SIZE > 64*1024) ? PAGE_SIZE : 64*1024)

/*
 * Due to binary compatibility, the actual resource numbers
 * may be different for different linux versions..
 */
#include <lkl/asm/resource.h>


#endif /* _LKL_LINUX_RESOURCE_H */
