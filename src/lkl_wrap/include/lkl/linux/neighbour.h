/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__LINUX_NEIGHBOUR_H
#define __LKL__LINUX_NEIGHBOUR_H

#include <lkl/linux/types.h>
#include <lkl/linux/netlink.h>

struct lkl_ndmsg {
	__lkl__u8		ndm_family;
	__lkl__u8		ndm_pad1;
	__lkl__u16		ndm_pad2;
	__lkl__s32		ndm_ifindex;
	__lkl__u16		ndm_state;
	__lkl__u8		ndm_flags;
	__lkl__u8		ndm_type;
};

enum {
	LKL_NDA_UNSPEC,
	LKL_NDA_DST,
	LKL_NDA_LLADDR,
	LKL_NDA_CACHEINFO,
	LKL_NDA_PROBES,
	LKL_NDA_VLAN,
	LKL_NDA_PORT,
	LKL_NDA_VNI,
	LKL_NDA_IFINDEX,
	LKL_NDA_MASTER,
	LKL_NDA_LINK_NETNSID,
	LKL_NDA_SRC_VNI,
	__LKL__NDA_MAX
};

#define LKL_NDA_MAX (__LKL__NDA_MAX - 1)

/*
 *	Neighbor Cache Entry Flags
 */

#define LKL_NTF_USE		0x01
#define LKL_NTF_SELF	0x02
#define LKL_NTF_MASTER	0x04
#define LKL_NTF_PROXY	0x08	/* == ATF_PUBL */
#define LKL_NTF_EXT_LEARNED	0x10
#define LKL_NTF_OFFLOADED   0x20
#define LKL_NTF_ROUTER	0x80

/*
 *	Neighbor Cache Entry States.
 */

#define LKL_NUD_INCOMPLETE	0x01
#define LKL_NUD_REACHABLE	0x02
#define LKL_NUD_STALE	0x04
#define LKL_NUD_DELAY	0x08
#define LKL_NUD_PROBE	0x10
#define LKL_NUD_FAILED	0x20

/* Dummy states */
#define LKL_NUD_NOARP	0x40
#define LKL_NUD_PERMANENT	0x80
#define LKL_NUD_NONE	0x00

/* LKL_NUD_NOARP & LKL_NUD_PERMANENT are pseudostates, they never change
   and make no address resolution or NUD.
   LKL_NUD_PERMANENT also cannot be deleted by garbage collectors.
 */

struct lkl_nda_cacheinfo {
	__lkl__u32		ndm_confirmed;
	__lkl__u32		ndm_used;
	__lkl__u32		ndm_updated;
	__lkl__u32		ndm_refcnt;
};

/*****************************************************************
 *		Neighbour tables specific messages.
 *
 * To retrieve the neighbour tables send LKL_RTM_GETNEIGHTBL with the
 * LKL_NLM_F_DUMP flag set. Every neighbour table configuration is
 * spread over multiple messages to avoid running into message
 * size limits on systems with many interfaces. The first message
 * in the sequence transports all not device specific data such as
 * statistics, configuration, and the default parameter set.
 * This message is followed by 0..n messages carrying device
 * specific parameter sets.
 * Although the ordering should be sufficient, LKL_NDTA_NAME can be
 * used to identify sequences. The initial message can be identified
 * by checking for LKL_NDTA_CONFIG. The device specific messages do
 * not contain this TLV but have LKL_NDTPA_IFINDEX set to the
 * corresponding interface index.
 *
 * To change neighbour table attributes, send LKL_RTM_SETNEIGHTBL
 * with LKL_NDTA_NAME set. Changeable attribute include NDTA_THRESH[1-3],
 * LKL_NDTA_GC_INTERVAL, and all TLVs in LKL_NDTA_PARMS unless marked
 * otherwise. Device specific parameter sets can be changed by
 * setting LKL_NDTPA_IFINDEX to the interface index of the corresponding
 * device.
 ****/

