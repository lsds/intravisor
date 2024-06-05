#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "syscall.h"

char *getcwd(char *buf, size_t size)
{
	char *tmp = NULL;
	if (!buf) {
		size = size == 0 ? PATH_MAX : size;
		tmp = malloc(size);
		buf = tmp;
		if (!tmp)
			return 0;
	} else if (!size) {
		errno = EINVAL;
		return 0;
	}
	long ret = syscall(SYS_getcwd, buf, size);
	if (ret < 0) {
		if (buf == tmp)
			free(tmp);
		return 0;
	}
	if (ret == 0 || buf[0] != '/') {
		if (buf == tmp)
			free(tmp);
		errno = ENOENT;
		return 0;
	}
	return buf;
}
