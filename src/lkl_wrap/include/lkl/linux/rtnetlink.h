/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__LINUX_RTNETLINK_H
#define __LKL__LINUX_RTNETLINK_H

#include <lkl/linux/types.h>
#include <lkl/linux/netlink.h>
#include <lkl/linux/if_link.h>
#include <lkl/linux/if_addr.h>
#include <lkl/linux/neighbour.h>

/* rtnetlink families. Values up to 127 are reserved for real address
 * families, values above 128 may be used arbitrarily.
 */
#define LKL_RTNL_FAMILY_IPMR		128
#define LKL_RTNL_FAMILY_IP6MR		129
#define LKL_RTNL_FAMILY_MAX			129

/****
 *		Routing/neighbour discovery messages.
 ****/

/* Types of messages */

enum {
	LKL_RTM_BASE	= 16,
#define LKL_RTM_BASE	LKL_RTM_BASE

	LKL_RTM_NEWLINK	= 16,
#define LKL_RTM_NEWLINK	LKL_RTM_NEWLINK
	LKL_RTM_DELLINK,
#define LKL_RTM_DELLINK	LKL_RTM_DELLINK
	LKL_RTM_GETLINK,
#define LKL_RTM_GETLINK	LKL_RTM_GETLINK
	LKL_RTM_SETLINK,
#define LKL_RTM_SETLINK	LKL_RTM_SETLINK

	LKL_RTM_NEWADDR	= 20,
#define LKL_RTM_NEWADDR	LKL_RTM_NEWADDR
	LKL_RTM_DELADDR,
#define LKL_RTM_DELADDR	LKL_RTM_DELADDR
	LKL_RTM_GETADDR,
#define LKL_RTM_GETADDR	LKL_RTM_GETADDR

	LKL_RTM_NEWROUTE	= 24,
#define LKL_RTM_NEWROUTE	LKL_RTM_NEWROUTE
	LKL_RTM_DELROUTE,
#define LKL_RTM_DELROUTE	LKL_RTM_DELROUTE
	LKL_RTM_GETROUTE,
#define LKL_RTM_GETROUTE	LKL_RTM_GETROUTE

	LKL_RTM_NEWNEIGH	= 28,
#define LKL_RTM_NEWNEIGH	LKL_RTM_NEWNEIGH
	LKL_RTM_DELNEIGH,
#define LKL_RTM_DELNEIGH	LKL_RTM_DELNEIGH
	LKL_RTM_GETNEIGH,
#define LKL_RTM_GETNEIGH	LKL_RTM_GETNEIGH

	LKL_RTM_NEWRULE	= 32,
#define LKL_RTM_NEWRULE	LKL_RTM_NEWRULE
	LKL_RTM_DELRULE,
#define LKL_RTM_DELRULE	LKL_RTM_DELRULE
	LKL_RTM_GETRULE,
#define LKL_RTM_GETRULE	LKL_RTM_GETRULE

	LKL_RTM_NEWQDISC	= 36,
#define LKL_RTM_NEWQDISC	LKL_RTM_NEWQDISC
	LKL_RTM_DELQDISC,
#define LKL_RTM_DELQDISC	LKL_RTM_DELQDISC
	LKL_RTM_GETQDISC,
#define LKL_RTM_GETQDISC	LKL_RTM_GETQDISC

	LKL_RTM_NEWTCLASS	= 40,
#define LKL_RTM_NEWTCLASS	LKL_RTM_NEWTCLASS
	LKL_RTM_DELTCLASS,
#define LKL_RTM_DELTCLASS	LKL_RTM_DELTCLASS
	LKL_RTM_GETTCLASS,
#define LKL_RTM_GETTCLASS	LKL_RTM_GETTCLASS

	LKL_RTM_NEWTFILTER	= 44,
#define LKL_RTM_NEWTFILTER	LKL_RTM_NEWTFILTER
	LKL_RTM_DELTFILTER,
#define LKL_RTM_DELTFILTER	LKL_RTM_DELTFILTER
	LKL_RTM_GETTFILTER,
#define LKL_RTM_GETTFILTER	LKL_RTM_GETTFILTER

	LKL_RTM_NEWACTION	= 48,
#define LKL_RTM_NEWACTION   LKL_RTM_NEWACTION
	LKL_RTM_DELACTION,
#define LKL_RTM_DELACTION   LKL_RTM_DELACTION
	LKL_RTM_GETACTION,
#define LKL_RTM_GETACTION   LKL_RTM_GETACTION

