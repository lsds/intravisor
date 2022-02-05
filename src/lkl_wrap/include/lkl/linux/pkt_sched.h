/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__LINUX_PKT_SCHED_H
#define __LKL__LINUX_PKT_SCHED_H

#include <lkl/linux/types.h>

/* Logical priority bands not depending on specific packet scheduler.
   Every scheduler will map them to real traffic classes, if it has
   no more precise mechanism to classify packets.

   These numbers have no special meaning, though their coincidence
   with obsolete IPv6 values is not occasional :-). New IPv6 drafts
   preferred full anarchy inspired by diffserv group.

   Note: LKL_TC_PRIO_BESTEFFORT does not mean that it is the most unhappy
   class, actually, as rule it will be handled with more care than
   filler or even bulk.
 */

#define LKL_TC_PRIO_BESTEFFORT		0
#define LKL_TC_PRIO_FILLER			1
#define LKL_TC_PRIO_BULK			2
#define LKL_TC_PRIO_INTERACTIVE_BULK	4
#define LKL_TC_PRIO_INTERACTIVE		6
#define LKL_TC_PRIO_CONTROL			7

#define LKL_TC_PRIO_MAX			15

/* Generic queue statistics, available for all the elements.
   Particular schedulers may have also their private records.
 */

struct lkl_tc_stats {
	__lkl__u64	bytes;			/* Number of enqueued bytes */
	__lkl__u32	packets;		/* Number of enqueued packets	*/
	__lkl__u32	drops;			/* Packets dropped because of lack of resources */
	__lkl__u32	overlimits;		/* Number of throttle events when this
					 * flow goes out of allocated bandwidth */
	__lkl__u32	bps;			/* Current flow byte rate */
	__lkl__u32	pps;			/* Current flow packet rate */
	__lkl__u32	qlen;
	__lkl__u32	backlog;
};

struct lkl_tc_estimator {
	signed char	interval;
	unsigned char	ewma_log;
};

/* "Handles"
   ---------

    All the traffic control objects have 32bit identifiers, or "handles".

    They can be considered as opaque numbers from user API viewpoint,
    but actually they always consist of two fields: major and
    minor numbers, which are interpreted by kernel specially,
    that may be used by applications, though not recommended.

    F.e. qdisc handles always have minor number equal to zero,
    classes (or flows) have major equal to parent qdisc major, and
    minor uniquely identifying class inside qdisc.

    Macros to manipulate handles:
 */

#define LKL_TC_H_MAJ_MASK (0xFFFF0000U)
#define LKL_TC_H_MIN_MASK (0x0000FFFFU)
#define LKL_TC_H_MAJ(h) ((h)&LKL_TC_H_MAJ_MASK)
#define LKL_TC_H_MIN(h) ((h)&LKL_TC_H_MIN_MASK)
#define LKL_TC_H_MAKE(maj,min) (((maj)&LKL_TC_H_MAJ_MASK)|((min)&LKL_TC_H_MIN_MASK))

#define LKL_TC_H_UNSPEC	(0U)
#define LKL_TC_H_ROOT	(0xFFFFFFFFU)
#define LKL_TC_H_INGRESS    (0xFFFFFFF1U)
#define LKL_TC_H_CLSACT	LKL_TC_H_INGRESS

#define LKL_TC_H_MIN_PRIORITY	0xFFE0U
#define LKL_TC_H_MIN_INGRESS	0xFFF2U
#define LKL_TC_H_MIN_EGRESS		0xFFF3U

/* Need to corrospond to iproute2 tc/tc_core.h "enum link_layer" */
enum lkl_tc_link_layer {
	LKL_TC_LINKLAYER_UNAWARE, /* Indicate unaware old iproute2 util */
	LKL_TC_LINKLAYER_ETHERNET,
	LKL_TC_LINKLAYER_ATM,
};
#define LKL_TC_LINKLAYER_MASK 0x0F /* limit use to lower 4 bits */

struct lkl_tc_ratespec {
	unsigned char	cell_log;
	__lkl__u8		linklayer; /* lower 4 bits */
	unsigned short	overhead;
	short		cell_align;
	unsigned short	mpu;
	__lkl__u32		rate;
};

#define LKL_TC_RTAB_SIZE	1024

struct lkl_tc_sizespec {
	unsigned char	cell_log;
	unsigned char	size_log;
	short		cell_align;
	int		overhead;
	unsigned int	linklayer;
	unsigned int	mpu;
	unsigned int	mtu;
	unsigned int	tsize;
};

enum {
	LKL_TCA_STAB_UNSPEC,
	LKL_TCA_STAB_BASE,
	LKL_TCA_STAB_DATA,
	__LKL__TCA_STAB_MAX
};

