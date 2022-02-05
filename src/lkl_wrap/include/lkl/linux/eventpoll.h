/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  include/linux/eventpoll.h ( Efficient event polling implementation )
 *  Copyright (C) 2001,...,2006	 Davide Libenzi
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#ifndef _LKL_LINUX_EVENTPOLL_H
#define _LKL_LINUX_EVENTPOLL_H

/* For LKL_O_CLOEXEC */
#include <lkl/linux/fcntl.h>
#include <lkl/linux/types.h>

/* Flags for epoll_create1.  */
#define LKL_EPOLL_CLOEXEC LKL_O_CLOEXEC

/* Valid opcodes to issue to sys_epoll_ctl() */
#define LKL_EPOLL_CTL_ADD 1
#define LKL_EPOLL_CTL_DEL 2
#define LKL_EPOLL_CTL_MOD 3

/* Epoll event masks */
#define LKL_EPOLLIN		(__lkl__poll_t)0x00000001
#define LKL_EPOLLPRI	(__lkl__poll_t)0x00000002
#define LKL_EPOLLOUT	(__lkl__poll_t)0x00000004
#define LKL_EPOLLERR	(__lkl__poll_t)0x00000008
#define LKL_EPOLLHUP	(__lkl__poll_t)0x00000010
#define LKL_EPOLLNVAL	(__lkl__poll_t)0x00000020
#define LKL_EPOLLRDNORM	(__lkl__poll_t)0x00000040
#define LKL_EPOLLRDBAND	(__lkl__poll_t)0x00000080
#define LKL_EPOLLWRNORM	(__lkl__poll_t)0x00000100
#define LKL_EPOLLWRBAND	(__lkl__poll_t)0x00000200
#define LKL_EPOLLMSG	(__lkl__poll_t)0x00000400
#define LKL_EPOLLRDHUP	(__lkl__poll_t)0x00002000

/* Set exclusive wakeup mode for the target file descriptor */
#define LKL_EPOLLEXCLUSIVE (__lkl__poll_t)(1U << 28)

/*
 * Request the handling of system wakeup events so as to prevent system suspends
 * from happening while those events are being processed.
 *
 * Assuming neither LKL_EPOLLET nor LKL_EPOLLONESHOT is set, system suspends will not be
 * re-allowed until epoll_wait is called again after consuming the wakeup
 * event(s).
 *
 * Requires LKL_CAP_BLOCK_SUSPEND
 */
#define LKL_EPOLLWAKEUP (__lkl__poll_t)(1U << 29)

/* Set the One Shot behaviour for the target file descriptor */
#define LKL_EPOLLONESHOT (__lkl__poll_t)(1U << 30)

/* Set the Edge Triggered behaviour for the target file descriptor */
#define LKL_EPOLLET (__lkl__poll_t)(1U << 31)

/* 
 * On x86-64 make the 64bit structure have the same alignment as the
 * 32bit structure. This makes 32bit emulation easier.
 *
 * UML/x86_64 needs the same packing as x86_64
 */
#ifdef __x86_64__
#define LKL_EPOLL_PACKED __attribute__((packed))
#else
#define LKL_EPOLL_PACKED
#endif

struct lkl_epoll_event {
	__lkl__poll_t events;
	__lkl__u64 data;
} LKL_EPOLL_PACKED;

#ifdef CONFIG_PM_SLEEP
static __inline__ void lkl_ep_take_care_of_epollwakeup(struct lkl_epoll_event *epev)
{
	if ((epev->events & LKL_EPOLLWAKEUP) && !capable(LKL_CAP_BLOCK_SUSPEND))
		epev->events &= ~LKL_EPOLLWAKEUP;
}
#else
static __inline__ void lkl_ep_take_care_of_epollwakeup(struct lkl_epoll_event *epev)
{
	epev->events &= ~LKL_EPOLLWAKEUP;
}
#endif
#endif /* _LKL_LINUX_EVENTPOLL_H */