	LKL_RTM_NEWPREFIX	= 52,
#define LKL_RTM_NEWPREFIX	LKL_RTM_NEWPREFIX

	LKL_RTM_GETMULTICAST = 58,
#define LKL_RTM_GETMULTICAST LKL_RTM_GETMULTICAST

	LKL_RTM_GETANYCAST	= 62,
#define LKL_RTM_GETANYCAST	LKL_RTM_GETANYCAST

	LKL_RTM_NEWNEIGHTBL	= 64,
#define LKL_RTM_NEWNEIGHTBL	LKL_RTM_NEWNEIGHTBL
	LKL_RTM_GETNEIGHTBL	= 66,
#define LKL_RTM_GETNEIGHTBL	LKL_RTM_GETNEIGHTBL
	LKL_RTM_SETNEIGHTBL,
#define LKL_RTM_SETNEIGHTBL	LKL_RTM_SETNEIGHTBL

	LKL_RTM_NEWNDUSEROPT = 68,
#define LKL_RTM_NEWNDUSEROPT LKL_RTM_NEWNDUSEROPT

	LKL_RTM_NEWADDRLABEL = 72,
#define LKL_RTM_NEWADDRLABEL LKL_RTM_NEWADDRLABEL
	LKL_RTM_DELADDRLABEL,
#define LKL_RTM_DELADDRLABEL LKL_RTM_DELADDRLABEL
	LKL_RTM_GETADDRLABEL,
#define LKL_RTM_GETADDRLABEL LKL_RTM_GETADDRLABEL

	LKL_RTM_GETDCB = 78,
#define LKL_RTM_GETDCB LKL_RTM_GETDCB
	LKL_RTM_SETDCB,
#define LKL_RTM_SETDCB LKL_RTM_SETDCB

	LKL_RTM_NEWNETCONF = 80,
#define LKL_RTM_NEWNETCONF LKL_RTM_NEWNETCONF
	LKL_RTM_DELNETCONF,
#define LKL_RTM_DELNETCONF LKL_RTM_DELNETCONF
	LKL_RTM_GETNETCONF = 82,
#define LKL_RTM_GETNETCONF LKL_RTM_GETNETCONF

	LKL_RTM_NEWMDB = 84,
#define LKL_RTM_NEWMDB LKL_RTM_NEWMDB
	LKL_RTM_DELMDB = 85,
#define LKL_RTM_DELMDB LKL_RTM_DELMDB
	LKL_RTM_GETMDB = 86,
#define LKL_RTM_GETMDB LKL_RTM_GETMDB

	LKL_RTM_NEWNSID = 88,
#define LKL_RTM_NEWNSID LKL_RTM_NEWNSID
	LKL_RTM_DELNSID = 89,
#define LKL_RTM_DELNSID LKL_RTM_DELNSID
	LKL_RTM_GETNSID = 90,
#define LKL_RTM_GETNSID LKL_RTM_GETNSID

	LKL_RTM_NEWSTATS = 92,
#define LKL_RTM_NEWSTATS LKL_RTM_NEWSTATS
	LKL_RTM_GETSTATS = 94,
#define LKL_RTM_GETSTATS LKL_RTM_GETSTATS

	LKL_RTM_NEWCACHEREPORT = 96,
#define LKL_RTM_NEWCACHEREPORT LKL_RTM_NEWCACHEREPORT

	__LKL__RTM_MAX,
#define LKL_RTM_MAX		(((__LKL__RTM_MAX + 3) & ~3) - 1)
};

#define LKL_RTM_NR_MSGTYPES	(LKL_RTM_MAX + 1 - LKL_RTM_BASE)
#define LKL_RTM_NR_FAMILIES	(LKL_RTM_NR_MSGTYPES >> 2)
#define LKL_RTM_FAM(cmd)	(((cmd) - LKL_RTM_BASE) >> 2)

/* 
   Generic structure for encapsulation of optional route information.
   It is reminiscent of sockaddr, but with sa_family replaced
   with attribute type.
 */

struct lkl_rtattr {
	unsigned short	rta_len;
	unsigned short	rta_type;
};

/* Macros to handle rtattributes */

#define LKL_RTA_ALIGNTO	4U
#define LKL_RTA_ALIGN(len) ( ((len)+LKL_RTA_ALIGNTO-1) & ~(LKL_RTA_ALIGNTO-1) )
#define LKL_RTA_OK(rta,len) ((len) >= (int)sizeof(struct lkl_rtattr) && \
			 (rta)->rta_len >= sizeof(struct lkl_rtattr) && \
			 (rta)->rta_len <= (len))
