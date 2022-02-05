/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions of the Internet Protocol.
 *
 * Version:	@(#)in.h	1.0.1	04/21/93
 *
 * Authors:	Original taken from the GNU Project <netinet/in.h> file.
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#ifndef _LKL_LINUX_IN_H
#define _LKL_LINUX_IN_H

#include <lkl/linux/types.h>
#include <lkl/linux/libc-compat.h>
#include <lkl/linux/socket.h>

#if __LKL__UAPI_DEF_IN_IPPROTO
/* Standard well-defined IP protocols.  */
enum {
  LKL_IPPROTO_IP = 0,		/* Dummy protocol for TCP		*/
#define LKL_IPPROTO_IP		LKL_IPPROTO_IP
  LKL_IPPROTO_ICMP = 1,		/* Internet Control Message Protocol	*/
#define LKL_IPPROTO_ICMP		LKL_IPPROTO_ICMP
  LKL_IPPROTO_IGMP = 2,		/* Internet Group Management Protocol	*/
#define LKL_IPPROTO_IGMP		LKL_IPPROTO_IGMP
  LKL_IPPROTO_IPIP = 4,		/* IPIP tunnels (older KA9Q tunnels use 94) */
#define LKL_IPPROTO_IPIP		LKL_IPPROTO_IPIP
  LKL_IPPROTO_TCP = 6,		/* Transmission Control Protocol	*/
#define LKL_IPPROTO_TCP		LKL_IPPROTO_TCP
  LKL_IPPROTO_EGP = 8,		/* Exterior Gateway Protocol		*/
#define LKL_IPPROTO_EGP		LKL_IPPROTO_EGP
  LKL_IPPROTO_PUP = 12,		/* PUP protocol				*/
#define LKL_IPPROTO_PUP		LKL_IPPROTO_PUP
  LKL_IPPROTO_UDP = 17,		/* User Datagram Protocol		*/
#define LKL_IPPROTO_UDP		LKL_IPPROTO_UDP
  LKL_IPPROTO_IDP = 22,		/* XNS IDP protocol			*/
#define LKL_IPPROTO_IDP		LKL_IPPROTO_IDP
  LKL_IPPROTO_TP = 29,		/* SO Transport Protocol Class 4	*/
#define LKL_IPPROTO_TP		LKL_IPPROTO_TP
  LKL_IPPROTO_DCCP = 33,		/* Datagram Congestion Control Protocol */
#define LKL_IPPROTO_DCCP		LKL_IPPROTO_DCCP
  LKL_IPPROTO_IPV6 = 41,		/* IPv6-in-IPv4 tunnelling		*/
#define LKL_IPPROTO_IPV6		LKL_IPPROTO_IPV6
  LKL_IPPROTO_RSVP = 46,		/* RSVP Protocol			*/
#define LKL_IPPROTO_RSVP		LKL_IPPROTO_RSVP
  LKL_IPPROTO_GRE = 47,		/* Cisco GRE tunnels (rfc 1701,1702)	*/
#define LKL_IPPROTO_GRE		LKL_IPPROTO_GRE
  LKL_IPPROTO_ESP = 50,		/* Encapsulation Security Payload protocol */
#define LKL_IPPROTO_ESP		LKL_IPPROTO_ESP
  LKL_IPPROTO_AH = 51,		/* Authentication Header protocol	*/
#define LKL_IPPROTO_AH		LKL_IPPROTO_AH
  LKL_IPPROTO_MTP = 92,		/* Multicast Transport Protocol		*/
#define LKL_IPPROTO_MTP		LKL_IPPROTO_MTP
  LKL_IPPROTO_BEETPH = 94,		/* IP option pseudo header for BEET	*/
#define LKL_IPPROTO_BEETPH		LKL_IPPROTO_BEETPH
  LKL_IPPROTO_ENCAP = 98,		/* Encapsulation Header			*/
#define LKL_IPPROTO_ENCAP		LKL_IPPROTO_ENCAP
  LKL_IPPROTO_PIM = 103,		/* Protocol Independent Multicast	*/
#define LKL_IPPROTO_PIM		LKL_IPPROTO_PIM
  LKL_IPPROTO_COMP = 108,		/* Compression Header Protocol		*/
#define LKL_IPPROTO_COMP		LKL_IPPROTO_COMP
  LKL_IPPROTO_SCTP = 132,		/* Stream Control Transport Protocol	*/
#define LKL_IPPROTO_SCTP		LKL_IPPROTO_SCTP
  LKL_IPPROTO_UDPLITE = 136,	/* UDP-Lite (RFC 3828)			*/
#define LKL_IPPROTO_UDPLITE		LKL_IPPROTO_UDPLITE
  LKL_IPPROTO_MPLS = 137,		/* MPLS in IP (RFC 4023)		*/
#define LKL_IPPROTO_MPLS		LKL_IPPROTO_MPLS
  LKL_IPPROTO_RAW = 255,		/* Raw IP packets			*/
#define LKL_IPPROTO_RAW		LKL_IPPROTO_RAW
  LKL_IPPROTO_MAX
};
#endif

#if __LKL__UAPI_DEF_IN_ADDR
/* Internet address. */
struct lkl_in_addr {
	__lkl__be32	lkl_s_addr;
};
#endif

#define LKL_IP_TOS		1
#define LKL_IP_TTL		2
#define LKL_IP_HDRINCL	3
#define LKL_IP_OPTIONS	4
#define LKL_IP_ROUTER_ALERT	5
#define LKL_IP_RECVOPTS	6
#define LKL_IP_RETOPTS	7
#define LKL_IP_PKTINFO	8
#define LKL_IP_PKTOPTIONS	9
#define LKL_IP_MTU_DISCOVER	10
#define LKL_IP_RECVERR	11
#define LKL_IP_RECVTTL	12
#define	LKL_IP_RECVTOS	13
#define LKL_IP_MTU		14
#define LKL_IP_FREEBIND	15
#define LKL_IP_IPSEC_POLICY	16
#define LKL_IP_XFRM_POLICY	17
#define LKL_IP_PASSSEC	18
#define LKL_IP_TRANSPARENT	19

/* BSD compatibility */
#define LKL_IP_RECVRETOPTS	LKL_IP_RETOPTS

/* TProxy original addresses */
#define LKL_IP_ORIGDSTADDR       20
#define LKL_IP_RECVORIGDSTADDR   LKL_IP_ORIGDSTADDR

#define LKL_IP_MINTTL       21
#define LKL_IP_NODEFRAG     22
#define LKL_IP_CHECKSUM	23
#define LKL_IP_BIND_ADDRESS_NO_PORT	24
#define LKL_IP_RECVFRAGSIZE	25

/* LKL_IP_MTU_DISCOVER values */
#define LKL_IP_PMTUDISC_DONT		0	/* Never send DF frames */
#define LKL_IP_PMTUDISC_WANT		1	/* Use per route hints	*/
#define LKL_IP_PMTUDISC_DO			2	/* Always DF		*/
#define LKL_IP_PMTUDISC_PROBE		3       /* Ignore dst pmtu      */
/* Always use interface mtu (ignores dst pmtu) but don't set DF flag.
 * Also incoming ICMP frag_needed notifications will be ignored on
 * this socket to prevent accepting spoofed ones.
 */
#define LKL_IP_PMTUDISC_INTERFACE		4
/* weaker version of LKL_IP_PMTUDISC_INTERFACE, which allos packets to get
 * fragmented if they exeed the interface mtu
 */
#define LKL_IP_PMTUDISC_OMIT		5

#define LKL_IP_MULTICAST_IF			32
#define LKL_IP_MULTICAST_TTL 		33
#define LKL_IP_MULTICAST_LOOP 		34
#define LKL_IP_ADD_MEMBERSHIP		35
#define LKL_IP_DROP_MEMBERSHIP		36
#define LKL_IP_UNBLOCK_SOURCE		37
#define LKL_IP_BLOCK_SOURCE			38
#define LKL_IP_ADD_SOURCE_MEMBERSHIP	39
#define LKL_IP_DROP_SOURCE_MEMBERSHIP	40
#define LKL_IP_MSFILTER			41
#define LKL_MCAST_JOIN_GROUP		42
#define LKL_MCAST_BLOCK_SOURCE		43
#define LKL_MCAST_UNBLOCK_SOURCE		44
#define LKL_MCAST_LEAVE_GROUP		45
#define LKL_MCAST_JOIN_SOURCE_GROUP		46
#define LKL_MCAST_LEAVE_SOURCE_GROUP	47
#define LKL_MCAST_MSFILTER			48
#define LKL_IP_MULTICAST_ALL		49
#define LKL_IP_UNICAST_IF			50

#define LKL_MCAST_EXCLUDE	0
#define LKL_MCAST_INCLUDE	1

/* These need to appear somewhere around here */
#define LKL_IP_DEFAULT_MULTICAST_TTL        1
#define LKL_IP_DEFAULT_MULTICAST_LOOP       1

/* Request struct for multicast socket ops */

#if __LKL__UAPI_DEF_IP_MREQ
struct lkl_ip_mreq  {
	struct lkl_in_addr imr_multiaddr;	/* IP multicast address of group */
	struct lkl_in_addr imr_interface;	/* local IP address of interface */
};

struct lkl_ip_mreqn {
	struct lkl_in_addr	imr_multiaddr;		/* IP multicast address of group */
	struct lkl_in_addr	imr_address;		/* local IP address of interface */
	int		imr_ifindex;		/* Interface index */
};

struct lkl_ip_mreq_source {
	__lkl__be32		imr_multiaddr;
	__lkl__be32		imr_interface;
	__lkl__be32		imr_sourceaddr;
};

struct lkl_ip_msfilter {
	__lkl__be32		imsf_multiaddr;
	__lkl__be32		imsf_interface;
	__lkl__u32		imsf_fmode;
	__lkl__u32		imsf_numsrc;
	__lkl__be32		imsf_slist[1];
};

#define LKL_IP_MSFILTER_SIZE(numsrc) \
	(sizeof(struct lkl_ip_msfilter) - sizeof(__lkl__u32) \
	+ (numsrc) * sizeof(__lkl__u32))

struct lkl_group_req {
	__lkl__u32				 gr_interface;	/* interface index */
	struct __lkl__kernel_sockaddr_storage gr_group;	/* group address */
};

struct lkl_group_source_req {
	__lkl__u32				 gsr_interface;	/* interface index */
	struct __lkl__kernel_sockaddr_storage gsr_group;	/* group address */
	struct __lkl__kernel_sockaddr_storage gsr_source;	/* source address */
};

struct lkl_group_filter {
	__lkl__u32				 gf_interface;	/* interface index */
	struct __lkl__kernel_sockaddr_storage gf_group;	/* multicast address */
	__lkl__u32				 gf_fmode;	/* filter mode */
	__lkl__u32				 gf_numsrc;	/* number of sources */
	struct __lkl__kernel_sockaddr_storage gf_slist[1];	/* interface index */
};

#define LKL_GROUP_FILTER_SIZE(numsrc) \
	(sizeof(struct lkl_group_filter) - sizeof(struct __lkl__kernel_sockaddr_storage) \
	+ (numsrc) * sizeof(struct __lkl__kernel_sockaddr_storage))
#endif

#if __LKL__UAPI_DEF_IN_PKTINFO
struct lkl_in_pktinfo {
	int		ipi_ifindex;
	struct lkl_in_addr	ipi_spec_dst;
	struct lkl_in_addr	ipi_addr;
};
#endif

/* Structure describing an Internet (IP) socket address. */
#if  __LKL__UAPI_DEF_SOCKADDR_IN
#define __LKL__SOCK_SIZE__	16		/* sizeof(struct lkl_sockaddr)	*/
struct lkl_sockaddr_in {
  __lkl__kernel_sa_family_t	sin_family;	/* Address family		*/
  __lkl__be16		sin_port;	/* Port number			*/
  struct lkl_in_addr	sin_addr;	/* Internet address		*/

  /* Pad to size of `struct lkl_sockaddr'. */
  unsigned char		__pad[__LKL__SOCK_SIZE__ - sizeof(short int) -
			sizeof(unsigned short int) - sizeof(struct lkl_in_addr)];
};
#define lkl_sin_zero	__pad		/* for BSD UNIX comp. -FvK	*/
#endif

#if __LKL__UAPI_DEF_IN_CLASS
/*
 * Definitions of the bits in an Internet address integer.
 * On subnets, host and network parts are found according
 * to the subnet mask, not these masks.
 */
#define	LKL_IN_CLASSA(a)		((((long int) (a)) & 0x80000000) == 0)
#define	LKL_IN_CLASSA_NET		0xff000000
#define	LKL_IN_CLASSA_NSHIFT	24
#define	LKL_IN_CLASSA_HOST		(0xffffffff & ~LKL_IN_CLASSA_NET)
#define	LKL_IN_CLASSA_MAX		128

#define	LKL_IN_CLASSB(a)		((((long int) (a)) & 0xc0000000) == 0x80000000)
#define	LKL_IN_CLASSB_NET		0xffff0000
#define	LKL_IN_CLASSB_NSHIFT	16
#define	LKL_IN_CLASSB_HOST		(0xffffffff & ~LKL_IN_CLASSB_NET)
#define	LKL_IN_CLASSB_MAX		65536

#define	LKL_IN_CLASSC(a)		((((long int) (a)) & 0xe0000000) == 0xc0000000)
#define	LKL_IN_CLASSC_NET		0xffffff00
#define	LKL_IN_CLASSC_NSHIFT	8
#define	LKL_IN_CLASSC_HOST		(0xffffffff & ~LKL_IN_CLASSC_NET)

#define	LKL_IN_CLASSD(a)		((((long int) (a)) & 0xf0000000) == 0xe0000000)
#define	LKL_IN_MULTICAST(a)		LKL_IN_CLASSD(a)
#define LKL_IN_MULTICAST_NET	0xF0000000

#define	LKL_IN_EXPERIMENTAL(a)	((((long int) (a)) & 0xf0000000) == 0xf0000000)
#define	LKL_IN_BADCLASS(a)		LKL_IN_EXPERIMENTAL((a))

/* Address to accept any incoming messages. */
#define	LKL_INADDR_ANY		((unsigned long int) 0x00000000)

/* Address to send to all hosts. */
#define	LKL_INADDR_BROADCAST	((unsigned long int) 0xffffffff)

/* Address indicating an error return. */
#define	LKL_INADDR_NONE		((unsigned long int) 0xffffffff)

/* Network number for local host loopback. */
#define	LKL_IN_LOOPBACKNET		127

/* Address to loopback in software to local host.  */
#define	LKL_INADDR_LOOPBACK		0x7f000001	/* 127.0.0.1   */
#define	LKL_IN_LOOPBACK(a)		((((long int) (a)) & 0xff000000) == 0x7f000000)

/* Defines for Multicast INADDR */
#define LKL_INADDR_UNSPEC_GROUP   	0xe0000000U	/* 224.0.0.0   */
#define LKL_INADDR_ALLHOSTS_GROUP 	0xe0000001U	/* 224.0.0.1   */
#define LKL_INADDR_ALLRTRS_GROUP    0xe0000002U	/* 224.0.0.2 */
#define LKL_INADDR_MAX_LOCAL_GROUP  0xe00000ffU	/* 224.0.0.255 */
#endif

/* <asm/byteorder.h> contains the htonl type stuff.. */
#include <lkl/asm/byteorder.h> 


#endif /* _LKL_LINUX_IN_H */
