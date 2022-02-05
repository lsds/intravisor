/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_SOCKET_H
#define _LKL_LINUX_SOCKET_H

/*
 * Desired design of maximum size and alignment (see RFC2553)
 */
#define _LKL_K_SS_MAXSIZE	128	/* Implementation specific max size */
#define _LKL_K_SS_ALIGNSIZE	(__alignof__ (struct lkl_sockaddr *))
				/* Implementation specific desired alignment */

typedef unsigned short __lkl__kernel_sa_family_t;

struct __lkl__kernel_sockaddr_storage {
	__lkl__kernel_sa_family_t	ss_family;		/* address family */
	/* Following field(s) are implementation specific */
	char		__data[_LKL_K_SS_MAXSIZE - sizeof(unsigned short)];
				/* space to achieve desired size, */
				/* _SS_MAXSIZE value minus size of ss_family */
} __attribute__ ((aligned(_LKL_K_SS_ALIGNSIZE)));	/* force desired alignment */

#endif /* _LKL_LINUX_SOCKET_H */
