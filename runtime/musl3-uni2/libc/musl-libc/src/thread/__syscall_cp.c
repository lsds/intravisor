#include "pthread_impl.h"
#include "syscall.h"

hidden intptr_t __syscall_cp_c();

static intptr_t sccp(long nr,
                 syscall_arg_t u, syscall_arg_t v, syscall_arg_t w,
                 syscall_arg_t x, syscall_arg_t y, syscall_arg_t z)
{
	return __syscall(nr, u, v, w, x, y, z);
}

weak_alias(sccp, __syscall_cp_c);

intptr_t (__syscall_cp)(long nr,
                    syscall_arg_t u, syscall_arg_t v, syscall_arg_t w,
                    syscall_arg_t x, syscall_arg_t y, syscall_arg_t z)
{
#ifndef INTRAVISOR
	return __syscall_cp_c(nr, u, v, w, x, y, z);
#else
	return __syscall(nr, u, v, w, x, y, z);
#endif
}
