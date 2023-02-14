/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_TIME_H
#define _LKL_LINUX_TIME_H

#include <lkl/linux/types.h>


#ifndef _LKL_STRUCT_TIMESPEC
#define _LKL_STRUCT_TIMESPEC
struct lkl_timespec {
	__lkl__kernel_time_t	tv_sec;			/* seconds */
	long		tv_nsec;		/* nanoseconds */
};
#endif

struct lkl_timeval {
	__lkl__kernel_time_t		tv_sec;		/* seconds */
	__lkl__kernel_suseconds_t	tv_usec;	/* microseconds */
};

struct lkl_timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};


/*
 * Names of the interval timers, and structure
 * defining a timer setting:
 */
#define	LKL_ITIMER_REAL		0
#define	LKL_ITIMER_VIRTUAL		1
#define	LKL_ITIMER_PROF		2

struct lkl_itimerspec {
	struct lkl_timespec it_interval;	/* timer period */
	struct lkl_timespec it_value;	/* timer expiration */
};

struct lkl_itimerval {
	struct lkl_timeval it_interval;	/* timer interval */
	struct lkl_timeval it_value;	/* current value */
};

/*
 * legacy timeval structure, only embedded in structures that
 * traditionally used 'timeval' to pass time intervals (not absolute
 * times). Do not add new users. If user space fails to compile
 * here, this is probably because it is not y2038 safe and needs to
 * be changed to use another interface.
 */
struct __lkl__kernel_old_timeval {
	__lkl__kernel_long_t tv_sec;
	__lkl__kernel_long_t tv_usec;
};

/*
 * The IDs of the various system clocks (for POSIX.1b interval timers):
 */
#define LKL_CLOCK_REALTIME			0
#define LKL_CLOCK_MONOTONIC			1
#define LKL_CLOCK_PROCESS_CPUTIME_ID	2
#define LKL_CLOCK_THREAD_CPUTIME_ID		3
#define LKL_CLOCK_MONOTONIC_RAW		4
#define LKL_CLOCK_REALTIME_COARSE		5
#define LKL_CLOCK_MONOTONIC_COARSE		6
#define LKL_CLOCK_BOOTTIME			7
#define LKL_CLOCK_REALTIME_ALARM		8
#define LKL_CLOCK_BOOTTIME_ALARM		9
/*
 * The driver implementing this got removed. The clock ID is kept as a
 * place holder. Do not reuse!
 */
#define LKL_CLOCK_SGI_CYCLE			10
#define LKL_CLOCK_TAI			11

#define LKL_MAX_CLOCKS			16
#define LKL_CLOCKS_MASK			(LKL_CLOCK_REALTIME | LKL_CLOCK_MONOTONIC)
#define LKL_CLOCKS_MONO			LKL_CLOCK_MONOTONIC

/*
 * The various flags for setting POSIX.1b interval timers:
 */
#define LKL_TIMER_ABSTIME			0x01

#endif /* _LKL_LINUX_TIME_H */
