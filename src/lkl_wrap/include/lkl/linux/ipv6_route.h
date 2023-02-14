/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 *
 *	This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#ifndef _LKL_LINUX_IPV6_ROUTE_H
#define _LKL_LINUX_IPV6_ROUTE_H

#include <lkl/linux/types.h>
#include <lkl/linux/in6.h>			/* For struct lkl_in6_addr. */

#define LKL_RTF_DEFAULT	0x00010000	/* default - learned via ND	*/
#define LKL_RTF_ALLONLINK	0x00020000	/* (deprecated and will be removed)
					   fallback, no routers on link */
#define LKL_RTF_ADDRCONF	0x00040000	/* addrconf route - RA		*/
#define LKL_RTF_PREFIX_RT	0x00080000	/* A prefix only route - RA	*/
#define LKL_RTF_ANYCAST	0x00100000	/* Anycast			*/

#define LKL_RTF_NONEXTHOP	0x00200000	/* route with no nexthop	*/
#define LKL_RTF_EXPIRES	0x00400000

#define LKL_RTF_ROUTEINFO	0x00800000	/* route information - RA	*/

#define LKL_RTF_CACHE	0x01000000	/* read-only: can not be set by user */
#define LKL_RTF_FLOW	0x02000000	/* flow significant route	*/
#define LKL_RTF_POLICY	0x04000000	/* policy route			*/

#define LKL_RTF_PREF(pref)	((pref) << 27)
#define LKL_RTF_PREF_MASK	0x18000000

#define LKL_RTF_PCPU	0x40000000	/* read-only: can not be set by user */
#define LKL_RTF_LOCAL	0x80000000


struct lkl_in6_rtmsg {
	struct lkl_in6_addr		rtmsg_dst;
	struct lkl_in6_addr		rtmsg_src;
	struct lkl_in6_addr		rtmsg_gateway;
	__lkl__u32			rtmsg_type;
	__lkl__u16			rtmsg_dst_len;
	__lkl__u16			rtmsg_src_len;
	__lkl__u32			rtmsg_metric;
	unsigned long		rtmsg_info;
        __lkl__u32			rtmsg_flags;
	int			rtmsg_ifindex;
};

#define LKL_RTMSG_NEWDEVICE		0x11
#define LKL_RTMSG_DELDEVICE		0x12
#define LKL_RTMSG_NEWROUTE		0x21
#define LKL_RTMSG_DELROUTE		0x22

#define LKL_IP6_RT_PRIO_USER	1024
#define LKL_IP6_RT_PRIO_ADDRCONF	256

#endif /* _LKL_LINUX_IPV6_ROUTE_H */
