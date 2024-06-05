#include "pthread_impl.h"

int pthread_attr_setguardsize(pthread_attr_t *a, size_t size)
{
#ifdef __CHERI_PURE_CAPABILITY__
	a->_a_guardsize = 0;
	return size ? EINVAL : 0;
#else
	if (size > SIZE_MAX/8) return EINVAL;
	a->_a_guardsize = size;
	return 0;
#endif
}
