#include <unistd.h>
#include "syscall.h"


ssize_t write(int fd, const void *buf, size_t count)
{
	if(fd >= 0 && fd < 3) {
		char *tbuf = (char *) buf;
		tbuf[count]='\0';
		printf("%s", buf);
		return count;
	}
	
#ifdef USE_HOST_NET
	if (fd < 1000)
		return wrap_write(fd, buf, count);
#endif

	return syscall_cp(SYS_write, fd, buf, count);
}