#define LKL_TCA_STAB_MAX (__LKL__TCA_STAB_MAX - 1)

/* FIFO section */

struct lkl_tc_fifo_qopt {
	__lkl__u32	limit;	/* Queue length: bytes for bfifo, packets for pfifo */
};

/* PRIO section */

#define LKL_TCQ_PRIO_BANDS	16
#define LKL_TCQ_MIN_PRIO_BANDS 2

struct lkl_tc_prio_qopt {
	int	bands;			/* Number of bands */
	__lkl__u8	priomap[LKL_TC_PRIO_MAX+1];	/* Map: logical priority -> PRIO band */
};

/* MULTIQ section */

struct lkl_tc_multiq_qopt {
	__lkl__u16	bands;			/* Number of bands */
	__lkl__u16	max_bands;		/* Maximum number of queues */
};

/* PLUG section */

#define LKL_TCQ_PLUG_BUFFER                0
#define LKL_TCQ_PLUG_RELEASE_ONE           1
#define LKL_TCQ_PLUG_RELEASE_INDEFINITE    2
#define LKL_TCQ_PLUG_LIMIT                 3

struct lkl_tc_plug_qopt {
	/* LKL_TCQ_PLUG_BUFFER: Inset a plug into the queue and
	 *  buffer any incoming packets
	 * LKL_TCQ_PLUG_RELEASE_ONE: Dequeue packets from queue head
	 *   to beginning of the next plug.
	 * LKL_TCQ_PLUG_RELEASE_INDEFINITE: Dequeue all packets from queue.
	 *   Stop buffering packets until the next LKL_TCQ_PLUG_BUFFER
	 *   command is received (just act as a pass-thru queue).
	 * LKL_TCQ_PLUG_LIMIT: Increase/decrease queue size
	 */
	int             action;
	__lkl__u32           limit;
};

/* TBF section */

struct lkl_tc_tbf_qopt {
	struct lkl_tc_ratespec rate;
	struct lkl_tc_ratespec peakrate;
	__lkl__u32		limit;
	__lkl__u32		buffer;
	__lkl__u32		mtu;
};

enum {
	LKL_TCA_TBF_UNSPEC,
	LKL_TCA_TBF_PARMS,
	LKL_TCA_TBF_RTAB,
	LKL_TCA_TBF_PTAB,
	LKL_TCA_TBF_RATE64,
	LKL_TCA_TBF_PRATE64,
	LKL_TCA_TBF_BURST,
	LKL_TCA_TBF_PBURST,
	LKL_TCA_TBF_PAD,
	__LKL__TCA_TBF_MAX,
};

#define LKL_TCA_TBF_MAX (__LKL__TCA_TBF_MAX - 1)


/* TEQL section */

/* TEQL does not require any parameters */

/* SFQ section */

struct lkl_tc_sfq_qopt {
	unsigned	quantum;	/* Bytes per round allocated to flow */
	int		perturb_period;	/* Period of hash perturbation */
	__lkl__u32		limit;		/* Maximal packets in queue */
	unsigned	divisor;	/* Hash divisor  */
	unsigned	flows;		/* Maximal number of flows  */
};

struct lkl_tc_sfqred_stats {
	__lkl__u32           prob_drop;      /* Early drops, below max threshold */
	__lkl__u32           forced_drop;	/* Early drops, after max threshold */
	__lkl__u32           prob_mark;      /* Marked packets, below max threshold */
	__lkl__u32           forced_mark;    /* Marked packets, after max threshold */
	__lkl__u32           prob_mark_head; /* Marked packets, below max threshold */
	__lkl__u32           forced_mark_head;/* Marked packets, after max threshold */
};

struct lkl_tc_sfq_qopt_v1 {
	struct lkl_tc_sfq_qopt v0;
	unsigned int	depth;		/* max number of packets per flow */
	unsigned int	headdrop;
/* SFQRED parameters */
	__lkl__u32		limit;		/* HARD maximal flow queue length (bytes) */
	__lkl__u32		qth_min;	/* Min average length threshold (bytes) */
	__lkl__u32		qth_max;	/* Max average length threshold (bytes) */
	unsigned char   Wlog;		/* log(W)		*/
	unsigned char   Plog;		/* log(P_max/(qth_max-qth_min))	*/
	unsigned char   Scell_log;	/* cell size for idle damping */
	unsigned char	flags;
	__lkl__u32		max_P;		/* probability, high resolution */
/* SFQRED stats */
	struct lkl_tc_sfqred_stats stats;
};


struct lkl_tc_sfq_xstats {
	__lkl__s32		allot;
};

/* RED section */

