#include <sys/prctl.h>
#include <stdarg.h>
#include "cheri_helpers.h"
#include "syscall.h"

int prctl(int op, ...)
{
	uintptr_t x[4];
	int i;
	va_list ap;
	va_start(ap, op);
	for (i=0; i<4; i++) x[i] = VA_ARG_IF_IN_BOUNDS(ap, uintptr_t);
	va_end(ap);
	return syscall(SYS_prctl, op, x[0], x[1], x[2], x[3]);
}
