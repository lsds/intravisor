/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_SOCKET_H
#define _LKL_LINUX_SOCKET_H

/*
 * Desired design of maximum size and alignment (see RFC2553)
 */
#define _LKL_K_SS_MAXSIZE	128	/* Implementation specific max size */

typedef unsigned short __lkl__kernel_sa_family_t;

/*
 * The definition uses anonymous union and struct in order to control the
 * default alignment.
 */
struct __lkl__kernel_sockaddr_storage {
	union {
		struct {
			__lkl__kernel_sa_family_t	ss_family; /* address family */
			/* Following field(s) are implementation specific */
			char __data[_LKL_K_SS_MAXSIZE - sizeof(unsigned short)];
				/* space to achieve desired size, */
				/* _SS_MAXSIZE value minus size of ss_family */
		};
		void *__align; /* implementation specific desired alignment */
	};
};

#define LKL_SOCK_SNDBUF_LOCK	1
#define LKL_SOCK_RCVBUF_LOCK	2

#define LKL_SOCK_BUF_LOCK_MASK (LKL_SOCK_SNDBUF_LOCK | LKL_SOCK_RCVBUF_LOCK)

#define LKL_SOCK_TXREHASH_DEFAULT	255
#define LKL_SOCK_TXREHASH_DISABLED	0
#define LKL_SOCK_TXREHASH_ENABLED	1

#endif /* _LKL_LINUX_SOCKET_H */