enum {
	LKL_TCA_RED_UNSPEC,
	LKL_TCA_RED_PARMS,
	LKL_TCA_RED_STAB,
	LKL_TCA_RED_MAX_P,
	__LKL__TCA_RED_MAX,
};

#define LKL_TCA_RED_MAX (__LKL__TCA_RED_MAX - 1)

struct lkl_tc_red_qopt {
	__lkl__u32		limit;		/* HARD maximal queue length (bytes)	*/
	__lkl__u32		qth_min;	/* Min average length threshold (bytes) */
	__lkl__u32		qth_max;	/* Max average length threshold (bytes) */
	unsigned char   Wlog;		/* log(W)		*/
	unsigned char   Plog;		/* log(P_max/(qth_max-qth_min))	*/
	unsigned char   Scell_log;	/* cell size for idle damping */
	unsigned char	flags;
#define LKL_TC_RED_ECN		1
#define LKL_TC_RED_HARDDROP		2
#define LKL_TC_RED_ADAPTATIVE	4
};

struct lkl_tc_red_xstats {
	__lkl__u32           early;          /* Early drops */
	__lkl__u32           pdrop;          /* Drops due to queue limits */
	__lkl__u32           other;          /* Drops due to drop() calls */
	__lkl__u32           marked;         /* Marked packets */
};

/* GRED section */

#define lkl_MAX_DPs 16

enum {
       LKL_TCA_GRED_UNSPEC,
       LKL_TCA_GRED_PARMS,
       LKL_TCA_GRED_STAB,
       LKL_TCA_GRED_DPS,
       LKL_TCA_GRED_MAX_P,
       LKL_TCA_GRED_LIMIT,
       __LKL__TCA_GRED_MAX,
};

#define LKL_TCA_GRED_MAX (__LKL__TCA_GRED_MAX - 1)

struct lkl_tc_gred_qopt {
	__lkl__u32		limit;        /* HARD maximal queue length (bytes)    */
	__lkl__u32		qth_min;      /* Min average length threshold (bytes) */
	__lkl__u32		qth_max;      /* Max average length threshold (bytes) */
	__lkl__u32		DP;           /* up to 2^32 DPs */
	__lkl__u32		backlog;
	__lkl__u32		qave;
	__lkl__u32		forced;
	__lkl__u32		early;
	__lkl__u32		other;
	__lkl__u32		pdrop;
	__lkl__u8		Wlog;         /* log(W)               */
	__lkl__u8		Plog;         /* log(P_max/(qth_max-qth_min)) */
	__lkl__u8		Scell_log;    /* cell size for idle damping */
	__lkl__u8		prio;         /* prio of this VQ */
	__lkl__u32		packets;
	__lkl__u32		bytesin;
};

/* gred setup */
struct lkl_tc_gred_sopt {
	__lkl__u32		DPs;
	__lkl__u32		def_DP;
	__lkl__u8		grio;
	__lkl__u8		flags;
	__lkl__u16		pad1;
};

/* CHOKe section */

enum {
	LKL_TCA_CHOKE_UNSPEC,
	LKL_TCA_CHOKE_PARMS,
	LKL_TCA_CHOKE_STAB,
	LKL_TCA_CHOKE_MAX_P,
	__LKL__TCA_CHOKE_MAX,
};

#define LKL_TCA_CHOKE_MAX (__LKL__TCA_CHOKE_MAX - 1)

struct lkl_tc_choke_qopt {
	__lkl__u32		limit;		/* Hard queue length (packets)	*/
	__lkl__u32		qth_min;	/* Min average threshold (packets) */
	__lkl__u32		qth_max;	/* Max average threshold (packets) */
	unsigned char   Wlog;		/* log(W)		*/
	unsigned char   Plog;		/* log(P_max/(qth_max-qth_min))	*/
	unsigned char   Scell_log;	/* cell size for idle damping */
	unsigned char	flags;		/* see RED flags */
};

struct lkl_tc_choke_xstats {
	__lkl__u32		early;          /* Early drops */
	__lkl__u32		pdrop;          /* Drops due to queue limits */
	__lkl__u32		other;          /* Drops due to drop() calls */
	__lkl__u32		marked;         /* Marked packets */
	__lkl__u32		matched;	/* Drops due to flow match */
};

/* HTB section */
#define LKL_TC_HTB_NUMPRIO		8
#define LKL_TC_HTB_MAXDEPTH		8
#define LKL_TC_HTB_PROTOVER		3 /* the same as HTB and TC's major */

