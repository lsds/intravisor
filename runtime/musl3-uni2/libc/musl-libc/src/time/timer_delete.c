#include <time.h>
#include <limits.h>
#include "pthread_impl.h"

int timer_delete(timer_t t)
{
#ifdef __CHERI_PURE_CAPABILITY__
	if(t.thread)
	{
		pthread_t td = t.ptr;
		a_store(&td->timer_id, td->timer_id);
		__syscall(SYS_tkill, td->tid, SIGTIMER);
		return 0;
	}
#else
	if ((intptr_t)t < 0) {
		pthread_t td = (void *)((uintptr_t)t << 1);
		a_store(&td->timer_id, td->timer_id | INT_MIN);
		__syscall(SYS_tkill, td->tid, SIGTIMER);
		return 0;
	}
#endif
#ifdef __CHERI_PURE_CAPABILITY__
	return __syscall(SYS_timer_delete, t.ptr);
#else
	return __syscall(SYS_timer_delete, t);
#endif
}
