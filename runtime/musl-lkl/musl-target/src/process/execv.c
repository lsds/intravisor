#include <unistd.h>

extern char **__environ;

int execv(const char *path, char *const argv[])
{
	lkl_printf("%s\n",__func__);while(1);
	return execve(path, argv, __environ);
}
