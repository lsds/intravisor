#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include "syscall.h"

int socket(int domain, int type, int protocol)
{
#ifdef USE_HOST_NET
	int ret = wrap_socket(domain, type, protocol);
//	lkl_printf("%s %d %d\n", __func__, __LINE__, ret);
	return ret;
#else
//	lkl_printf("I shouldnt be there\n"); while(1);
	int s = __socketcall(socket, domain, type, protocol, 0, 0, 0);
	if ((s==-EINVAL || s==-EPROTONOSUPPORT)
	    && (type&(SOCK_CLOEXEC|SOCK_NONBLOCK))) {
		s = __socketcall(socket, domain,
			type & ~(SOCK_CLOEXEC|SOCK_NONBLOCK),
			protocol, 0, 0, 0);
		if (s < 0) return __syscall_ret(s);
		if (type & SOCK_CLOEXEC)
			__syscall(SYS_fcntl, s, F_SETFD, FD_CLOEXEC);
		if (type & SOCK_NONBLOCK)
			__syscall(SYS_fcntl, s, F_SETFL, O_NONBLOCK);
	}
	return __syscall_ret(s);
#endif
}
