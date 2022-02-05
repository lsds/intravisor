#include <sys/eventfd.h>
#include <unistd.h>
#include <errno.h>
#include "syscall.h"

int eventfd(unsigned int count, int flags)
{
#ifdef USE_HOST_NET
//	lkl_printf("%s %d %d %d %d\n", __func__, __LINE__, count, flags);
	return wrap_eventfd(count, flags);
#endif
	int r = __syscall(SYS_eventfd2, count, flags);
#ifdef SYS_eventfd
	if (r==-ENOSYS && !flags) r = __syscall(SYS_eventfd, count);
#endif
	return __syscall_ret(r);
}

int eventfd_read(int fd, eventfd_t *value)
{
	return (sizeof(*value) == read(fd, value, sizeof(*value))) ? 0 : -1;
}

int eventfd_write(int fd, eventfd_t value)
{
	return (sizeof(value) == write(fd, &value, sizeof(value))) ? 0 : -1;
}
