#include <stdlib.h>
#include "syscall.h"

_Noreturn void _Exit(int ec)
{
	printf("EXIT IS CALLED\n"); while(1);
	__syscall(SYS_exit_group, ec);
	for (;;) __syscall(SYS_exit, ec);
}
