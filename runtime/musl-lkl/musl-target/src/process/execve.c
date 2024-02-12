#include <unistd.h>
#include "syscall.h"

int execve(const char *path, char *const argv[], char *const envp[])
{
	lkl_printf("%s\n",__func__);while(1);
	/* do we need to use environ if envp is null? */
	return syscall(SYS_execve, path, argv, envp);
}
