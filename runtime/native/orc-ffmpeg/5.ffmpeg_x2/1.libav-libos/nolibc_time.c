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

#define LEAPOCH (946684800LL + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

const char utc[] = "UTC";

int secs_to_tm(long long t, struct tm *tm)
{
    long long days, secs, years;
    int remdays, remsecs, remyears;
    int qc_cycles, c_cycles, q_cycles;
    int months;
    int wday, yday, leap;
    static const char days_in_month[] = {31,30,31,30,31,31,30,31,30,31,31,29};

    /* Reject time_t values whose year would overflow int */
    if (t < INT_MIN * 31622400LL || t > INT_MAX * 31622400LL)
	return -1;

    secs = t - LEAPOCH;
    days = secs / 86400;
    remsecs = secs % 86400;
    if (remsecs < 0) {
	remsecs += 86400;
	days--;
    }

    wday = (3+days)%7;
    if (wday < 0) wday += 7;

    qc_cycles = days / DAYS_PER_400Y;
    remdays = days % DAYS_PER_400Y;
    if (remdays < 0) {
	remdays += DAYS_PER_400Y;
	qc_cycles--;
    }

    c_cycles = remdays / DAYS_PER_100Y;
    if (c_cycles == 4) c_cycles--;
    remdays -= c_cycles * DAYS_PER_100Y;

    q_cycles = remdays / DAYS_PER_4Y;
    if (q_cycles == 25) q_cycles--;
    remdays -= q_cycles * DAYS_PER_4Y;

    remyears = remdays / 365;
    if (remyears == 4) remyears--;
    remdays -= remyears * 365;

    leap = !remyears && (q_cycles || !c_cycles);
    yday = remdays + 31 + 28 + leap;
    if (yday >= 365+leap) yday -= 365+leap;

    years = remyears + 4*q_cycles + 100*c_cycles + 400LL*qc_cycles;

    for (months=0; days_in_month[months] <= remdays; months++)
	remdays -= days_in_month[months];

    if (months >= 10) {
	months -= 12;
	years++;
    }

    if (years+100 > INT_MAX || years+100 < INT_MIN)
	return -1;

    tm->tm_year = years + 100;
    tm->tm_mon = months + 2;
    tm->tm_mday = remdays + 1;
    tm->tm_wday = wday;
    tm->tm_yday = yday;

    tm->tm_hour = remsecs / 3600;
    tm->tm_min = remsecs / 60 % 60;
    tm->tm_sec = remsecs % 60;

    return 0;
}


struct tm *gmtime_r(const time_t *restrict t, struct tm *restrict tm)
{
    if (secs_to_tm(*t, tm) < 0) {
	errno = EOVERFLOW;
	return 0;
    }
    tm->tm_isdst = 0;
    tm->__tm_gmtoff = 0;
    tm->__tm_zone = utc;
    return tm;
}

#include <time.h>
#include "syscall.h"

time_t time(time_t *t)
{
#if 0
    struct timespec ts;
    __clock_gettime(CLOCK_REALTIME, &ts);
    if (t) *t = ts.tv_sec;
    return ts.tv_sec;
#else
    printf("not implemened %s\n", __func__);
#endif
}


struct tm *localtime_r(const time_t *restrict t, struct tm *restrict tm)
{
    /* Reject time_t values whose year would overflow int because
     * __secs_to_zone cannot safely handle them. */
    if (*t < INT_MIN * 31622400LL || *t > INT_MAX * 31622400LL) {
	errno = EOVERFLOW;
	return 0;
    }
    secs_to_zone(*t, 0, &tm->tm_isdst, &tm->__tm_gmtoff, 0, &tm->__tm_zone);
    if (secs_to_tm((long long)*t + tm->__tm_gmtoff, tm) < 0) {
	errno = EOVERFLOW;
	return 0;
    }
    return tm;
}

time_t mktime(struct tm *tm)
{
    struct tm new;
    long opp;
    long long t = tm_to_secs(tm);

    secs_to_zone(t, 1, &new.tm_isdst, &new.__tm_gmtoff, &opp, &new.__tm_zone);

    if (tm->tm_isdst>=0 && new.tm_isdst!=tm->tm_isdst)
	t -= opp - new.__tm_gmtoff;

    t -= new.__tm_gmtoff;
    if ((time_t)t != t) goto error;

    secs_to_zone(t, 0, &new.tm_isdst, &new.__tm_gmtoff, &opp, &new.__tm_zone);

    if (secs_to_tm(t + new.__tm_gmtoff, &new) < 0) goto error;

    *tm = new;
    return t;

error:
    errno = EOVERFLOW;
    return -1;
}

