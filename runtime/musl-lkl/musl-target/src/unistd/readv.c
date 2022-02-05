#include <sys/uio.h>
#include "syscall.h"

ssize_t readv(int fd, const struct iovec *iov, int count)
{
#ifdef USE_HOST_NET
	printf("%s %d %d\n", __func__, __LINE__, fd);
#endif

	return syscall_cp(SYS_readv, fd, iov, count);
}
