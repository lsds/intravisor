/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *	Types and definitions for LKL_AF_INET6 
 *	Linux INET6 implementation 
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>	
 *
 *	Sources:
 *	IPv6 Program Interfaces for BSD Systems
 *      <draft-ietf-ipngwg-bsd-api-05.txt>
 *
 *	Advanced Sockets API for IPv6
 *	<draft-stevens-advanced-api-00.txt>
 *
 *	This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 */

#ifndef _LKL_LINUX_IN6_H
#define _LKL_LINUX_IN6_H

#include <lkl/linux/types.h>
#include <lkl/linux/libc-compat.h>

/*
 *	IPv6 address structure
 */

#if __LKL__UAPI_DEF_IN6_ADDR
struct lkl_in6_addr {
	union {
		__lkl__u8		u6_addr8[16];
#if __LKL__UAPI_DEF_IN6_ADDR_ALT
		__lkl__be16		u6_addr16[8];
		__lkl__be32		u6_addr32[4];
#endif
	} in6_u;
#define lkl_s6_addr			in6_u.u6_addr8
#if __LKL__UAPI_DEF_IN6_ADDR_ALT
#define lkl_s6_addr16		in6_u.u6_addr16
#define lkl_s6_addr32		in6_u.u6_addr32
#endif
};
#endif /* __LKL__UAPI_DEF_IN6_ADDR */

#if __LKL__UAPI_DEF_SOCKADDR_IN6
struct lkl_sockaddr_in6 {
	unsigned short int	sin6_family;    /* LKL_AF_INET6 */
	__lkl__be16			sin6_port;      /* Transport layer port # */
	__lkl__be32			sin6_flowinfo;  /* IPv6 flow information */
	struct lkl_in6_addr		sin6_addr;      /* IPv6 address */
	__lkl__u32			sin6_scope_id;  /* scope id (new in RFC2553) */
};
#endif /* __LKL__UAPI_DEF_SOCKADDR_IN6 */

#if __LKL__UAPI_DEF_IPV6_MREQ
struct lkl_ipv6_mreq {
	/* IPv6 multicast address of group */
	struct lkl_in6_addr ipv6mr_multiaddr;

	/* local IPv6 address of interface */
	int		ipv6mr_ifindex;
};
#endif /* __UAPI_DEF_IVP6_MREQ */

#define lkl_ipv6mr_acaddr	ipv6mr_multiaddr

struct lkl_in6_flowlabel_req {
	struct lkl_in6_addr	flr_dst;
	__lkl__be32	flr_label;
	__lkl__u8	flr_action;
	__lkl__u8	flr_share;
	__lkl__u16	flr_flags;
	__lkl__u16 	flr_expires;
	__lkl__u16	flr_linger;
	__lkl__u32	__flr_pad;
	/* Options in format of IPV6_PKTOPTIONS */
};

#define LKL_IPV6_FL_A_GET	0
#define LKL_IPV6_FL_A_PUT	1
#define LKL_IPV6_FL_A_RENEW	2

#define LKL_IPV6_FL_F_CREATE	1
#define LKL_IPV6_FL_F_EXCL		2
#define LKL_IPV6_FL_F_REFLECT	4
#define LKL_IPV6_FL_F_REMOTE	8

#define LKL_IPV6_FL_S_NONE		0
#define LKL_IPV6_FL_S_EXCL		1
#define LKL_IPV6_FL_S_PROCESS	2
#define LKL_IPV6_FL_S_USER		3
#define LKL_IPV6_FL_S_ANY		255


/*
 *	Bitmask constant declarations to help applications select out the 
 *	flow label and priority fields.
 *
 *	Note that this are in host byte order while the flowinfo field of
 *	sockaddr_in6 is in network byte order.
 */

#define LKL_IPV6_FLOWINFO_FLOWLABEL		0x000fffff
#define LKL_IPV6_FLOWINFO_PRIORITY		0x0ff00000

