#include <sys/socket.h>
#include "syscall.h"

int bind(int fd, const struct sockaddr *addr, socklen_t len)
{
#ifdef USE_HOST_NET
//	lkl_printf("%s %d %d\n", __func__, __LINE__, fd);
	if(fd < 1000)
		return wrap_bind(fd, addr, len);
#else
	return socketcall(bind, fd, addr, len, 0, 0, 0);
#endif
}
