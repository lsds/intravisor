/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions for the IP protocol.
 *
 * Version:	@(#)ip.h	1.0.2	04/28/93
 *
 * Authors:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#ifndef _LKL_LINUX_IP_H
#define _LKL_LINUX_IP_H
#include <lkl/linux/types.h>
#include <lkl/asm/byteorder.h>

#define LKL_IPTOS_TOS_MASK		0x1E
#define LKL_IPTOS_TOS(tos)		((tos)&LKL_IPTOS_TOS_MASK)
#define	LKL_IPTOS_LOWDELAY		0x10
#define	LKL_IPTOS_THROUGHPUT	0x08
#define	LKL_IPTOS_RELIABILITY	0x04
#define	LKL_IPTOS_MINCOST		0x02

#define LKL_IPTOS_PREC_MASK		0xE0
#define LKL_IPTOS_PREC(tos)		((tos)&LKL_IPTOS_PREC_MASK)
#define LKL_IPTOS_PREC_NETCONTROL           0xe0
#define LKL_IPTOS_PREC_INTERNETCONTROL      0xc0
#define LKL_IPTOS_PREC_CRITIC_ECP           0xa0
#define LKL_IPTOS_PREC_FLASHOVERRIDE        0x80
#define LKL_IPTOS_PREC_FLASH                0x60
#define LKL_IPTOS_PREC_IMMEDIATE            0x40
#define LKL_IPTOS_PREC_PRIORITY             0x20
#define LKL_IPTOS_PREC_ROUTINE              0x00


/* IP options */
#define LKL_IPOPT_COPY		0x80
#define LKL_IPOPT_CLASS_MASK	0x60
#define LKL_IPOPT_NUMBER_MASK	0x1f

#define	LKL_IPOPT_COPIED(o)		((o)&LKL_IPOPT_COPY)
#define	LKL_IPOPT_CLASS(o)		((o)&LKL_IPOPT_CLASS_MASK)
#define	LKL_IPOPT_NUMBER(o)		((o)&LKL_IPOPT_NUMBER_MASK)

#define	LKL_IPOPT_CONTROL		0x00
#define	LKL_IPOPT_RESERVED1		0x20
#define	LKL_IPOPT_MEASUREMENT	0x40
#define	LKL_IPOPT_RESERVED2		0x60

#define LKL_IPOPT_END	(0 |LKL_IPOPT_CONTROL)
#define LKL_IPOPT_NOOP	(1 |LKL_IPOPT_CONTROL)
#define LKL_IPOPT_SEC	(2 |LKL_IPOPT_CONTROL|LKL_IPOPT_COPY)
#define LKL_IPOPT_LSRR	(3 |LKL_IPOPT_CONTROL|LKL_IPOPT_COPY)
#define LKL_IPOPT_TIMESTAMP	(4 |LKL_IPOPT_MEASUREMENT)
#define LKL_IPOPT_CIPSO	(6 |LKL_IPOPT_CONTROL|LKL_IPOPT_COPY)
#define LKL_IPOPT_RR	(7 |LKL_IPOPT_CONTROL)
#define LKL_IPOPT_SID	(8 |LKL_IPOPT_CONTROL|LKL_IPOPT_COPY)
#define LKL_IPOPT_SSRR	(9 |LKL_IPOPT_CONTROL|LKL_IPOPT_COPY)
#define LKL_IPOPT_RA	(20|LKL_IPOPT_CONTROL|LKL_IPOPT_COPY)

#define LKL_IPVERSION	4
#define LKL_MAXTTL		255
#define LKL_IPDEFTTL	64

#define LKL_IPOPT_OPTVAL 0
#define LKL_IPOPT_OLEN   1
#define LKL_IPOPT_OFFSET 2
#define LKL_IPOPT_MINOFF 4
#define LKL_MAX_IPOPTLEN 40
#define LKL_IPOPT_NOP LKL_IPOPT_NOOP
#define LKL_IPOPT_EOL LKL_IPOPT_END
#define LKL_IPOPT_TS  LKL_IPOPT_TIMESTAMP

#define	LKL_IPOPT_TS_TSONLY		0		/* timestamps only */
#define	LKL_IPOPT_TS_TSANDADDR	1		/* timestamps and addresses */
#define	LKL_IPOPT_TS_PRESPEC	3		/* specified modules only */

#define LKL_IPV4_BEET_PHMAXLEN 8

struct lkl_iphdr {
#if defined(__LKL__LITTLE_ENDIAN_BITFIELD)
	__lkl__u8	ihl:4,
		version:4;
#elif defined (__LKL__BIG_ENDIAN_BITFIELD)
	__lkl__u8	version:4,
  		ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
	__lkl__u8	tos;
	__lkl__be16	tot_len;
	__lkl__be16	id;
	__lkl__be16	frag_off;
	__lkl__u8	ttl;
	__lkl__u8	protocol;
	__lkl__sum16	check;
	__lkl__be32	saddr;
	__lkl__be32	daddr;
	/*The options start here. */
};


struct lkl_ip_auth_hdr {
	__lkl__u8  nexthdr;
	__lkl__u8  hdrlen;		/* This one is measured in 32 bit units! */
	__lkl__be16 reserved;
	__lkl__be32 spi;
	__lkl__be32 seq_no;		/* Sequence number */
	__lkl__u8  auth_data[0];	/* Variable len but >=4. Mind the 64 bit alignment! */
};

struct lkl_ip_esp_hdr {
	__lkl__be32 spi;
	__lkl__be32 seq_no;		/* Sequence number */
	__lkl__u8  enc_data[0];	/* Variable len but >=8. Mind the 64 bit alignment! */
};

struct lkl_ip_comp_hdr {
	__lkl__u8 nexthdr;
	__lkl__u8 flags;
	__lkl__be16 cpi;
};

struct lkl_ip_beet_phdr {
	__lkl__u8 nexthdr;
	__lkl__u8 hdrlen;
	__lkl__u8 padlen;
	__lkl__u8 reserved;
};

/* index values for the variables in ipv4_devconf */
enum
{
	LKL_IPV4_DEVCONF_FORWARDING=1,
	LKL_IPV4_DEVCONF_MC_FORWARDING,
	LKL_IPV4_DEVCONF_PROXY_ARP,
	LKL_IPV4_DEVCONF_ACCEPT_REDIRECTS,
	LKL_IPV4_DEVCONF_SECURE_REDIRECTS,
	LKL_IPV4_DEVCONF_SEND_REDIRECTS,
	LKL_IPV4_DEVCONF_SHARED_MEDIA,
	LKL_IPV4_DEVCONF_RP_FILTER,
	LKL_IPV4_DEVCONF_ACCEPT_SOURCE_ROUTE,
	LKL_IPV4_DEVCONF_BOOTP_RELAY,
	LKL_IPV4_DEVCONF_LOG_MARTIANS,
	LKL_IPV4_DEVCONF_TAG,
	LKL_IPV4_DEVCONF_ARPFILTER,
	LKL_IPV4_DEVCONF_MEDIUM_ID,
	LKL_IPV4_DEVCONF_NOXFRM,
	LKL_IPV4_DEVCONF_NOPOLICY,
	LKL_IPV4_DEVCONF_FORCE_IGMP_VERSION,
	LKL_IPV4_DEVCONF_ARP_ANNOUNCE,
	LKL_IPV4_DEVCONF_ARP_IGNORE,
	LKL_IPV4_DEVCONF_PROMOTE_SECONDARIES,
	LKL_IPV4_DEVCONF_ARP_ACCEPT,
	LKL_IPV4_DEVCONF_ARP_NOTIFY,
	LKL_IPV4_DEVCONF_ACCEPT_LOCAL,
	LKL_IPV4_DEVCONF_SRC_VMARK,
	LKL_IPV4_DEVCONF_PROXY_ARP_PVLAN,
	LKL_IPV4_DEVCONF_ROUTE_LOCALNET,
	LKL_IPV4_DEVCONF_IGMPV2_UNSOLICITED_REPORT_INTERVAL,
	LKL_IPV4_DEVCONF_IGMPV3_UNSOLICITED_REPORT_INTERVAL,
	LKL_IPV4_DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN,
	LKL_IPV4_DEVCONF_DROP_UNICAST_IN_L2_MULTICAST,
	LKL_IPV4_DEVCONF_DROP_GRATUITOUS_ARP,
	__LKL__IPV4_DEVCONF_MAX
};

#define LKL_IPV4_DEVCONF_MAX (__LKL__IPV4_DEVCONF_MAX - 1)

#endif /* _LKL_LINUX_IP_H */
