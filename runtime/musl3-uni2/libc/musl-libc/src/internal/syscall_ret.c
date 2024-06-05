#include <errno.h>
#include "syscall.h"

#ifdef __CHERI_PURE_CAPABILITY__
intptr_t __syscall_ret(uintptr_t r)
#else
long __syscall_ret(unsigned long r)
#endif
{
	if ((unsigned long)r > -4096UL) {
		errno = -(int)(r);
		return -1;
	}
	return r;
}
