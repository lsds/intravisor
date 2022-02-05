#include <sys/socket.h>
#include "syscall.h"

int connect(int fd, const struct sockaddr *addr, socklen_t len)
{
printf("%s %d\n", __func__, __LINE__);
	return socketcall_cp(connect, fd, addr, len, 0, 0, 0);
}
