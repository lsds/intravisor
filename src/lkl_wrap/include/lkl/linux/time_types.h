/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_TIME_TYPES_H
#define _LKL_LINUX_TIME_TYPES_H

#include <lkl/linux/types.h>

struct __lkl__kernel_timespec {
	__lkl__kernel_time64_t       tv_sec;                 /* seconds */
	long long               tv_nsec;                /* nanoseconds */
};

struct __lkl__kernel_itimerspec {
	struct __lkl__kernel_timespec it_interval;    /* timer period */
	struct __lkl__kernel_timespec it_value;       /* timer expiration */
};

/*
 * legacy timeval structure, only embedded in structures that
 * traditionally used 'timeval' to pass time intervals (not absolute
 * times). Do not add new users. If user space fails to compile
 * here, this is probably because it is not y2038 safe and needs to
 * be changed to use another interface.
 */
#ifndef __kernel_old_timeval
struct __lkl__kernel_old_timeval {
	__lkl__kernel_long_t tv_sec;
	__lkl__kernel_long_t tv_usec;
};
#endif

struct __lkl__kernel_old_timespec {
	__lkl__kernel_old_time_t	tv_sec;		/* seconds */
	long			tv_nsec;	/* nanoseconds */
};

struct __lkl__kernel_old_itimerval {
	struct __lkl__kernel_old_timeval it_interval;/* timer interval */
	struct __lkl__kernel_old_timeval it_value;	/* current value */
};

struct __lkl__kernel_sock_timeval {
	__lkl__s64 tv_sec;
	__lkl__s64 tv_usec;
};

#endif /* _LKL_LINUX_TIME_TYPES_H */
