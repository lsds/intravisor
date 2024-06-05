#define _BSD_SOURCE
#include <unistd.h>
#include <errno.h>

int brk(void *end)
{
	return __syscall_ret(-ENOMEM);
}
