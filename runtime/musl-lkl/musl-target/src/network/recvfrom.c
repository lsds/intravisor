#include <sys/socket.h>
#include "syscall.h"

ssize_t recvfrom(int fd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict alen)
{
#ifdef USE_HOST_NET
//	lkl_printf("%s %d %d\n", __func__, __LINE__, fd);
	if (fd < 1000)
		return wrap_recvfrom(fd, buf, len, flags, addr, alen);
#endif

	return socketcall_cp(recvfrom, fd, buf, len, flags, addr, alen);
}
