#define _GNU_SOURCE
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <stdint.h>
#include "cheri_helpers.h"
#include "syscall.h"

int fcntl(int fd, int cmd, ...)
{

	/* some arguments should be ints, some should be pointers - this is
	 * dependent on the cmd */
	switch (cmd) {
		case F_DUPFD:
		case F_DUPFD_CLOEXEC:
		case F_SETFD:
		case F_SETFL:
		case F_NOTIFY:
		case F_SETSIG:
		case F_SETOWN:
		case F_SETPIPE_SZ:
		case F_ADD_SEALS:
		case F_GET_RW_HINT:
		case F_SET_RW_HINT:
		case F_GET_FILE_RW_HINT:
		case F_SET_FILE_RW_HINT:
		case F_SETLEASE:
		{
			va_list ap;
			va_start(ap, cmd);
			int arg = va_arg(ap, int);
			va_end(ap);

			if (cmd == F_SETFL) arg |= O_LARGEFILE;
			if (cmd == F_DUPFD_CLOEXEC) {
				int ret = __syscall(SYS_fcntl, fd, F_DUPFD_CLOEXEC, arg);
				if (ret != -EINVAL) {
					if (ret >= 0)
						__syscall(SYS_fcntl, ret, F_SETFD, FD_CLOEXEC);
					return __syscall_ret(ret);
				}
				ret = __syscall(SYS_fcntl, fd, F_DUPFD_CLOEXEC, 0);
				if (ret != -EINVAL) {
					if (ret >= 0) __syscall(SYS_close, ret);
					return __syscall_ret(-EINVAL);
				}
				ret = __syscall(SYS_fcntl, fd, F_DUPFD, arg);
				if (ret >= 0) __syscall(SYS_fcntl, ret, F_SETFD, FD_CLOEXEC);
				return __syscall_ret(ret);
			}

			return syscall(SYS_fcntl, fd, cmd, arg);
		}

		case F_SETLK:
		case F_SETLKW:
		case F_GETLK:
		case F_OFD_SETLK:
		case F_OFD_SETLKW:
		case F_OFD_GETLK:
		case F_GETOWN_EX:
		case F_SETOWN_EX:
		{
			va_list ap;
			va_start(ap, cmd);
			void *arg = va_arg(ap, void *);
			va_end(ap);

			if (cmd == F_SETLKW) return syscall_cp(SYS_fcntl, fd, cmd, arg);

			return syscall(SYS_fcntl, fd, cmd, arg);
		}
		case F_GETOWN:
		{
			struct f_owner_ex ex;
			int ret = __syscall(SYS_fcntl, fd, F_GETOWN_EX, &ex);
			if (ret == -EINVAL) return __syscall(SYS_fcntl, fd, cmd);
			if (ret) return __syscall_ret(ret);
			return ex.type == F_OWNER_PGRP ? -ex.pid : ex.pid;
		}
	}

	return syscall(SYS_fcntl, fd, cmd);
}
