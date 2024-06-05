#include <time.h>
#include <limits.h>
#include "pthread_impl.h"

int timer_gettime(timer_t t, struct itimerspec *val)
{
#ifdef __CHERI_PURE_CAPABILITY__
	void *timer;
	if(t.thread)
	{
		pthread_t td = t.ptr;
		timer = (void *)td->timer_id;
	}
	else
	{
		timer = t.ptr;
	}
#else
	if ((intptr_t)t < 0) {
		pthread_t td = (void *)((uintptr_t)t << 1);
		t = (void *)(uintptr_t)(td->timer_id & INT_MAX);
	}
#endif

#ifdef SYS_timer_gettime64
	int r = -ENOSYS;
	if (sizeof(time_t) > 4)
		r = __syscall(SYS_timer_gettime64, t, val);
	if (SYS_timer_gettime == SYS_timer_gettime64 || r!=-ENOSYS)
		return __syscall_ret(r);
	long val32[4];
	r = __syscall(SYS_timer_gettime, t, val32);
	if (!r) {
		val->it_interval.tv_sec = val32[0];
		val->it_interval.tv_nsec = val32[1];
		val->it_value.tv_sec = val32[2];
		val->it_value.tv_nsec = val32[3];
	}
	return __syscall_ret(r);
#endif
#ifdef __CHERI_PURE_CAPABILITY__
	return syscall(SYS_timer_gettime, timer, val);
#else
	return syscall(SYS_timer_gettime, t, val);
#endif
}
