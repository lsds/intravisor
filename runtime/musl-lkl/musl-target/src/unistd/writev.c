#include <sys/uio.h>
#include "syscall.h"

ssize_t writev(int fd, const struct iovec *iov, int count)
{
#ifdef USE_HOST_NET
//	printf("%s %d %d\n", __func__, __LINE__, fd);
	if(fd < 1000)
		return wrap_writev(fd, iov, count);
#endif
	return syscall_cp(SYS_writev, fd, iov, count);
}
