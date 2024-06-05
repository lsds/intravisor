#include <time.h>
#include <limits.h>
#include "pthread_impl.h"

int timer_getoverrun(timer_t t)
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
#ifdef __CHERI_PURE_CAPABILITY__
	return syscall(SYS_timer_getoverrun, timer);
#else
	return syscall(SYS_timer_getoverrun, t);
#endif
}
