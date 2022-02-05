#include <sys/socket.h>
#include "syscall.h"

int accept(int fd, struct sockaddr *restrict addr, socklen_t *restrict len)
{
#ifdef USE_HOST_NET
//	lkl_printf("%s %d %d\n", __func__, __LINE__, fd);
	return wrap_accept(fd, addr, len);
#else
	return socketcall_cp(accept, fd, addr, len, 0, 0, 0);
#endif
}