struct lkl_tc_htb_opt {
	struct lkl_tc_ratespec 	rate;
	struct lkl_tc_ratespec 	ceil;
	__lkl__u32	buffer;
	__lkl__u32	cbuffer;
	__lkl__u32	quantum;
	__lkl__u32	level;		/* out only */
	__lkl__u32	prio;
};
struct lkl_tc_htb_glob {
	__lkl__u32 version;		/* to match HTB/TC */
    	__lkl__u32 rate2quantum;	/* bps->quantum divisor */
    	__lkl__u32 defcls;		/* default class number */
	__lkl__u32 debug;		/* debug flags */

	/* stats */
	__lkl__u32 direct_pkts; /* count of non shaped packets */
};
enum {
	LKL_TCA_HTB_UNSPEC,
	LKL_TCA_HTB_PARMS,
	LKL_TCA_HTB_INIT,
	LKL_TCA_HTB_CTAB,
	LKL_TCA_HTB_RTAB,
	LKL_TCA_HTB_DIRECT_QLEN,
	LKL_TCA_HTB_RATE64,
	LKL_TCA_HTB_CEIL64,
	LKL_TCA_HTB_PAD,
	__LKL__TCA_HTB_MAX,
};

#define LKL_TCA_HTB_MAX (__LKL__TCA_HTB_MAX - 1)

struct lkl_tc_htb_xstats {
	__lkl__u32 lends;
	__lkl__u32 borrows;
	__lkl__u32 giants;	/* too big packets (rate will not be accurate) */
	__lkl__u32 tokens;
	__lkl__u32 ctokens;
};

/* HFSC section */

struct lkl_tc_hfsc_qopt {
	__lkl__u16	defcls;		/* default class */
};

struct lkl_tc_service_curve {
	__lkl__u32	m1;		/* slope of the first segment in bps */
	__lkl__u32	d;		/* x-projection of the first segment in us */
	__lkl__u32	m2;		/* slope of the second segment in bps */
};

struct lkl_tc_hfsc_stats {
	__lkl__u64	work;		/* total work done */
	__lkl__u64	rtwork;		/* work done by real-time criteria */
	__lkl__u32	period;		/* current period */
	__lkl__u32	level;		/* class level in hierarchy */
};

enum {
	LKL_TCA_HFSC_UNSPEC,
	LKL_TCA_HFSC_RSC,
	LKL_TCA_HFSC_FSC,
	LKL_TCA_HFSC_USC,
	__LKL__TCA_HFSC_MAX,
};

#define LKL_TCA_HFSC_MAX (__LKL__TCA_HFSC_MAX - 1)


/* CBQ section */

#define LKL_TC_CBQ_MAXPRIO		8
#define LKL_TC_CBQ_MAXLEVEL		8
#define LKL_TC_CBQ_DEF_EWMA		5

struct lkl_tc_cbq_lssopt {
	unsigned char	change;
	unsigned char	flags;
#define LKL_TCF_CBQ_LSS_BOUNDED	1
#define LKL_TCF_CBQ_LSS_ISOLATED	2
	unsigned char  	ewma_log;
	unsigned char  	level;
#define LKL_TCF_CBQ_LSS_FLAGS	1
#define LKL_TCF_CBQ_LSS_EWMA	2
#define LKL_TCF_CBQ_LSS_MAXIDLE	4
#define LKL_TCF_CBQ_LSS_MINIDLE	8
#define LKL_TCF_CBQ_LSS_OFFTIME	0x10
#define LKL_TCF_CBQ_LSS_AVPKT	0x20
	__lkl__u32		maxidle;
	__lkl__u32		minidle;
	__lkl__u32		offtime;
	__lkl__u32		avpkt;
};

struct lkl_tc_cbq_wrropt {
	unsigned char	flags;
	unsigned char	priority;
	unsigned char	cpriority;
	unsigned char	__reserved;
	__lkl__u32		allot;
	__lkl__u32		weight;
};

struct lkl_tc_cbq_ovl {
	unsigned char	strategy;
#define	LKL_TC_CBQ_OVL_CLASSIC	0
#define	LKL_TC_CBQ_OVL_DELAY	1
#define	LKL_TC_CBQ_OVL_LOWPRIO	2
#define	LKL_TC_CBQ_OVL_DROP		3
#define	LKL_TC_CBQ_OVL_RCLASSIC	4
	unsigned char	priority2;
	__lkl__u16		pad;
	__lkl__u32		penalty;
};

struct lkl_tc_cbq_police {
	unsigned char	police;
	unsigned char	__res1;
	unsigned short	__res2;
};

struct lkl_tc_cbq_fopt {
	__lkl__u32		split;
	__lkl__u32		defmap;
	__lkl__u32		defchange;
};

struct lkl_tc_cbq_xstats {
	__lkl__u32		borrows;
	__lkl__u32		overactions;
	__lkl__s32		avgidle;
	__lkl__s32		undertime;
};