/* These definitions are obsolete */
#define LKL_IPV6_PRIORITY_UNCHARACTERIZED	0x0000
#define LKL_IPV6_PRIORITY_FILLER		0x0100
#define LKL_IPV6_PRIORITY_UNATTENDED	0x0200
#define LKL_IPV6_PRIORITY_RESERVED1		0x0300
#define LKL_IPV6_PRIORITY_BULK		0x0400
#define LKL_IPV6_PRIORITY_RESERVED2		0x0500
#define LKL_IPV6_PRIORITY_INTERACTIVE	0x0600
#define LKL_IPV6_PRIORITY_CONTROL		0x0700
#define LKL_IPV6_PRIORITY_8			0x0800
#define LKL_IPV6_PRIORITY_9			0x0900
#define LKL_IPV6_PRIORITY_10		0x0a00
#define LKL_IPV6_PRIORITY_11		0x0b00
#define LKL_IPV6_PRIORITY_12		0x0c00
#define LKL_IPV6_PRIORITY_13		0x0d00
#define LKL_IPV6_PRIORITY_14		0x0e00
#define LKL_IPV6_PRIORITY_15		0x0f00

/*
 *	IPV6 extension headers
 */
#if __LKL__UAPI_DEF_IPPROTO_V6
#define LKL_IPPROTO_HOPOPTS		0	/* IPv6 hop-by-hop options	*/
#define LKL_IPPROTO_ROUTING		43	/* IPv6 routing header		*/
#define LKL_IPPROTO_FRAGMENT	44	/* IPv6 fragmentation header	*/
#define LKL_IPPROTO_ICMPV6		58	/* ICMPv6			*/
#define LKL_IPPROTO_NONE		59	/* IPv6 no next header		*/
#define LKL_IPPROTO_DSTOPTS		60	/* IPv6 destination options	*/
#define LKL_IPPROTO_MH		135	/* IPv6 mobility header		*/
#endif /* __LKL__UAPI_DEF_IPPROTO_V6 */

/*
 *	IPv6 TLV options.
 */
#define LKL_IPV6_TLV_PAD1		0
#define LKL_IPV6_TLV_PADN		1
#define LKL_IPV6_TLV_ROUTERALERT	5
#define LKL_IPV6_TLV_CALIPSO	7	/* RFC 5570 */
#define LKL_IPV6_TLV_JUMBO		194
#define LKL_IPV6_TLV_HAO		201	/* home address option */

/*
 *	IPV6 socket options
 */
#if __LKL__UAPI_DEF_IPV6_OPTIONS
#define LKL_IPV6_ADDRFORM		1
#define LKL_IPV6_2292PKTINFO	2
#define LKL_IPV6_2292HOPOPTS	3
#define LKL_IPV6_2292DSTOPTS	4
#define LKL_IPV6_2292RTHDR		5
#define LKL_IPV6_2292PKTOPTIONS	6
#define LKL_IPV6_CHECKSUM		7
#define LKL_IPV6_2292HOPLIMIT	8
#define LKL_IPV6_NEXTHOP		9
#define LKL_IPV6_AUTHHDR		10	/* obsolete */
#define LKL_IPV6_FLOWINFO		11

#define LKL_IPV6_UNICAST_HOPS	16
#define LKL_IPV6_MULTICAST_IF	17
#define LKL_IPV6_MULTICAST_HOPS	18
#define LKL_IPV6_MULTICAST_LOOP	19
#define LKL_IPV6_ADD_MEMBERSHIP	20
#define LKL_IPV6_DROP_MEMBERSHIP	21
#define LKL_IPV6_ROUTER_ALERT	22
#define LKL_IPV6_MTU_DISCOVER	23
#define LKL_IPV6_MTU		24
#define LKL_IPV6_RECVERR		25
#define LKL_IPV6_V6ONLY		26
#define LKL_IPV6_JOIN_ANYCAST	27
#define LKL_IPV6_LEAVE_ANYCAST	28

/* LKL_IPV6_MTU_DISCOVER values */
#define LKL_IPV6_PMTUDISC_DONT		0
#define LKL_IPV6_PMTUDISC_WANT		1
#define LKL_IPV6_PMTUDISC_DO		2
#define LKL_IPV6_PMTUDISC_PROBE		3
/* same as LKL_IPV6_PMTUDISC_PROBE, provided for symetry with IPv4
 * also see comments on LKL_IP_PMTUDISC_INTERFACE
 */
#define LKL_IPV6_PMTUDISC_INTERFACE		4
/* weaker version of LKL_IPV6_PMTUDISC_INTERFACE, which allows packets to
 * get fragmented if they exceed the interface mtu
 */
#define LKL_IPV6_PMTUDISC_OMIT		5