#define LKL_RTA_NEXT(rta,attrlen)	((attrlen) -= LKL_RTA_ALIGN((rta)->rta_len), \
				 (struct lkl_rtattr*)(((char*)(rta)) + LKL_RTA_ALIGN((rta)->rta_len)))
#define LKL_RTA_LENGTH(len)	(LKL_RTA_ALIGN(sizeof(struct lkl_rtattr)) + (len))
#define LKL_RTA_SPACE(len)	LKL_RTA_ALIGN(LKL_RTA_LENGTH(len))
#define LKL_RTA_DATA(rta)   ((void*)(((char*)(rta)) + LKL_RTA_LENGTH(0)))
#define LKL_RTA_PAYLOAD(rta) ((int)((rta)->rta_len) - LKL_RTA_LENGTH(0))




/******************************************************************************
 *		Definitions used in routing table administration.
 ****/

struct lkl_rtmsg {
	unsigned char		rtm_family;
	unsigned char		rtm_dst_len;
	unsigned char		rtm_src_len;
	unsigned char		rtm_tos;

	unsigned char		rtm_table;	/* Routing table id */
	unsigned char		rtm_protocol;	/* Routing protocol; see below	*/
	unsigned char		rtm_scope;	/* See below */	
	unsigned char		rtm_type;	/* See below	*/

	unsigned		rtm_flags;
};

/* rtm_type */

enum {
	LKL_RTN_UNSPEC,
	LKL_RTN_UNICAST,		/* Gateway or direct route	*/
	LKL_RTN_LOCAL,		/* Accept locally		*/
	LKL_RTN_BROADCAST,		/* Accept locally as broadcast,
				   send as broadcast */
	LKL_RTN_ANYCAST,		/* Accept locally as broadcast,
				   but send as unicast */
	LKL_RTN_MULTICAST,		/* Multicast route		*/
	LKL_RTN_BLACKHOLE,		/* Drop				*/
	LKL_RTN_UNREACHABLE,	/* Destination is unreachable   */
	LKL_RTN_PROHIBIT,		/* Administratively prohibited	*/
	LKL_RTN_THROW,		/* Not in this table		*/
	LKL_RTN_NAT,		/* Translate this address	*/
	LKL_RTN_XRESOLVE,		/* Use external resolver	*/
	__LKL__RTN_MAX
};

#define LKL_RTN_MAX (__LKL__RTN_MAX - 1)


/* rtm_protocol */

#define LKL_RTPROT_UNSPEC	0
#define LKL_RTPROT_REDIRECT	1	/* Route installed by ICMP redirects;
				   not used by current IPv4 */
#define LKL_RTPROT_KERNEL	2	/* Route installed by kernel		*/
#define LKL_RTPROT_BOOT	3	/* Route installed during boot		*/
#define LKL_RTPROT_STATIC	4	/* Route installed by administrator	*/

/* Values of protocol >= LKL_RTPROT_STATIC are not interpreted by kernel;
   they are just passed from user and back as is.
   It will be used by hypothetical multiple routing daemons.
   Note that protocol values should be standardized in order to
   avoid conflicts.
 */

#define LKL_RTPROT_GATED	8	/* Apparently, GateD */
#define LKL_RTPROT_RA	9	/* RDISC/ND router advertisements */
#define LKL_RTPROT_MRT	10	/* Merit MRT */
#define LKL_RTPROT_ZEBRA	11	/* Zebra */
#define LKL_RTPROT_BIRD	12	/* BIRD */
#define LKL_RTPROT_DNROUTED	13	/* DECnet routing daemon */
#define LKL_RTPROT_XORP	14	/* XORP */
#define LKL_RTPROT_NTK	15	/* Netsukuku */
#define LKL_RTPROT_DHCP	16      /* DHCP client */
#define LKL_RTPROT_MROUTED	17      /* Multicast daemon */
#define LKL_RTPROT_BABEL	42      /* Babel daemon */

/* rtm_scope

   Really it is not scope, but sort of distance to the destination.
   NOWHERE are reserved for not existing destinations, HOST is our
   local addresses, LINK are destinations, located on directly attached
   link and UNIVERSE is everywhere in the Universe.

   Intermediate values are also possible f.e. interior routes
   could be assigned a value between UNIVERSE and LINK.
*/

enum lkl_rt_scope_t {
	LKL_RT_SCOPE_UNIVERSE=0,
/* User defined values  */
	LKL_RT_SCOPE_SITE=200,
	LKL_RT_SCOPE_LINK=253,
	LKL_RT_SCOPE_HOST=254,
	LKL_RT_SCOPE_NOWHERE=255
};

