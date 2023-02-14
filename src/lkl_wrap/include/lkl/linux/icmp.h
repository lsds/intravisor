/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions for the ICMP protocol.
 *
 * Version:	@(#)icmp.h	1.0.3	04/28/93
 *
 * Author:	Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#ifndef _LKL_LINUX_ICMP_H
#define _LKL_LINUX_ICMP_H

#include <lkl/linux/types.h>

#define LKL_ICMP_ECHOREPLY		0	/* Echo Reply			*/
#define LKL_ICMP_DEST_UNREACH	3	/* Destination Unreachable	*/
#define LKL_ICMP_SOURCE_QUENCH	4	/* Source Quench		*/
#define LKL_ICMP_REDIRECT		5	/* Redirect (change route)	*/
#define LKL_ICMP_ECHO		8	/* Echo Request			*/
#define LKL_ICMP_TIME_EXCEEDED	11	/* Time Exceeded		*/
#define LKL_ICMP_PARAMETERPROB	12	/* Parameter Problem		*/
#define LKL_ICMP_TIMESTAMP		13	/* Timestamp Request		*/
#define LKL_ICMP_TIMESTAMPREPLY	14	/* Timestamp Reply		*/
#define LKL_ICMP_INFO_REQUEST	15	/* Information Request		*/
#define LKL_ICMP_INFO_REPLY		16	/* Information Reply		*/
#define LKL_ICMP_ADDRESS		17	/* Address Mask Request		*/
#define LKL_ICMP_ADDRESSREPLY	18	/* Address Mask Reply		*/
#define LKL_NR_ICMP_TYPES		18


/* Codes for UNREACH. */
#define LKL_ICMP_NET_UNREACH	0	/* Network Unreachable		*/
#define LKL_ICMP_HOST_UNREACH	1	/* Host Unreachable		*/
#define LKL_ICMP_PROT_UNREACH	2	/* Protocol Unreachable		*/
#define LKL_ICMP_PORT_UNREACH	3	/* Port Unreachable		*/
#define LKL_ICMP_FRAG_NEEDED	4	/* Fragmentation Needed/DF set	*/
#define LKL_ICMP_SR_FAILED		5	/* Source Route failed		*/
#define LKL_ICMP_NET_UNKNOWN	6
#define LKL_ICMP_HOST_UNKNOWN	7
#define LKL_ICMP_HOST_ISOLATED	8
#define LKL_ICMP_NET_ANO		9
#define LKL_ICMP_HOST_ANO		10
#define LKL_ICMP_NET_UNR_TOS	11
#define LKL_ICMP_HOST_UNR_TOS	12
#define LKL_ICMP_PKT_FILTERED	13	/* Packet filtered */
#define LKL_ICMP_PREC_VIOLATION	14	/* Precedence violation */
#define LKL_ICMP_PREC_CUTOFF	15	/* Precedence cut off */
#define LKL_NR_ICMP_UNREACH		15	/* instead of hardcoding immediate value */

/* Codes for REDIRECT. */
#define LKL_ICMP_REDIR_NET		0	/* Redirect Net			*/
#define LKL_ICMP_REDIR_HOST		1	/* Redirect Host		*/
#define LKL_ICMP_REDIR_NETTOS	2	/* Redirect Net for TOS		*/
#define LKL_ICMP_REDIR_HOSTTOS	3	/* Redirect Host for TOS	*/

/* Codes for TIME_EXCEEDED. */
#define LKL_ICMP_EXC_TTL		0	/* TTL count exceeded		*/
#define LKL_ICMP_EXC_FRAGTIME	1	/* Fragment Reass time exceeded	*/


struct lkl_icmphdr {
  __lkl__u8		type;
  __lkl__u8		code;
  __lkl__sum16	checksum;
  union {
	struct {
		__lkl__be16	id;
		__lkl__be16	sequence;
	} echo;
	__lkl__be32	gateway;
	struct {
		__lkl__be16	__unused;
		__lkl__be16	mtu;
	} frag;
	__lkl__u8	reserved[4];
  } un;
};


/*
 *	constants for (set|get)sockopt
 */

#define LKL_ICMP_FILTER			1

struct lkl_icmp_filter {
	__lkl__u32		data;
};


#endif /* _LKL_LINUX_ICMP_H */
