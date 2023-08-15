#include <sys/socket.h>
#include "syscall.h"

ssize_t sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *addr, socklen_t alen)
{
#ifdef USE_HOST_NET
printf("%s %d\n", __func__, __LINE__);
//	if(fd < 1000)
//		return wrap_sendto(fd, buf, len, flags, addr, alen);
#endif
	return socketcall_cp(sendto, fd, buf, len, flags, addr, alen);
}
