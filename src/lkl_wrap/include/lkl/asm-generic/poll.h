/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_POLL_H
#define __LKL__ASM_GENERIC_POLL_H

/* These are specified by iBCS2 */
#define LKL_POLLIN		0x0001
#define LKL_POLLPRI		0x0002
#define LKL_POLLOUT		0x0004
#define LKL_POLLERR		0x0008
#define LKL_POLLHUP		0x0010
#define LKL_POLLNVAL	0x0020

/* The rest seem to be more-or-less nonstandard. Check them! */
#define LKL_POLLRDNORM	0x0040
#define LKL_POLLRDBAND	0x0080
#ifndef LKL_POLLWRNORM
#define LKL_POLLWRNORM	0x0100
#endif
#ifndef LKL_POLLWRBAND
#define LKL_POLLWRBAND	0x0200
#endif
#ifndef LKL_POLLMSG
#define LKL_POLLMSG		0x0400
#endif
#ifndef LKL_POLLREMOVE
#define LKL_POLLREMOVE	0x1000
#endif
#ifndef LKL_POLLRDHUP
#define LKL_POLLRDHUP       0x2000
#endif

#define LKL_POLLFREE	(__lkl__poll_t)0x4000	/* currently only for epoll */

#define LKL_POLL_BUSY_LOOP	(__lkl__poll_t)0x8000

struct lkl_pollfd {
	int fd;
	short events;
	short revents;
};

#endif	/* __LKL__ASM_GENERIC_POLL_H */