/* rtm_flags */

#define LKL_RTM_F_NOTIFY		0x100	/* Notify user of route change	*/
#define LKL_RTM_F_CLONED		0x200	/* This route is cloned		*/
#define LKL_RTM_F_EQUALIZE		0x400	/* Multipath equalizer: NI	*/
#define LKL_RTM_F_PREFIX		0x800	/* Prefix addresses		*/
#define LKL_RTM_F_LOOKUP_TABLE	0x1000	/* set rtm_table to FIB lookup result */
#define LKL_RTM_F_FIB_MATCH	        0x2000	/* return full fib lookup match */

/* Reserved table identifiers */

enum lkl_rt_class_t {
	LKL_RT_TABLE_UNSPEC=0,
/* User defined values */
	LKL_RT_TABLE_COMPAT=252,
	LKL_RT_TABLE_DEFAULT=253,
	LKL_RT_TABLE_MAIN=254,
	LKL_RT_TABLE_LOCAL=255,
	LKL_RT_TABLE_MAX=0xFFFFFFFF
};


/* Routing message attributes */

enum lkl_rtattr_type_t {
	LKL_RTA_UNSPEC,
	LKL_RTA_DST,
	LKL_RTA_SRC,
	LKL_RTA_IIF,
	LKL_RTA_OIF,
	LKL_RTA_GATEWAY,
	LKL_RTA_PRIORITY,
	LKL_RTA_PREFSRC,
	LKL_RTA_METRICS,
	LKL_RTA_MULTIPATH,
	LKL_RTA_PROTOINFO, /* no longer used */
	LKL_RTA_FLOW,
	LKL_RTA_CACHEINFO,
	LKL_RTA_SESSION, /* no longer used */
	LKL_RTA_MP_ALGO, /* no longer used */
	LKL_RTA_TABLE,
	LKL_RTA_MARK,
	LKL_RTA_MFC_STATS,
	LKL_RTA_VIA,
	LKL_RTA_NEWDST,
	LKL_RTA_PREF,
	LKL_RTA_ENCAP_TYPE,
	LKL_RTA_ENCAP,
	LKL_RTA_EXPIRES,
	LKL_RTA_PAD,
	LKL_RTA_UID,
	LKL_RTA_TTL_PROPAGATE,
	__LKL__RTA_MAX
};

#define LKL_RTA_MAX (__LKL__RTA_MAX - 1)

#define LKL_RTM_RTA(r)  ((struct lkl_rtattr*)(((char*)(r)) + LKL_NLMSG_ALIGN(sizeof(struct lkl_rtmsg))))
#define LKL_RTM_PAYLOAD(n) LKL_NLMSG_PAYLOAD(n,sizeof(struct lkl_rtmsg))

/* RTM_MULTIPATH --- array of struct lkl_rtnexthop.
 *
 * "struct lkl_rtnexthop" describes all necessary nexthop information,
 * i.e. parameters of path to a destination via this nexthop.
 *
 * At the moment it is impossible to set different prefsrc, mtu, window
 * and rtt for different paths from multipath.
 */

struct lkl_rtnexthop {
	unsigned short		rtnh_len;
	unsigned char		rtnh_flags;
	unsigned char		rtnh_hops;
	int			rtnh_ifindex;
};

/* rtnh_flags */

#define LKL_RTNH_F_DEAD		1	/* Nexthop is dead (used by multipath)	*/
#define LKL_RTNH_F_PERVASIVE	2	/* Do recursive gateway lookup	*/
#define LKL_RTNH_F_ONLINK		4	/* Gateway is forced on link	*/
#define LKL_RTNH_F_OFFLOAD		8	/* offloaded route */
#define LKL_RTNH_F_LINKDOWN		16	/* carrier-down on nexthop */
#define LKL_RTNH_F_UNRESOLVED	32	/* The entry is unresolved (ipmr) */

#define LKL_RTNH_COMPARE_MASK	(LKL_RTNH_F_DEAD | LKL_RTNH_F_LINKDOWN | LKL_RTNH_F_OFFLOAD)

/* Macros to handle hexthops */

#define LKL_RTNH_ALIGNTO	4
#define LKL_RTNH_ALIGN(len) ( ((len)+LKL_RTNH_ALIGNTO-1) & ~(LKL_RTNH_ALIGNTO-1) )
#define LKL_RTNH_OK(rtnh,len) ((rtnh)->rtnh_len >= sizeof(struct lkl_rtnexthop) && \
			   ((int)(rtnh)->rtnh_len) <= (len))
