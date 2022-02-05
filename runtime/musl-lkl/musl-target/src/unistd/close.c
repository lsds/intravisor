#include <unistd.h>
#include <errno.h>
#include "syscall.h"

static int dummy(int fd)
{
	return fd;
}

weak_alias(dummy, __aio_close);

int close(int fd)
{
#ifdef USE_HOST_NET
	if(fd < 1000)
		return wrap_close(fd);
#endif

	fd = __aio_close(fd);
	int r = __syscall_cp(SYS_close, fd);
	if (r == -EINTR) r = 0;
	return __syscall_ret(r);
}
