#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>
#include <limits.h>

#include <string.h>
#include <stdio.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#include "time_impl.h"
#include <errno.h>

#include <time.h>
#include "syscall.h"

time_t time(time_t * t) {
	struct timeval tv;
	gettimeofday(&tv, NULL);

	return (time_t) tv.tv_sec;
}

#define TIMEVAL_TO_TIMESPEC(tv, ts) ( \
	(ts)->tv_sec = (tv)->tv_sec, \
	(ts)->tv_nsec = (tv)->tv_usec * 1000, \
	(void)0 )
#define TIMESPEC_TO_TIMEVAL(tv, ts) ( \
	(tv)->tv_sec = (ts)->tv_sec, \
	(tv)->tv_usec = (ts)->tv_nsec / 1000, \
	(void)0 )

int clock_gettime(clockid_t clock_id, struct timespec *tp) {
	struct timeval tv;
	int ret = host_gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, tp);
	return ret;
}

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp) {
	return host_nanosleep(rqtp, rmtp);
}

clock_t clock(void) {
	struct timespec ts;

	if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts))
		return -1;

	if(ts.tv_sec > LONG_MAX / 1000000 || ts.tv_nsec / 1000 > LONG_MAX - 1000000 * ts.tv_sec)
		return -1;

	return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

int gettimeofday(struct timeval *tv, struct timezone *tz) {
	if(!tv)
		return 0;

	return host_gettimeofday(tv, tz);
}