#define LKL_RTNH_NEXT(rtnh)	((struct lkl_rtnexthop*)(((char*)(rtnh)) + LKL_RTNH_ALIGN((rtnh)->rtnh_len)))
#define LKL_RTNH_LENGTH(len) (LKL_RTNH_ALIGN(sizeof(struct lkl_rtnexthop)) + (len))
#define LKL_RTNH_SPACE(len)	LKL_RTNH_ALIGN(LKL_RTNH_LENGTH(len))
#define LKL_RTNH_DATA(rtnh)   ((struct lkl_rtattr*)(((char*)(rtnh)) + LKL_RTNH_LENGTH(0)))

/* LKL_RTA_VIA */
struct lkl_rtvia {
	__lkl__kernel_sa_family_t	rtvia_family;
	__lkl__u8			rtvia_addr[0];
};

/* RTM_CACHEINFO */

struct lkl_rta_cacheinfo {
	__lkl__u32	rta_clntref;
	__lkl__u32	rta_lastuse;
	__lkl__s32	rta_expires;
	__lkl__u32	rta_error;
	__lkl__u32	rta_used;

#define LKL_RTNETLINK_HAVE_PEERINFO 1
	__lkl__u32	rta_id;
	__lkl__u32	rta_ts;
	__lkl__u32	rta_tsage;
};

/* RTM_METRICS --- array of struct lkl_rtattr with types of RTAX_* */

enum {
	LKL_RTAX_UNSPEC,
#define LKL_RTAX_UNSPEC LKL_RTAX_UNSPEC
	LKL_RTAX_LOCK,
#define LKL_RTAX_LOCK LKL_RTAX_LOCK
	LKL_RTAX_MTU,
#define LKL_RTAX_MTU LKL_RTAX_MTU
	LKL_RTAX_WINDOW,
#define LKL_RTAX_WINDOW LKL_RTAX_WINDOW
	LKL_RTAX_RTT,
#define LKL_RTAX_RTT LKL_RTAX_RTT
	LKL_RTAX_RTTVAR,
#define LKL_RTAX_RTTVAR LKL_RTAX_RTTVAR
	LKL_RTAX_SSTHRESH,
#define LKL_RTAX_SSTHRESH LKL_RTAX_SSTHRESH
	LKL_RTAX_CWND,
#define LKL_RTAX_CWND LKL_RTAX_CWND
	LKL_RTAX_ADVMSS,
#define LKL_RTAX_ADVMSS LKL_RTAX_ADVMSS
	LKL_RTAX_REORDERING,
#define LKL_RTAX_REORDERING LKL_RTAX_REORDERING
	LKL_RTAX_HOPLIMIT,
#define LKL_RTAX_HOPLIMIT LKL_RTAX_HOPLIMIT
	LKL_RTAX_INITCWND,
#define LKL_RTAX_INITCWND LKL_RTAX_INITCWND
	LKL_RTAX_FEATURES,
#define LKL_RTAX_FEATURES LKL_RTAX_FEATURES
	LKL_RTAX_RTO_MIN,
#define LKL_RTAX_RTO_MIN LKL_RTAX_RTO_MIN
	LKL_RTAX_INITRWND,
#define LKL_RTAX_INITRWND LKL_RTAX_INITRWND
	LKL_RTAX_QUICKACK,
#define LKL_RTAX_QUICKACK LKL_RTAX_QUICKACK
	LKL_RTAX_CC_ALGO,
#define LKL_RTAX_CC_ALGO LKL_RTAX_CC_ALGO
	LKL_RTAX_FASTOPEN_NO_COOKIE,
#define LKL_RTAX_FASTOPEN_NO_COOKIE LKL_RTAX_FASTOPEN_NO_COOKIE
	__LKL__RTAX_MAX
};

#define LKL_RTAX_MAX (__LKL__RTAX_MAX - 1)

#define LKL_RTAX_FEATURE_ECN	(1 << 0)
#define LKL_RTAX_FEATURE_SACK	(1 << 1)
#define LKL_RTAX_FEATURE_TIMESTAMP	(1 << 2)
#define LKL_RTAX_FEATURE_ALLFRAG	(1 << 3)

#define LKL_RTAX_FEATURE_MASK	(LKL_RTAX_FEATURE_ECN | LKL_RTAX_FEATURE_SACK | \
				 LKL_RTAX_FEATURE_TIMESTAMP | LKL_RTAX_FEATURE_ALLFRAG)

