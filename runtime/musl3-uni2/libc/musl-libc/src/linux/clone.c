#define _GNU_SOURCE
#include <stdarg.h>
#include <unistd.h>
#include <sched.h>
#include "pthread_impl.h"
#include "syscall.h"

static const int CLONE_CHILD_TID_FLAGS = CLONE_CHILD_SETTID | CLONE_CHILD_CLEARTID;
static const int CLONE_TLS_FLAGS = CLONE_SETTLS | CLONE_CHILD_TID_FLAGS;
static const int CLONE_PARENT_TID_FLAGS = CLONE_PARENT_SETTID | CLONE_PIDFD | CLONE_TLS_FLAGS;

int clone(int (*func)(void *), void *stack, int flags, void *arg, ...)
{
	va_list ap;
	pid_t *ptid = NULL, *ctid = NULL;
	void  *tls = NULL;

	if (!stack) {
		return __syscall_ret(-EINVAL);
	}

	va_start(ap, arg);
	if (0 != (flags & CLONE_PARENT_TID_FLAGS)) {
		ptid = va_arg(ap, pid_t *);
	}
	if (0 != (flags & CLONE_TLS_FLAGS)) {
		tls  = va_arg(ap, void *);
	}
	if (0 != (flags & CLONE_CHILD_TID_FLAGS)) {
		ctid = va_arg(ap, pid_t *);
	}
	va_end(ap);

	return __syscall_ret(__clone(func, stack, flags, arg, ptid, tls, ctid));
}