long long tm_to_secs(const struct tm *tm)
{
    int is_leap;
    long long year = tm->tm_year;
    int month = tm->tm_mon;
    if (month >= 12 || month < 0) {
	int adj = month / 12;
	month %= 12;
	if (month < 0) {
	    adj--;
	    month += 12;
	}
	year += adj;
    }
    long long t = year_to_secs(year, &is_leap);
    t += month_to_secs(month, is_leap);
    t += 86400LL * (tm->tm_mday-1);
    t += 3600LL * tm->tm_hour;
    t += 60LL * tm->tm_min;
    t += tm->tm_sec;
    return t;
}

long long year_to_secs(long long year, int *is_leap)
{
    if (year-2ULL <= 136) {
	int y = year;
	int leaps = (y-68)>>2;
	if (!((y-68)&3)) {
	    leaps--;
	    if (is_leap) *is_leap = 1;
	} else if (is_leap) *is_leap = 0;
	return 31536000*(y-70) + 86400*leaps;
    }

    int cycles, centuries, leaps, rem;

    if (!is_leap) is_leap = &(int){0};
    cycles = (year-100) / 400;
    rem = (year-100) % 400;
    if (rem < 0) {
	cycles--;
	rem += 400;
    }
    if (!rem) {
	*is_leap = 1;
	centuries = 0;
	leaps = 0;
    } else {
	if (rem >= 200) {
	    if (rem >= 300) centuries = 3, rem -= 300;
	    else centuries = 2, rem -= 200;
	} else {
	    if (rem >= 100) centuries = 1, rem -= 100;
	    else centuries = 0;
	}
	if (!rem) {
	    *is_leap = 0;
	    leaps = 0;
	} else {
	    leaps = rem / 4U;
	    rem %= 4U;
	    *is_leap = !rem;
	}
    }

    leaps += 97*cycles + 24*centuries - *is_leap;

    return (year-100) * 31536000LL + leaps * 86400LL + 946684800 + 86400;
}

int month_to_secs(int month, int is_leap)
{
    static const int secs_through_month[] = {
	0, 31*86400, 59*86400, 90*86400,
	120*86400, 151*86400, 181*86400, 212*86400,
	243*86400, 273*86400, 304*86400, 334*86400 };
    int t = secs_through_month[month];
    if (is_leap && month >= 2) t+=86400;
    return t;
}


void secs_to_zone(long long t, int local, int *isdst, long *offset, long *oppoff, const char **zonename)
{
#if 1
    printf("not implemented %s\n", __func__);
#else
    LOCK(lock);

    do_tzset();

    if (zi) {
	size_t alt, i = scan_trans(t, local, &alt);
	if (i != -1) {
	    *isdst = types[6*i+4];
	    *offset = (int32_t)zi_read32(types+6*i);
	    *zonename = (const char *)abbrevs + types[6*i+5];
	    if (oppoff) *oppoff = (int32_t)zi_read32(types+6*alt);
	    UNLOCK(lock);
	    return;
	}
    }

    if (!__daylight) goto std;

    /* FIXME: may be broken if DST changes right at year boundary?
     * Also, this could be more efficient.*/
    long long y = t / 31556952 + 70;
    while (__year_to_secs(y, 0) > t) y--;
    while (__year_to_secs(y+1, 0) < t) y++;

    long long t0 = rule_to_secs(r0, y);
    long long t1 = rule_to_secs(r1, y);

    if (!local) {
	t0 += __timezone;
	t1 += dst_off;
    }
    if (t0 < t1) {
	if (t >= t0 && t < t1) goto dst;
	goto std;
    } else {
	if (t >= t1 && t < t0) goto std;
	goto dst;
    }
std:
    *isdst = 0;
    *offset = -__timezone;
    if (oppoff) *oppoff = -dst_off;
    *zonename = __tzname[0];
    UNLOCK(lock);
    return;
dst:
    *isdst = 1;
    *offset = -dst_off;
    if (oppoff) *oppoff = -__timezone;
    *zonename = __tzname[1];
    UNLOCK(lock);
#endif
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
    printf("not implemented %s\n", __func__);
}