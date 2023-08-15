#include <unistd.h>
#include "syscall.h"

ssize_t read(int fd, void *buf, size_t count)
{
	if(fd >=0 && fd <3) {
		  printf("requested imput from STDIO FDs\n");
		  return 0;
	}

#ifdef USE_HOST_NET
	if (fd < 1000)
		return wrap_read(fd, buf, count);
#endif

	return syscall_cp(SYS_read, fd, buf, count);
}