enum {
	LKL_TCA_CBQ_UNSPEC,
	LKL_TCA_CBQ_LSSOPT,
	LKL_TCA_CBQ_WRROPT,
	LKL_TCA_CBQ_FOPT,
	LKL_TCA_CBQ_OVL_STRATEGY,
	LKL_TCA_CBQ_RATE,
	LKL_TCA_CBQ_RTAB,
	LKL_TCA_CBQ_POLICE,
	__LKL__TCA_CBQ_MAX,
};

#define LKL_TCA_CBQ_MAX	(__LKL__TCA_CBQ_MAX - 1)

/* dsmark section */

enum {
	LKL_TCA_DSMARK_UNSPEC,
	LKL_TCA_DSMARK_INDICES,
	LKL_TCA_DSMARK_DEFAULT_INDEX,
	LKL_TCA_DSMARK_SET_TC_INDEX,
	LKL_TCA_DSMARK_MASK,
	LKL_TCA_DSMARK_VALUE,
	__LKL__TCA_DSMARK_MAX,
};

#define LKL_TCA_DSMARK_MAX (__LKL__TCA_DSMARK_MAX - 1)

/* ATM  section */

enum {
	LKL_TCA_ATM_UNSPEC,
	LKL_TCA_ATM_FD,		/* file/socket descriptor */
	LKL_TCA_ATM_PTR,		/* pointer to descriptor - later */
	LKL_TCA_ATM_HDR,		/* LL header */
	LKL_TCA_ATM_EXCESS,		/* excess traffic class (0 for CLP)  */
	LKL_TCA_ATM_ADDR,		/* PVC address (for output only) */
	LKL_TCA_ATM_STATE,		/* VC state (ATM_VS_*; for output only) */
	__LKL__TCA_ATM_MAX,
};

#define LKL_TCA_ATM_MAX	(__LKL__TCA_ATM_MAX - 1)

/* Network emulator */

enum {
	LKL_TCA_NETEM_UNSPEC,
	LKL_TCA_NETEM_CORR,
	LKL_TCA_NETEM_DELAY_DIST,
	LKL_TCA_NETEM_REORDER,
	LKL_TCA_NETEM_CORRUPT,
	LKL_TCA_NETEM_LOSS,
	LKL_TCA_NETEM_RATE,
	LKL_TCA_NETEM_ECN,
	LKL_TCA_NETEM_RATE64,
	LKL_TCA_NETEM_PAD,
	LKL_TCA_NETEM_LATENCY64,
	LKL_TCA_NETEM_JITTER64,
	LKL_TCA_NETEM_SLOT,
	__LKL__TCA_NETEM_MAX,
};

#define LKL_TCA_NETEM_MAX (__LKL__TCA_NETEM_MAX - 1)

struct lkl_tc_netem_qopt {
	__lkl__u32	latency;	/* added delay (us) */
	__lkl__u32   limit;		/* fifo limit (packets) */
	__lkl__u32	loss;		/* random packet loss (0=none ~0=100%) */
	__lkl__u32	gap;		/* re-ordering gap (0 for none) */
	__lkl__u32   duplicate;	/* random packet dup  (0=none ~0=100%) */
	__lkl__u32	jitter;		/* random jitter in latency (us) */
};

struct lkl_tc_netem_corr {
	__lkl__u32	delay_corr;	/* delay correlation */
	__lkl__u32	loss_corr;	/* packet loss correlation */
	__lkl__u32	dup_corr;	/* duplicate correlation  */
};

struct lkl_tc_netem_reorder {
	__lkl__u32	probability;
	__lkl__u32	correlation;
};

struct lkl_tc_netem_corrupt {
	__lkl__u32	probability;
	__lkl__u32	correlation;
};

struct lkl_tc_netem_rate {
	__lkl__u32	rate;	/* byte/s */
	__lkl__s32	packet_overhead;
	__lkl__u32	cell_size;
	__lkl__s32	cell_overhead;
};

struct lkl_tc_netem_slot {
	__lkl__s64   min_delay; /* nsec */
	__lkl__s64   max_delay;
	__lkl__s32   max_packets;
	__lkl__s32   max_bytes;
};

enum {
	LKL_NETEM_LOSS_UNSPEC,
	LKL_NETEM_LOSS_GI,		/* General Intuitive - 4 state model */
	LKL_NETEM_LOSS_GE,		/* Gilbert Elliot models */
	__LKL__NETEM_LOSS_MAX
};
#define LKL_NETEM_LOSS_MAX (__LKL__NETEM_LOSS_MAX - 1)