/* Flowlabel */
#define LKL_IPV6_FLOWLABEL_MGR	32
#define LKL_IPV6_FLOWINFO_SEND	33

#define LKL_IPV6_IPSEC_POLICY	34
#define LKL_IPV6_XFRM_POLICY	35
#define LKL_IPV6_HDRINCL		36
#endif

/*
 * Multicast:
 * Following socket options are shared between IPv4 and IPv6.
 *
 * LKL_MCAST_JOIN_GROUP		42
 * LKL_MCAST_BLOCK_SOURCE		43
 * LKL_MCAST_UNBLOCK_SOURCE		44
 * LKL_MCAST_LEAVE_GROUP		45
 * LKL_MCAST_JOIN_SOURCE_GROUP	46
 * LKL_MCAST_LEAVE_SOURCE_GROUP	47
 * LKL_MCAST_MSFILTER		48
 */

/*
 * Advanced API (RFC3542) (1)
 *
 * Note: IPV6_RECVRTHDRDSTOPTS does not exist. see net/ipv6/datagram.c.
 */

#define LKL_IPV6_RECVPKTINFO	49
#define LKL_IPV6_PKTINFO		50
#define LKL_IPV6_RECVHOPLIMIT	51
#define LKL_IPV6_HOPLIMIT		52
#define LKL_IPV6_RECVHOPOPTS	53
#define LKL_IPV6_HOPOPTS		54
#define LKL_IPV6_RTHDRDSTOPTS	55
#define LKL_IPV6_RECVRTHDR		56
#define LKL_IPV6_RTHDR		57
#define LKL_IPV6_RECVDSTOPTS	58
#define LKL_IPV6_DSTOPTS		59
#define LKL_IPV6_RECVPATHMTU	60
#define LKL_IPV6_PATHMTU		61
#define LKL_IPV6_DONTFRAG		62
#if 0	/* not yet */
#define LKL_IPV6_USE_MIN_MTU	63
#endif

/*
 * Netfilter (1)
 *
 * Following socket options are used in ip6_tables;
 * see include/linux/netfilter_ipv6/ip6_tables.h.
 *
 * IP6T_SO_SET_REPLACE / IP6T_SO_GET_INFO		64
 * IP6T_SO_SET_ADD_COUNTERS / IP6T_SO_GET_ENTRIES	65
 */

/*
 * Advanced API (RFC3542) (2)
 */
#define LKL_IPV6_RECVTCLASS		66
#define LKL_IPV6_TCLASS		67

/*
 * Netfilter (2)
 *
 * Following socket options are used in ip6_tables;
 * see include/linux/netfilter_ipv6/ip6_tables.h.
 *
 * IP6T_SO_GET_REVISION_MATCH	68
 * IP6T_SO_GET_REVISION_TARGET	69
 * IP6T_SO_ORIGINAL_DST		80
 */

#define LKL_IPV6_AUTOFLOWLABEL	70
/* RFC5014: Source address selection */
#define LKL_IPV6_ADDR_PREFERENCES	72

#define LKL_IPV6_PREFER_SRC_TMP		0x0001
#define LKL_IPV6_PREFER_SRC_PUBLIC		0x0002
#define LKL_IPV6_PREFER_SRC_PUBTMP_DEFAULT	0x0100
#define LKL_IPV6_PREFER_SRC_COA		0x0004
#define LKL_IPV6_PREFER_SRC_HOME		0x0400
#define LKL_IPV6_PREFER_SRC_CGA		0x0008
#define LKL_IPV6_PREFER_SRC_NONCGA		0x0800

/* RFC5082: Generalized Ttl Security Mechanism */
#define LKL_IPV6_MINHOPCOUNT		73

#define LKL_IPV6_ORIGDSTADDR        74
#define LKL_IPV6_RECVORIGDSTADDR    LKL_IPV6_ORIGDSTADDR
#define LKL_IPV6_TRANSPARENT        75
#define LKL_IPV6_UNICAST_IF         76
#define LKL_IPV6_RECVFRAGSIZE	77
#define LKL_IPV6_FREEBIND		78

/*
 * Multicast Routing:
 * see include/uapi/linux/mroute6.h.
 *
 * MRT6_BASE			200
 * ...
 * MRT6_MAX
 */
#endif /* _LKL_LINUX_IN6_H */
