#include <errno.h>
#include "pthread_impl.h"

long carrie_errno;

int *__errno_location(void)
{
	return &carrie_errno; //FIXME
//	return &__pthread_self()->errno_val;
}

weak_alias(__errno_location, ___errno_location);