struct lkl_rta_session {
	__lkl__u8	proto;
	__lkl__u8	pad1;
	__lkl__u16	pad2;

	union {
		struct {
			__lkl__u16	sport;
			__lkl__u16	dport;
		} ports;

		struct {
			__lkl__u8	type;
			__lkl__u8	code;
			__lkl__u16	ident;
		} icmpt;

		__lkl__u32		spi;
	} u;
};

struct lkl_rta_mfc_stats {
	__lkl__u64	mfcs_packets;
	__lkl__u64	mfcs_bytes;
	__lkl__u64	mfcs_wrong_if;
};

/****
 *		General form of address family dependent message.
 ****/

struct lkl_rtgenmsg {
	unsigned char		rtgen_family;
};

/*****************************************************************
 *		Link layer specific messages.
 ****/

/* struct lkl_ifinfomsg
 * passes link level specific information, not dependent
 * on network protocol.
 */

struct lkl_ifinfomsg {
	unsigned char	ifi_family;
	unsigned char	__ifi_pad;
	unsigned short	ifi_type;		/* ARPHRD_* */
	int		ifi_index;		/* Link index	*/
	unsigned	ifi_flags;		/* IFF_* flags	*/
	unsigned	ifi_change;		/* IFF_* change mask */
};

/********************************************************************
 *		prefix information 
 ****/

struct lkl_prefixmsg {
	unsigned char	prefix_family;
	unsigned char	prefix_pad1;
	unsigned short	prefix_pad2;
	int		prefix_ifindex;
	unsigned char	prefix_type;
	unsigned char	prefix_len;
	unsigned char	prefix_flags;
	unsigned char	prefix_pad3;
};

enum 
{
	LKL_PREFIX_UNSPEC,
	LKL_PREFIX_ADDRESS,
	LKL_PREFIX_CACHEINFO,
	__LKL__PREFIX_MAX
};

#define LKL_PREFIX_MAX	(__LKL__PREFIX_MAX - 1)

struct lkl_prefix_cacheinfo {
	__lkl__u32	preferred_time;
	__lkl__u32	valid_time;
};


/*****************************************************************
 *		Traffic control messages.
 ****/

struct lkl_tcmsg {
	unsigned char	tcm_family;
	unsigned char	tcm__pad1;
	unsigned short	tcm__pad2;
	int		tcm_ifindex;
	__lkl__u32		tcm_handle;
	__lkl__u32		tcm_parent;
/* lkl_tcm_block_index is used instead of tcm_parent
 * in case tcm_ifindex == LKL_TCM_IFINDEX_MAGIC_BLOCK
 */
#define lkl_tcm_block_index tcm_parent
	__lkl__u32		tcm_info;
};

/* For manipulation of filters in shared block, tcm_ifindex is set to
 * LKL_TCM_IFINDEX_MAGIC_BLOCK, and tcm_parent is aliased to lkl_tcm_block_index
 * which is the block index.
 */
#define LKL_TCM_IFINDEX_MAGIC_BLOCK (0xFFFFFFFFU)

enum {
	LKL_TCA_UNSPEC,
	LKL_TCA_KIND,
	LKL_TCA_OPTIONS,
	LKL_TCA_STATS,
	LKL_TCA_XSTATS,
	LKL_TCA_RATE,
	LKL_TCA_FCNT,
	LKL_TCA_STATS2,
	LKL_TCA_STAB,
	LKL_TCA_PAD,
	LKL_TCA_DUMP_INVISIBLE,
	LKL_TCA_CHAIN,
	LKL_TCA_HW_OFFLOAD,
	LKL_TCA_INGRESS_BLOCK,
	LKL_TCA_EGRESS_BLOCK,
	__LKL__TCA_MAX
};

#define LKL_TCA_MAX (__LKL__TCA_MAX - 1)

#define LKL_TCA_RTA(r)  ((struct lkl_rtattr*)(((char*)(r)) + LKL_NLMSG_ALIGN(sizeof(struct lkl_tcmsg))))
#define LKL_TCA_PAYLOAD(n) LKL_NLMSG_PAYLOAD(n,sizeof(struct lkl_tcmsg))

/********************************************************************
 *		Neighbor Discovery userland options
 ****/

struct lkl_nduseroptmsg {
	unsigned char	nduseropt_family;
	unsigned char	nduseropt_pad1;
	unsigned short	nduseropt_opts_len;	/* Total length of options */
	int		nduseropt_ifindex;
	__lkl__u8		nduseropt_icmp_type;
	__lkl__u8		nduseropt_icmp_code;
	unsigned short	nduseropt_pad2;
	unsigned int	nduseropt_pad3;
	/* Followed by one or more ND options */
};

