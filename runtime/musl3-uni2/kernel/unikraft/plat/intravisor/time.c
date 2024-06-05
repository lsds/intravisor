#include <string.h>
#include <uk/plat/time.h>
#include <uk/assert.h>
#include "hostcalls.h"

#define TIMER_INTVAL_NSEC    UKPLAT_TIME_TICK_NSEC
#define TIMER_SIGNUM         SIGALRM


/* POSIX definitions */

#define K_CLOCK_REALTIME       0
#define K_CLOCK_MONOTONIC      1

typedef int k_clockid_t;

typedef int k_timer_t;

struct k_timespec {
	long tv_sec;
	long tv_nsec;
};

struct timeval {
	long      tv_sec;     /* seconds */
	long tv_usec;    /* microseconds */
};

struct k_itimerspec {
	struct k_timespec it_interval;
	struct k_timespec it_value;
};


static k_timer_t timerid;

#define TIMEVAL_TO_TIMESPEC(tv, ts) ( \
	(ts)->tv_sec = (tv)->tv_sec, \
	(ts)->tv_nsec = (tv)->tv_usec * 1000, \
	(void)0 )
#define TIMESPEC_TO_TIMEVAL(tv, ts) ( \
	(tv)->tv_sec = (ts)->tv_sec, \
	(tv)->tv_usec = (ts)->tv_nsec / 1000, \
	(void)0 )

int sys_clock_gettime(k_clockid_t clock_id, struct k_timespec *tp) {
	struct timeval tv;
	int ret = host_gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, tp);
	return ret;
}


__nsec ukplat_monotonic_clock(void)
{
	struct k_timespec tp;
	__nsec ret;
	int rc;

	rc = sys_clock_gettime(K_CLOCK_MONOTONIC, &tp);
	if (unlikely(rc != 0))
		return 0;

	ret = ukarch_time_sec_to_nsec((__nsec) tp.tv_sec);
	ret += (__nsec) tp.tv_nsec;

	return ret;
}

__nsec ukplat_wall_clock(void)
{
	struct k_timespec tp;
	__nsec ret;
	int rc;

	rc = sys_clock_gettime(K_CLOCK_REALTIME, &tp);
	if (unlikely(rc != 0))
		return 0;

	ret = ukarch_time_sec_to_nsec((__nsec) tp.tv_sec);
	ret += (__nsec) tp.tv_nsec;

	return ret;
}

void ukplat_time_init(void)
{
	uk_pr_debug("not implemented %s\n", __func__);
}

void ukplat_time_fini(void)
{
	uk_pr_debug("not implemented %s\n", __func__);
}
