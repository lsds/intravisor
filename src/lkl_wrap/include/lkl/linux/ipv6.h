/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_IPV6_H
#define _LKL_IPV6_H

#include <lkl/linux/libc-compat.h>
#include <lkl/linux/types.h>
#include <lkl/linux/in6.h>
#include <lkl/asm/byteorder.h>

/* The latest drafts declared increase in minimal mtu up to 1280. */

#define LKL_IPV6_MIN_MTU	1280

/*
 *	Advanced API
 *	source interface/address selection, source routing, etc...
 *	*under construction*
 */

#if __LKL__UAPI_DEF_IN6_PKTINFO
struct lkl_in6_pktinfo {
	struct lkl_in6_addr	ipi6_addr;
	int		ipi6_ifindex;
};
#endif

#if __LKL__UAPI_DEF_IP6_MTUINFO
struct lkl_ip6_mtuinfo {
	struct lkl_sockaddr_in6	ip6m_addr;
	__lkl__u32			ip6m_mtu;
};
#endif

struct lkl_in6_ifreq {
	struct lkl_in6_addr	ifr6_addr;
	__lkl__u32		ifr6_prefixlen;
	int		ifr6_ifindex; 
};

#define LKL_IPV6_SRCRT_STRICT	0x01	/* Deprecated; will be removed */
#define LKL_IPV6_SRCRT_TYPE_0	0	/* Deprecated; will be removed */
#define LKL_IPV6_SRCRT_TYPE_2	2	/* IPv6 type 2 Routing Header	*/
#define LKL_IPV6_SRCRT_TYPE_4	4	/* Segment Routing with IPv6 */

/*
 *	routing header
 */
struct lkl_ipv6_rt_hdr {
	__lkl__u8		nexthdr;
	__lkl__u8		hdrlen;
	__lkl__u8		type;
	__lkl__u8		segments_left;

	/*
	 *	type specific data
	 *	variable length field
	 */
};


struct lkl_ipv6_opt_hdr {
	__lkl__u8 		nexthdr;
	__lkl__u8 		hdrlen;
	/* 
	 * TLV encoded option data follows.
	 */
} __attribute__((packed));	/* required for some archs */

#define lkl_ipv6_destopt_hdr ipv6_opt_hdr
#define lkl_ipv6_hopopt_hdr  ipv6_opt_hdr

/* Router Alert option values (RFC2711) */
#define LKL_IPV6_OPT_ROUTERALERT_MLD	0x0000	/* MLD(RFC2710) */

/*
 *	routing header type 0 (used in cmsghdr struct)
 */

struct lkl_rt0_hdr {
	struct lkl_ipv6_rt_hdr	rt_hdr;
	__lkl__u32			reserved;
	struct lkl_in6_addr		addr[0];

#define lkl_rt0_type		rt_hdr.type
};

/*
 *	routing header type 2
 */

struct lkl_rt2_hdr {
	struct lkl_ipv6_rt_hdr	rt_hdr;
	__lkl__u32			reserved;
	struct lkl_in6_addr		addr;

#define lkl_rt2_type		rt_hdr.type
};

/*
 *	home address option in destination options header
 */

struct lkl_ipv6_destopt_hao {
	__lkl__u8			type;
	__lkl__u8			length;
	struct lkl_in6_addr		addr;
} __attribute__((packed));

/*
 *	IPv6 fixed header
 *
 *	BEWARE, it is incorrect. The first 4 bits of flow_lbl
 *	are glued to priority now, forming "class".
 */

struct lkl_ipv6hdr {
#if defined(__LKL__LITTLE_ENDIAN_BITFIELD)
	__lkl__u8			priority:4,
				version:4;
#elif defined(__LKL__BIG_ENDIAN_BITFIELD)
	__lkl__u8			version:4,
				priority:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
	__lkl__u8			flow_lbl[3];

	__lkl__be16			payload_len;
	__lkl__u8			nexthdr;
	__lkl__u8			hop_limit;

	struct	lkl_in6_addr	saddr;
	struct	lkl_in6_addr	daddr;
};


/* index values for the variables in ipv6_devconf */
enum {
	LKL_DEVCONF_FORWARDING = 0,
	LKL_DEVCONF_HOPLIMIT,
	LKL_DEVCONF_MTU6,
	LKL_DEVCONF_ACCEPT_RA,
	LKL_DEVCONF_ACCEPT_REDIRECTS,
	LKL_DEVCONF_AUTOCONF,
	LKL_DEVCONF_DAD_TRANSMITS,
	LKL_DEVCONF_RTR_SOLICITS,
	LKL_DEVCONF_RTR_SOLICIT_INTERVAL,
	LKL_DEVCONF_RTR_SOLICIT_DELAY,
	LKL_DEVCONF_USE_TEMPADDR,
	LKL_DEVCONF_TEMP_VALID_LFT,
	LKL_DEVCONF_TEMP_PREFERED_LFT,
	LKL_DEVCONF_REGEN_MAX_RETRY,
	LKL_DEVCONF_MAX_DESYNC_FACTOR,
	LKL_DEVCONF_MAX_ADDRESSES,
	LKL_DEVCONF_FORCE_MLD_VERSION,
	LKL_DEVCONF_ACCEPT_RA_DEFRTR,
	LKL_DEVCONF_ACCEPT_RA_PINFO,
	LKL_DEVCONF_ACCEPT_RA_RTR_PREF,
	LKL_DEVCONF_RTR_PROBE_INTERVAL,
	LKL_DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN,
	LKL_DEVCONF_PROXY_NDP,
	LKL_DEVCONF_OPTIMISTIC_DAD,
	LKL_DEVCONF_ACCEPT_SOURCE_ROUTE,
	LKL_DEVCONF_MC_FORWARDING,
	LKL_DEVCONF_DISABLE_IPV6,
	LKL_DEVCONF_ACCEPT_DAD,
	LKL_DEVCONF_FORCE_TLLAO,
	LKL_DEVCONF_NDISC_NOTIFY,
	LKL_DEVCONF_MLDV1_UNSOLICITED_REPORT_INTERVAL,
	LKL_DEVCONF_MLDV2_UNSOLICITED_REPORT_INTERVAL,
	LKL_DEVCONF_SUPPRESS_FRAG_NDISC,
	LKL_DEVCONF_ACCEPT_RA_FROM_LOCAL,
	LKL_DEVCONF_USE_OPTIMISTIC,
	LKL_DEVCONF_ACCEPT_RA_MTU,
	LKL_DEVCONF_STABLE_SECRET,
	LKL_DEVCONF_USE_OIF_ADDRS_ONLY,
	LKL_DEVCONF_ACCEPT_RA_MIN_HOP_LIMIT,
	LKL_DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN,
	LKL_DEVCONF_DROP_UNICAST_IN_L2_MULTICAST,
	LKL_DEVCONF_DROP_UNSOLICITED_NA,
	LKL_DEVCONF_KEEP_ADDR_ON_DOWN,
	LKL_DEVCONF_RTR_SOLICIT_MAX_INTERVAL,
	LKL_DEVCONF_SEG6_ENABLED,
	LKL_DEVCONF_SEG6_REQUIRE_HMAC,
	LKL_DEVCONF_ENHANCED_DAD,
	LKL_DEVCONF_ADDR_GEN_MODE,
	LKL_DEVCONF_DISABLE_POLICY,
	LKL_DEVCONF_ACCEPT_RA_RT_INFO_MIN_PLEN,
	LKL_DEVCONF_NDISC_TCLASS,
	LKL_DEVCONF_MAX
};


#endif /* _LKL_IPV6_H */