/* State transition probabilities for 4 state model */
struct lkl_tc_netem_gimodel {
	__lkl__u32	p13;
	__lkl__u32	p31;
	__lkl__u32	p32;
	__lkl__u32	p14;
	__lkl__u32	p23;
};

/* Gilbert-Elliot models */
struct lkl_tc_netem_gemodel {
	__lkl__u32 p;
	__lkl__u32 r;
	__lkl__u32 h;
	__lkl__u32 k1;
};

#define LKL_NETEM_DIST_SCALE	8192
#define LKL_NETEM_DIST_MAX		16384

/* DRR */

enum {
	LKL_TCA_DRR_UNSPEC,
	LKL_TCA_DRR_QUANTUM,
	__LKL__TCA_DRR_MAX
};

#define LKL_TCA_DRR_MAX	(__LKL__TCA_DRR_MAX - 1)

struct lkl_tc_drr_stats {
	__lkl__u32	deficit;
};

/* MQPRIO */
#define LKL_TC_QOPT_BITMASK 15
#define LKL_TC_QOPT_MAX_QUEUE 16

enum {
	LKL_TC_MQPRIO_HW_OFFLOAD_NONE,	/* no offload requested */
	LKL_TC_MQPRIO_HW_OFFLOAD_TCS,	/* offload TCs, no queue counts */
	__LKL__TC_MQPRIO_HW_OFFLOAD_MAX
};

#define LKL_TC_MQPRIO_HW_OFFLOAD_MAX (__LKL__TC_MQPRIO_HW_OFFLOAD_MAX - 1)

enum {
	LKL_TC_MQPRIO_MODE_DCB,
	LKL_TC_MQPRIO_MODE_CHANNEL,
	__LKL__TC_MQPRIO_MODE_MAX
};

#define __LKL__TC_MQPRIO_MODE_MAX (__LKL__TC_MQPRIO_MODE_MAX - 1)

enum {
	LKL_TC_MQPRIO_SHAPER_DCB,
	LKL_TC_MQPRIO_SHAPER_BW_RATE,	/* Add new shapers below */
	__LKL__TC_MQPRIO_SHAPER_MAX
};

#define __LKL__TC_MQPRIO_SHAPER_MAX (__LKL__TC_MQPRIO_SHAPER_MAX - 1)

struct lkl_tc_mqprio_qopt {
	__lkl__u8	num_tc;
	__lkl__u8	prio_tc_map[LKL_TC_QOPT_BITMASK + 1];
	__lkl__u8	hw;
	__lkl__u16	count[LKL_TC_QOPT_MAX_QUEUE];
	__lkl__u16	offset[LKL_TC_QOPT_MAX_QUEUE];
};

#define LKL_TC_MQPRIO_F_MODE		0x1
#define LKL_TC_MQPRIO_F_SHAPER		0x2
#define LKL_TC_MQPRIO_F_MIN_RATE		0x4
#define LKL_TC_MQPRIO_F_MAX_RATE		0x8

enum {
	LKL_TCA_MQPRIO_UNSPEC,
	LKL_TCA_MQPRIO_MODE,
	LKL_TCA_MQPRIO_SHAPER,
	LKL_TCA_MQPRIO_MIN_RATE64,
	LKL_TCA_MQPRIO_MAX_RATE64,
	__LKL__TCA_MQPRIO_MAX,
};

#define LKL_TCA_MQPRIO_MAX (__LKL__TCA_MQPRIO_MAX - 1)

/* SFB */

enum {
	LKL_TCA_SFB_UNSPEC,
	LKL_TCA_SFB_PARMS,
	__LKL__TCA_SFB_MAX,
};

#define LKL_TCA_SFB_MAX (__LKL__TCA_SFB_MAX - 1)

/*
 * Note: increment, decrement are Q0.16 fixed-point values.
 */
struct lkl_tc_sfb_qopt {
	__lkl__u32 rehash_interval;	/* delay between hash move, in ms */
	__lkl__u32 warmup_time;	/* double buffering warmup time in ms (warmup_time < rehash_interval) */
	__lkl__u32 max;		/* max len of qlen_min */
	__lkl__u32 bin_size;		/* maximum queue length per bin */
	__lkl__u32 increment;	/* probability increment, (d1 in Blue) */
	__lkl__u32 decrement;	/* probability decrement, (d2 in Blue) */
	__lkl__u32 limit;		/* max SFB queue length */
	__lkl__u32 penalty_rate;	/* inelastic flows are rate limited to 'rate' pps */
	__lkl__u32 penalty_burst;
};