enum {
	LKL_NDUSEROPT_UNSPEC,
	LKL_NDUSEROPT_SRCADDR,
	__LKL__NDUSEROPT_MAX
};

#define LKL_NDUSEROPT_MAX	(__LKL__NDUSEROPT_MAX - 1)

/* RTnetlink multicast groups - backwards compatibility for userspace */
#define LKL_RTMGRP_LINK		1
#define LKL_RTMGRP_NOTIFY		2
#define LKL_RTMGRP_NEIGH		4
#define LKL_RTMGRP_TC		8

#define LKL_RTMGRP_IPV4_IFADDR	0x10
#define LKL_RTMGRP_IPV4_MROUTE	0x20
#define LKL_RTMGRP_IPV4_ROUTE	0x40
#define LKL_RTMGRP_IPV4_RULE	0x80

#define LKL_RTMGRP_IPV6_IFADDR	0x100
#define LKL_RTMGRP_IPV6_MROUTE	0x200
#define LKL_RTMGRP_IPV6_ROUTE	0x400
#define LKL_RTMGRP_IPV6_IFINFO	0x800

#define lkl_RTMGRP_DECnet_IFADDR    0x1000
#define lkl_RTMGRP_DECnet_ROUTE     0x4000

#define LKL_RTMGRP_IPV6_PREFIX	0x20000

/* RTnetlink multicast groups */
enum lkl_rtnetlink_groups {
	LKL_RTNLGRP_NONE,
#define LKL_RTNLGRP_NONE		LKL_RTNLGRP_NONE
	LKL_RTNLGRP_LINK,
#define LKL_RTNLGRP_LINK		LKL_RTNLGRP_LINK
	LKL_RTNLGRP_NOTIFY,
#define LKL_RTNLGRP_NOTIFY		LKL_RTNLGRP_NOTIFY
	LKL_RTNLGRP_NEIGH,
#define LKL_RTNLGRP_NEIGH		LKL_RTNLGRP_NEIGH
	LKL_RTNLGRP_TC,
#define LKL_RTNLGRP_TC		LKL_RTNLGRP_TC
	LKL_RTNLGRP_IPV4_IFADDR,
#define LKL_RTNLGRP_IPV4_IFADDR	LKL_RTNLGRP_IPV4_IFADDR
	LKL_RTNLGRP_IPV4_MROUTE,
#define	LKL_RTNLGRP_IPV4_MROUTE	LKL_RTNLGRP_IPV4_MROUTE
	LKL_RTNLGRP_IPV4_ROUTE,
#define LKL_RTNLGRP_IPV4_ROUTE	LKL_RTNLGRP_IPV4_ROUTE
	LKL_RTNLGRP_IPV4_RULE,
#define LKL_RTNLGRP_IPV4_RULE	LKL_RTNLGRP_IPV4_RULE
	LKL_RTNLGRP_IPV6_IFADDR,
#define LKL_RTNLGRP_IPV6_IFADDR	LKL_RTNLGRP_IPV6_IFADDR
	LKL_RTNLGRP_IPV6_MROUTE,
#define LKL_RTNLGRP_IPV6_MROUTE	LKL_RTNLGRP_IPV6_MROUTE
	LKL_RTNLGRP_IPV6_ROUTE,
#define LKL_RTNLGRP_IPV6_ROUTE	LKL_RTNLGRP_IPV6_ROUTE
	LKL_RTNLGRP_IPV6_IFINFO,
#define LKL_RTNLGRP_IPV6_IFINFO	LKL_RTNLGRP_IPV6_IFINFO
	lkl_RTNLGRP_DECnet_IFADDR,
#define lkl_RTNLGRP_DECnet_IFADDR	lkl_RTNLGRP_DECnet_IFADDR
	LKL_RTNLGRP_NOP2,
	lkl_RTNLGRP_DECnet_ROUTE,
#define lkl_RTNLGRP_DECnet_ROUTE	lkl_RTNLGRP_DECnet_ROUTE
	lkl_RTNLGRP_DECnet_RULE,
#define lkl_RTNLGRP_DECnet_RULE	lkl_RTNLGRP_DECnet_RULE
	LKL_RTNLGRP_NOP4,
	LKL_RTNLGRP_IPV6_PREFIX,
#define LKL_RTNLGRP_IPV6_PREFIX	LKL_RTNLGRP_IPV6_PREFIX
	LKL_RTNLGRP_IPV6_RULE,
#define LKL_RTNLGRP_IPV6_RULE	LKL_RTNLGRP_IPV6_RULE
	LKL_RTNLGRP_ND_USEROPT,
#define LKL_RTNLGRP_ND_USEROPT	LKL_RTNLGRP_ND_USEROPT
	LKL_RTNLGRP_PHONET_IFADDR,
#define LKL_RTNLGRP_PHONET_IFADDR	LKL_RTNLGRP_PHONET_IFADDR
	LKL_RTNLGRP_PHONET_ROUTE,
#define LKL_RTNLGRP_PHONET_ROUTE	LKL_RTNLGRP_PHONET_ROUTE
	LKL_RTNLGRP_DCB,
#define LKL_RTNLGRP_DCB		LKL_RTNLGRP_DCB
	LKL_RTNLGRP_IPV4_NETCONF,
#define LKL_RTNLGRP_IPV4_NETCONF	LKL_RTNLGRP_IPV4_NETCONF
	LKL_RTNLGRP_IPV6_NETCONF,
#define LKL_RTNLGRP_IPV6_NETCONF	LKL_RTNLGRP_IPV6_NETCONF
	LKL_RTNLGRP_MDB,
#define LKL_RTNLGRP_MDB		LKL_RTNLGRP_MDB
	LKL_RTNLGRP_MPLS_ROUTE,
#define LKL_RTNLGRP_MPLS_ROUTE	LKL_RTNLGRP_MPLS_ROUTE
	LKL_RTNLGRP_NSID,
#define LKL_RTNLGRP_NSID		LKL_RTNLGRP_NSID
	LKL_RTNLGRP_MPLS_NETCONF,
#define LKL_RTNLGRP_MPLS_NETCONF	LKL_RTNLGRP_MPLS_NETCONF
	LKL_RTNLGRP_IPV4_MROUTE_R,
#define LKL_RTNLGRP_IPV4_MROUTE_R	LKL_RTNLGRP_IPV4_MROUTE_R
	LKL_RTNLGRP_IPV6_MROUTE_R,
#define LKL_RTNLGRP_IPV6_MROUTE_R	LKL_RTNLGRP_IPV6_MROUTE_R
	__LKL__RTNLGRP_MAX
};
#define LKL_RTNLGRP_MAX	(__LKL__RTNLGRP_MAX - 1)

