#define _BSD_SOURCE
#include <unistd.h>
#include "syscall.h"
#include <stdarg.h>
#include "cheri_helpers.h"

#undef syscall

intptr_t syscall(long n, ...)
{
	va_list ap;
	syscall_arg_t a,b,c,d,e,f;
	va_start(ap, n);
	a=VA_ARG_IF_IN_BOUNDS(ap, syscall_arg_t);
	b=VA_ARG_IF_IN_BOUNDS(ap, syscall_arg_t);
	c=VA_ARG_IF_IN_BOUNDS(ap, syscall_arg_t);
	d=VA_ARG_IF_IN_BOUNDS(ap, syscall_arg_t);
	e=VA_ARG_IF_IN_BOUNDS(ap, syscall_arg_t);
	f=VA_ARG_IF_IN_BOUNDS(ap, syscall_arg_t);
	va_end(ap);
	return __syscall_ret(__syscall(n,a,b,c,d,e,f));
}
