#include "pthread_impl.h"

void *__tls_get_addr(tls_mod_off_t *v)
{
	pthread_t self = __pthread_self();
#ifdef __CHERI_PURE_CAPABILITY__
	return __builtin_cheri_bounds_set((void *)(self->dtv[v[0]] + v[1]), v[2]);
#else
	return (void *)(self->dtv[v[0]] + v[1]);
#endif
}
