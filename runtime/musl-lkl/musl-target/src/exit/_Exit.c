#include <stdlib.h>
#include "syscall.h"

_Noreturn void _Exit(int ec)
{
#if 0
	__syscall(SYS_exit_group, ec);
	for (;;) __syscall(SYS_exit, ec);
#else
	printf("Warning: _Exit is replaced by wrap_thread_exit()\n");
	extern void wrap_thread_exit();
	wrap_thread_exit();
#endif
}