struct lkl_ndt_stats {
	__lkl__u64		ndts_allocs;
	__lkl__u64		ndts_destroys;
	__lkl__u64		ndts_hash_grows;
	__lkl__u64		ndts_res_failed;
	__lkl__u64		ndts_lookups;
	__lkl__u64		ndts_hits;
	__lkl__u64		ndts_rcv_probes_mcast;
	__lkl__u64		ndts_rcv_probes_ucast;
	__lkl__u64		ndts_periodic_gc_runs;
	__lkl__u64		ndts_forced_gc_runs;
	__lkl__u64		ndts_table_fulls;
};

enum {
	LKL_NDTPA_UNSPEC,
	LKL_NDTPA_IFINDEX,			/* lkl_u32, unchangeable */
	LKL_NDTPA_REFCNT,			/* lkl_u32, read-only */
	LKL_NDTPA_REACHABLE_TIME,		/* lkl_u64, read-only, msecs */
	LKL_NDTPA_BASE_REACHABLE_TIME,	/* lkl_u64, msecs */
	LKL_NDTPA_RETRANS_TIME,		/* lkl_u64, msecs */
	LKL_NDTPA_GC_STALETIME,		/* lkl_u64, msecs */
	LKL_NDTPA_DELAY_PROBE_TIME,		/* lkl_u64, msecs */
	LKL_NDTPA_QUEUE_LEN,		/* lkl_u32 */
	LKL_NDTPA_APP_PROBES,		/* lkl_u32 */
	LKL_NDTPA_UCAST_PROBES,		/* lkl_u32 */
	LKL_NDTPA_MCAST_PROBES,		/* lkl_u32 */
	LKL_NDTPA_ANYCAST_DELAY,		/* lkl_u64, msecs */
	LKL_NDTPA_PROXY_DELAY,		/* lkl_u64, msecs */
	LKL_NDTPA_PROXY_QLEN,		/* lkl_u32 */
	LKL_NDTPA_LOCKTIME,			/* lkl_u64, msecs */
	LKL_NDTPA_QUEUE_LENBYTES,		/* lkl_u32 */
	LKL_NDTPA_MCAST_REPROBES,		/* lkl_u32 */
	LKL_NDTPA_PAD,
	__LKL__NDTPA_MAX
};
#define LKL_NDTPA_MAX (__LKL__NDTPA_MAX - 1)

struct lkl_ndtmsg {
	__lkl__u8		ndtm_family;
	__lkl__u8		ndtm_pad1;
	__lkl__u16		ndtm_pad2;
};

struct lkl_ndt_config {
	__lkl__u16		ndtc_key_len;
	__lkl__u16		ndtc_entry_size;
	__lkl__u32		ndtc_entries;
	__lkl__u32		ndtc_last_flush;	/* delta to now in msecs */
	__lkl__u32		ndtc_last_rand;		/* delta to now in msecs */
	__lkl__u32		ndtc_hash_rnd;
	__lkl__u32		ndtc_hash_mask;
	__lkl__u32		ndtc_hash_chain_gc;
	__lkl__u32		ndtc_proxy_qlen;
};

enum {
	LKL_NDTA_UNSPEC,
	LKL_NDTA_NAME,			/* char *, unchangeable */
	LKL_NDTA_THRESH1,			/* lkl_u32 */
	LKL_NDTA_THRESH2,			/* lkl_u32 */
	LKL_NDTA_THRESH3,			/* lkl_u32 */
	LKL_NDTA_CONFIG,			/* struct lkl_ndt_config, read-only */
	LKL_NDTA_PARMS,			/* nested TLV NDTPA_* */
	LKL_NDTA_STATS,			/* struct lkl_ndt_stats, read-only */
	LKL_NDTA_GC_INTERVAL,		/* lkl_u64, msecs */
	LKL_NDTA_PAD,
	__LKL__NDTA_MAX
};
#define LKL_NDTA_MAX (__LKL__NDTA_MAX - 1)

#endif