struct lkl_tc_sfb_xstats {
	__lkl__u32 earlydrop;
	__lkl__u32 penaltydrop;
	__lkl__u32 bucketdrop;
	__lkl__u32 queuedrop;
	__lkl__u32 childdrop; /* drops in child qdisc */
	__lkl__u32 marked;
	__lkl__u32 maxqlen;
	__lkl__u32 maxprob;
	__lkl__u32 avgprob;
};

#define LKL_SFB_MAX_PROB 0xFFFF

/* QFQ */
enum {
	LKL_TCA_QFQ_UNSPEC,
	LKL_TCA_QFQ_WEIGHT,
	LKL_TCA_QFQ_LMAX,
	__LKL__TCA_QFQ_MAX
};

#define LKL_TCA_QFQ_MAX	(__LKL__TCA_QFQ_MAX - 1)

struct lkl_tc_qfq_stats {
	__lkl__u32 weight;
	__lkl__u32 lmax;
};

/* CODEL */

enum {
	LKL_TCA_CODEL_UNSPEC,
	LKL_TCA_CODEL_TARGET,
	LKL_TCA_CODEL_LIMIT,
	LKL_TCA_CODEL_INTERVAL,
	LKL_TCA_CODEL_ECN,
	LKL_TCA_CODEL_CE_THRESHOLD,
	__LKL__TCA_CODEL_MAX
};

#define LKL_TCA_CODEL_MAX	(__LKL__TCA_CODEL_MAX - 1)

struct lkl_tc_codel_xstats {
	__lkl__u32	maxpacket; /* largest packet we've seen so far */
	__lkl__u32	count;	   /* how many drops we've done since the last time we
			    * entered dropping state
			    */
	__lkl__u32	lastcount; /* count at entry to dropping state */
	__lkl__u32	ldelay;    /* in-queue delay seen by most recently dequeued packet */
	__lkl__s32	drop_next; /* time to drop next packet */
	__lkl__u32	drop_overlimit; /* number of time max qdisc packet limit was hit */
	__lkl__u32	ecn_mark;  /* number of packets we ECN marked instead of dropped */
	__lkl__u32	dropping;  /* are we in dropping state ? */
	__lkl__u32	ce_mark;   /* number of CE marked packets because of ce_threshold */
};

/* FQ_CODEL */

enum {
	LKL_TCA_FQ_CODEL_UNSPEC,
	LKL_TCA_FQ_CODEL_TARGET,
	LKL_TCA_FQ_CODEL_LIMIT,
	LKL_TCA_FQ_CODEL_INTERVAL,
	LKL_TCA_FQ_CODEL_ECN,
	LKL_TCA_FQ_CODEL_FLOWS,
	LKL_TCA_FQ_CODEL_QUANTUM,
	LKL_TCA_FQ_CODEL_CE_THRESHOLD,
	LKL_TCA_FQ_CODEL_DROP_BATCH_SIZE,
	LKL_TCA_FQ_CODEL_MEMORY_LIMIT,
	__LKL__TCA_FQ_CODEL_MAX
};

#define LKL_TCA_FQ_CODEL_MAX	(__LKL__TCA_FQ_CODEL_MAX - 1)

enum {
	LKL_TCA_FQ_CODEL_XSTATS_QDISC,
	LKL_TCA_FQ_CODEL_XSTATS_CLASS,
};

struct lkl_tc_fq_codel_qd_stats {
	__lkl__u32	maxpacket;	/* largest packet we've seen so far */
	__lkl__u32	drop_overlimit; /* number of time max qdisc
				 * packet limit was hit
				 */
	__lkl__u32	ecn_mark;	/* number of packets we ECN marked
				 * instead of being dropped
				 */
	__lkl__u32	new_flow_count; /* number of time packets
				 * created a 'new flow'
				 */
	__lkl__u32	new_flows_len;	/* count of flows in new list */
	__lkl__u32	old_flows_len;	/* count of flows in old list */
	__lkl__u32	ce_mark;	/* packets above ce_threshold */
	__lkl__u32	memory_usage;	/* in bytes */
	__lkl__u32	drop_overmemory;
};

struct lkl_tc_fq_codel_cl_stats {
	__lkl__s32	deficit;
	__lkl__u32	ldelay;		/* in-queue delay seen by most recently
				 * dequeued packet
				 */
	__lkl__u32	count;
	__lkl__u32	lastcount;
	__lkl__u32	dropping;
	__lkl__s32	drop_next;
};

struct lkl_tc_fq_codel_xstats {
	__lkl__u32	type;
	union {
		struct lkl_tc_fq_codel_qd_stats qdisc_stats;
		struct lkl_tc_fq_codel_cl_stats class_stats;
	};
};

/* FQ */

enum {
	LKL_TCA_FQ_UNSPEC,

