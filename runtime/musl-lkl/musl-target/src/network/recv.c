#include <sys/socket.h>

ssize_t recv(int fd, void *buf, size_t len, int flags)
{
#ifdef USE_HOST_NET
//	lkl_printf("%s %d %d\n", __func__, __LINE__, fd);
	if (fd < 1000)
		return wrap_recv(fd, buf, len, flags);
#endif

	return recvfrom(fd, buf, len, flags, 0, 0);
}
