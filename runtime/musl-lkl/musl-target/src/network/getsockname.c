#include <sys/socket.h>
#include "syscall.h"

int getsockname(int fd, struct sockaddr *restrict addr, socklen_t *restrict len)
{
printf("%s %d\n", __func__, __LINE__);
	return socketcall(getsockname, fd, addr, len, 0, 0, 0);
}
