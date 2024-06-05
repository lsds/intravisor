#define _GNU_SOURCE
#include "pthread_impl.h"
#include <sys/mman.h>

#ifdef __CHERI_PURE_CAPABILITY__

#define ROUND(x) (((x)+PAGE_SIZE-1)&-PAGE_SIZE)

#endif

static void dummy1(pthread_t t)
{
}
weak_alias(dummy1, __tl_sync);

static int munmap_wrap(void *addr, size_t len) {
//	if(addr) 
//		free(addr);
	return 0;
}

static int __pthread_timedjoin_np(pthread_t t, void **res, const struct timespec *at)
{
	int state, cs, r = 0;
	__pthread_testcancel();
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	if (cs == PTHREAD_CANCEL_ENABLE) __pthread_setcancelstate(cs, 0);
	while ((state = t->detach_state) && r != ETIMEDOUT && r != EINVAL) {
		if (state >= DT_DETACHED) a_crash();
		r = __timedwait_cp(&t->detach_state, state, CLOCK_REALTIME, at, 1);
	}
	__pthread_setcancelstate(cs, 0);
	if (r == ETIMEDOUT || r == EINVAL) return r;
	__tl_sync(t);
	if (res) *res = t->result;

#ifdef INTRAVISOR
	if (t->map_base) munmap_wrap(t->map_base, t->map_size);
#else
	if (t->map_base) __munmap(t->map_base, t->map_size);
#endif

#ifdef __CHERI_PURE_CAPABILITY__
	/*
	 * Free tsd afterwards as it stores structure required to access thread information.
	 */
	if (t->tsd && t->map_base)
#ifdef INTRAVISOR
		munmap_wrap((unsigned char *)(t->tsd) - libc.tls_size, ROUND(libc.tls_size +  __pthread_tsd_size));
#else
		__munmap((unsigned char *)(t->tsd) - libc.tls_size, ROUND(libc.tls_size +  __pthread_tsd_size));
#endif
#endif

	return 0;
}

int __pthread_join(pthread_t t, void **res)
{
	return __pthread_timedjoin_np(t, res, 0);
}

static int __pthread_tryjoin_np(pthread_t t, void **res)
{
	return t->detach_state==DT_JOINABLE ? EBUSY : __pthread_join(t, res);
}

weak_alias(__pthread_tryjoin_np, pthread_tryjoin_np);
weak_alias(__pthread_timedjoin_np, pthread_timedjoin_np);
weak_alias(__pthread_join, pthread_join);