/* TC action piece */
struct lkl_tcamsg {
	unsigned char	tca_family;
	unsigned char	tca__pad1;
	unsigned short	tca__pad2;
};

enum {
	LKL_TCA_ROOT_UNSPEC,
	LKL_TCA_ROOT_TAB,
#define LKL_TCA_ACT_TAB LKL_TCA_ROOT_TAB
#define LKL_TCAA_MAX LKL_TCA_ROOT_TAB
	LKL_TCA_ROOT_FLAGS,
	LKL_TCA_ROOT_COUNT,
	LKL_TCA_ROOT_TIME_DELTA, /* in msecs */
	__LKL__TCA_ROOT_MAX,
#define	LKL_TCA_ROOT_MAX (__LKL__TCA_ROOT_MAX - 1)
};

#define LKL_TA_RTA(r)  ((struct lkl_rtattr*)(((char*)(r)) + LKL_NLMSG_ALIGN(sizeof(struct lkl_tcamsg))))
#define LKL_TA_PAYLOAD(n) LKL_NLMSG_PAYLOAD(n,sizeof(struct lkl_tcamsg))
/* tcamsg flags stored in attribute LKL_TCA_ROOT_FLAGS
 *
 * LKL_TCA_FLAG_LARGE_DUMP_ON user->kernel to request for larger than TCA_ACT_MAX_PRIO
 * actions in a dump. All dump responses will contain the number of actions
 * being dumped stored in for user app's consumption in LKL_TCA_ROOT_COUNT
 *
 */
#define LKL_TCA_FLAG_LARGE_DUMP_ON		(1 << 0)

/* New extended info filters for LKL_IFLA_EXT_MASK */
#define LKL_RTEXT_FILTER_VF		(1 << 0)
#define LKL_RTEXT_FILTER_BRVLAN	(1 << 1)
#define LKL_RTEXT_FILTER_BRVLAN_COMPRESSED	(1 << 2)
#define	LKL_RTEXT_FILTER_SKIP_STATS	(1 << 3)

/* End of information exported to user level */



#endif /* __LKL__LINUX_RTNETLINK_H */