	LKL_TCA_FQ_PLIMIT,		/* limit of total number of packets in queue */

	LKL_TCA_FQ_FLOW_PLIMIT,	/* limit of packets per flow */

	LKL_TCA_FQ_QUANTUM,		/* RR quantum */

	LKL_TCA_FQ_INITIAL_QUANTUM,		/* RR quantum for new flow */

	LKL_TCA_FQ_RATE_ENABLE,	/* enable/disable rate limiting */

	LKL_TCA_FQ_FLOW_DEFAULT_RATE,/* obsolete, do not use */

	LKL_TCA_FQ_FLOW_MAX_RATE,	/* per flow max rate */

	LKL_TCA_FQ_BUCKETS_LOG,	/* log2(number of buckets) */

	LKL_TCA_FQ_FLOW_REFILL_DELAY,	/* flow credit refill delay in usec */

	LKL_TCA_FQ_ORPHAN_MASK,	/* mask applied to orphaned skb hashes */

	LKL_TCA_FQ_LOW_RATE_THRESHOLD, /* per packet delay under this rate */

	__LKL__TCA_FQ_MAX
};

#define LKL_TCA_FQ_MAX	(__LKL__TCA_FQ_MAX - 1)

struct lkl_tc_fq_qd_stats {
	__lkl__u64	gc_flows;
	__lkl__u64	highprio_packets;
	__lkl__u64	tcp_retrans;
	__lkl__u64	throttled;
	__lkl__u64	flows_plimit;
	__lkl__u64	pkts_too_long;
	__lkl__u64	allocation_errors;
	__lkl__s64	time_next_delayed_flow;
	__lkl__u32	flows;
	__lkl__u32	inactive_flows;
	__lkl__u32	throttled_flows;
	__lkl__u32	unthrottle_latency_ns;
};

/* Heavy-Hitter Filter */

enum {
	LKL_TCA_HHF_UNSPEC,
	LKL_TCA_HHF_BACKLOG_LIMIT,
	LKL_TCA_HHF_QUANTUM,
	LKL_TCA_HHF_HH_FLOWS_LIMIT,
	LKL_TCA_HHF_RESET_TIMEOUT,
	LKL_TCA_HHF_ADMIT_BYTES,
	LKL_TCA_HHF_EVICT_TIMEOUT,
	LKL_TCA_HHF_NON_HH_WEIGHT,
	__LKL__TCA_HHF_MAX
};

#define LKL_TCA_HHF_MAX	(__LKL__TCA_HHF_MAX - 1)

struct lkl_tc_hhf_xstats {
	__lkl__u32	drop_overlimit; /* number of times max qdisc packet limit
				 * was hit
				 */
	__lkl__u32	hh_overlimit;   /* number of times max heavy-hitters was hit */
	__lkl__u32	hh_tot_count;   /* number of captured heavy-hitters so far */
	__lkl__u32	hh_cur_count;   /* number of current heavy-hitters */
};

/* PIE */
enum {
	LKL_TCA_PIE_UNSPEC,
	LKL_TCA_PIE_TARGET,
	LKL_TCA_PIE_LIMIT,
	LKL_TCA_PIE_TUPDATE,
	LKL_TCA_PIE_ALPHA,
	LKL_TCA_PIE_BETA,
	LKL_TCA_PIE_ECN,
	LKL_TCA_PIE_BYTEMODE,
	__LKL__TCA_PIE_MAX
};
#define LKL_TCA_PIE_MAX   (__LKL__TCA_PIE_MAX - 1)

struct lkl_tc_pie_xstats {
	__lkl__u32 prob;             /* current probability */
	__lkl__u32 delay;            /* current delay in ms */
	__lkl__u32 avg_dq_rate;      /* current average dq_rate in bits/pie_time */
	__lkl__u32 packets_in;       /* total number of packets enqueued */
	__lkl__u32 dropped;          /* packets dropped due to pie_action */
	__lkl__u32 overlimit;        /* dropped due to lack of space in queue */
	__lkl__u32 maxq;             /* maximum queue size */
	__lkl__u32 ecn_mark;         /* packets marked with ecn*/
};

/* CBS */
struct lkl_tc_cbs_qopt {
	__lkl__u8 offload;
	__lkl__u8 _pad[3];
	__lkl__s32 hicredit;
	__lkl__s32 locredit;
	__lkl__s32 idleslope;
	__lkl__s32 sendslope;
};

enum {
	LKL_TCA_CBS_UNSPEC,
	LKL_TCA_CBS_PARMS,
	__LKL__TCA_CBS_MAX,
};

#define LKL_TCA_CBS_MAX (__LKL__TCA_CBS_MAX - 1)

#endif
