/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_IF_LINK_H
#define _LKL_LINUX_IF_LINK_H

#include <lkl/linux/types.h>
#include <lkl/linux/netlink.h>

/* This struct should be in sync with struct lkl_rtnl_link_stats64 */
struct lkl_rtnl_link_stats {
	__lkl__u32	rx_packets;
	__lkl__u32	tx_packets;
	__lkl__u32	rx_bytes;
	__lkl__u32	tx_bytes;
	__lkl__u32	rx_errors;
	__lkl__u32	tx_errors;
	__lkl__u32	rx_dropped;
	__lkl__u32	tx_dropped;
	__lkl__u32	multicast;
	__lkl__u32	collisions;
	/* detailed rx_errors: */
	__lkl__u32	rx_length_errors;
	__lkl__u32	rx_over_errors;
	__lkl__u32	rx_crc_errors;
	__lkl__u32	rx_frame_errors;
	__lkl__u32	rx_fifo_errors;
	__lkl__u32	rx_missed_errors;

	/* detailed tx_errors */
	__lkl__u32	tx_aborted_errors;
	__lkl__u32	tx_carrier_errors;
	__lkl__u32	tx_fifo_errors;
	__lkl__u32	tx_heartbeat_errors;
	__lkl__u32	tx_window_errors;

	/* for cslip etc */
	__lkl__u32	rx_compressed;
	__lkl__u32	tx_compressed;

	__lkl__u32	rx_nohandler;
};

/**
 * struct lkl_rtnl_link_stats64 - The main device statistics structure.
 *
 * @rx_packets: Number of good packets received by the interface.
 *   For hardware interfaces counts all good packets received from the device
 *   by the host, including packets which host had to drop at various stages
 *   of processing (even in the driver).
 *
 * @tx_packets: Number of packets successfully transmitted.
 *   For hardware interfaces counts packets which host was able to successfully
 *   hand over to the device, which does not necessarily mean that packets
 *   had been successfully transmitted out of the device, only that device
 *   acknowledged it copied them out of host memory.
 *
 * @rx_bytes: Number of good received bytes, corresponding to @rx_packets.
 *
 *   For IEEE 802.3 devices should count the length of Ethernet Frames
 *   excluding the FCS.
 *
 * @tx_bytes: Number of good transmitted bytes, corresponding to @tx_packets.
 *
 *   For IEEE 802.3 devices should count the length of Ethernet Frames
 *   excluding the FCS.
 *
 * @rx_errors: Total number of bad packets received on this network device.
 *   This counter must include events counted by @rx_length_errors,
 *   @rx_crc_errors, @rx_frame_errors and other errors not otherwise
 *   counted.
 *
 * @tx_errors: Total number of transmit problems.
 *   This counter must include events counter by @tx_aborted_errors,
 *   @tx_carrier_errors, @tx_fifo_errors, @tx_heartbeat_errors,
 *   @tx_window_errors and other errors not otherwise counted.
 *
 * @rx_dropped: Number of packets received but not processed,
 *   e.g. due to lack of resources or unsupported protocol.
 *   For hardware interfaces this counter may include packets discarded
 *   due to L2 address filtering but should not include packets dropped
 *   by the device due to buffer exhaustion which are counted separately in
 *   @rx_missed_errors (since procfs folds those two counters together).
 *
 * @tx_dropped: Number of packets dropped on their way to transmission,
 *   e.g. due to lack of resources.
 *
 * @multicast: Multicast packets received.
 *   For hardware interfaces this statistic is commonly calculated
 *   at the device level (unlike @rx_packets) and therefore may include
 *   packets which did not reach the host.
 *
 *   For IEEE 802.3 devices this counter may be equivalent to:
 *
 *    - 30.3.1.1.21 aMulticastFramesReceivedOK
 *
 * @collisions: Number of collisions during packet transmissions.
 *
 * @rx_length_errors: Number of packets dropped due to invalid length.
 *   Part of aggregate "frame" errors in `/proc/net/dev`.
 *
 *   For IEEE 802.3 devices this counter should be equivalent to a sum
 *   of the following attributes:
 *
 *    - 30.3.1.1.23 aInRangeLengthErrors
 *    - 30.3.1.1.24 aOutOfRangeLengthField
 *    - 30.3.1.1.25 aFrameTooLongErrors
 *
 * @rx_over_errors: Receiver FIFO overflow event counter.
 *
 *   Historically the count of overflow events. Such events may be
 *   reported in the receive descriptors or via interrupts, and may
 *   not correspond one-to-one with dropped packets.
 *
 *   The recommended interpretation for high speed interfaces is -
 *   number of packets dropped because they did not fit into buffers
 *   provided by the host, e.g. packets larger than MTU or next buffer
 *   in the ring was not available for a scatter transfer.
 *
 *   Part of aggregate "frame" errors in `/proc/net/dev`.
 *
 *   This statistics was historically used interchangeably with
 *   @rx_fifo_errors.
 *
 *   This statistic corresponds to hardware events and is not commonly used
 *   on software devices.
 *
 * @rx_crc_errors: Number of packets received with a CRC error.
 *   Part of aggregate "frame" errors in `/proc/net/dev`.
 *
 *   For IEEE 802.3 devices this counter must be equivalent to:
 *
 *    - 30.3.1.1.6 aFrameCheckSequenceErrors
 *
 * @rx_frame_errors: Receiver frame alignment errors.
 *   Part of aggregate "frame" errors in `/proc/net/dev`.
 *
 *   For IEEE 802.3 devices this counter should be equivalent to:
 *
 *    - 30.3.1.1.7 aAlignmentErrors
 *
 * @rx_fifo_errors: Receiver FIFO error counter.
 *
 *   Historically the count of overflow events. Those events may be
 *   reported in the receive descriptors or via interrupts, and may
 *   not correspond one-to-one with dropped packets.
 *
 *   This statistics was used interchangeably with @rx_over_errors.
 *   Not recommended for use in drivers for high speed interfaces.
 *
 *   This statistic is used on software devices, e.g. to count software
 *   packet queue overflow (can) or sequencing errors (GRE).
 *
 * @rx_missed_errors: Count of packets missed by the host.
 *   Folded into the "drop" counter in `/proc/net/dev`.
 *
 *   Counts number of packets dropped by the device due to lack
 *   of buffer space. This usually indicates that the host interface
 *   is slower than the network interface, or host is not keeping up
 *   with the receive packet rate.
 *
 *   This statistic corresponds to hardware events and is not used
 *   on software devices.
 *
 * @tx_aborted_errors:
 *   Part of aggregate "carrier" errors in `/proc/net/dev`.
 *   For IEEE 802.3 devices capable of half-duplex operation this counter
 *   must be equivalent to:
 *
 *    - 30.3.1.1.11 aFramesAbortedDueToXSColls
 *
 *   High speed interfaces may use this counter as a general device
 *   discard counter.
 *
 * @tx_carrier_errors: Number of frame transmission errors due to loss
 *   of carrier during transmission.
 *   Part of aggregate "carrier" errors in `/proc/net/dev`.
 *
 *   For IEEE 802.3 devices this counter must be equivalent to:
 *
 *    - 30.3.1.1.13 aCarrierSenseErrors
 *
 * @tx_fifo_errors: Number of frame transmission errors due to device
 *   FIFO underrun / underflow. This condition occurs when the device
 *   begins transmission of a frame but is unable to deliver the
 *   entire frame to the transmitter in time for transmission.
 *   Part of aggregate "carrier" errors in `/proc/net/dev`.
 *
 * @tx_heartbeat_errors: Number of Heartbeat / SQE Test errors for
 *   old half-duplex Ethernet.
 *   Part of aggregate "carrier" errors in `/proc/net/dev`.
 *
 *   For IEEE 802.3 devices possibly equivalent to:
 *
 *    - 30.3.2.1.4 aSQETestErrors
 *
 * @tx_window_errors: Number of frame transmission errors due
 *   to late collisions (for Ethernet - after the first 64B of transmission).
 *   Part of aggregate "carrier" errors in `/proc/net/dev`.
 *
 *   For IEEE 802.3 devices this counter must be equivalent to:
 *
 *    - 30.3.1.1.10 aLateCollisions
 *
 * @rx_compressed: Number of correctly received compressed packets.
 *   This counters is only meaningful for interfaces which support
 *   packet compression (e.g. CSLIP, PPP).
 *
 * @tx_compressed: Number of transmitted compressed packets.
 *   This counters is only meaningful for interfaces which support
 *   packet compression (e.g. CSLIP, PPP).
 *
 * @rx_nohandler: Number of packets received on the interface
 *   but dropped by the networking stack because the device is
 *   not designated to receive packets (e.g. backup link in a bond).
 *
 * @rx_otherhost_dropped: Number of packets dropped due to mismatch
 *   in destination MAC address.
 */
struct lkl_rtnl_link_stats64 {
	__lkl__u64	rx_packets;
	__lkl__u64	tx_packets;
	__lkl__u64	rx_bytes;
	__lkl__u64	tx_bytes;
	__lkl__u64	rx_errors;
	__lkl__u64	tx_errors;
	__lkl__u64	rx_dropped;
	__lkl__u64	tx_dropped;
	__lkl__u64	multicast;
	__lkl__u64	collisions;

	/* detailed rx_errors: */
	__lkl__u64	rx_length_errors;
	__lkl__u64	rx_over_errors;
	__lkl__u64	rx_crc_errors;
	__lkl__u64	rx_frame_errors;
	__lkl__u64	rx_fifo_errors;
	__lkl__u64	rx_missed_errors;

	/* detailed tx_errors */
	__lkl__u64	tx_aborted_errors;
	__lkl__u64	tx_carrier_errors;
	__lkl__u64	tx_fifo_errors;
	__lkl__u64	tx_heartbeat_errors;
	__lkl__u64	tx_window_errors;

	/* for cslip etc */
	__lkl__u64	rx_compressed;
	__lkl__u64	tx_compressed;
	__lkl__u64	rx_nohandler;

	__lkl__u64	rx_otherhost_dropped;
};

/* Subset of link stats useful for in-HW collection. Meaning of the fields is as
 * for struct lkl_rtnl_link_stats64.
 */
struct lkl_rtnl_hw_stats64 {
	__lkl__u64	rx_packets;
	__lkl__u64	tx_packets;
	__lkl__u64	rx_bytes;
	__lkl__u64	tx_bytes;
	__lkl__u64	rx_errors;
	__lkl__u64	tx_errors;
	__lkl__u64	rx_dropped;
	__lkl__u64	tx_dropped;
	__lkl__u64	multicast;
};

/* The struct should be in sync with struct lkl_ifmap */
struct lkl_rtnl_link_ifmap {
	__lkl__u64	mem_start;
	__lkl__u64	mem_end;
	__lkl__u64	base_addr;
	__lkl__u16	irq;
	__lkl__u8	dma;
	__lkl__u8	port;
};

/*
 * LKL_IFLA_AF_SPEC
 *   Contains nested attributes for address family specific attributes.
 *   Each address family may create a attribute with the address family
 *   number as type and create its own attribute structure in it.
 *
 *   Example:
 *   [LKL_IFLA_AF_SPEC] = {
 *       [LKL_AF_INET] = {
 *           [LKL_IFLA_INET_CONF] = ...,
 *       },
 *       [LKL_AF_INET6] = {
 *           [LKL_IFLA_INET6_FLAGS] = ...,
 *           [LKL_IFLA_INET6_CONF] = ...,
 *       }
 *   }
 */

enum {
	LKL_IFLA_UNSPEC,
	LKL_IFLA_ADDRESS,
	LKL_IFLA_BROADCAST,
	LKL_IFLA_IFNAME,
	LKL_IFLA_MTU,
	LKL_IFLA_LINK,
	LKL_IFLA_QDISC,
	LKL_IFLA_STATS,
	LKL_IFLA_COST,
#define LKL_IFLA_COST LKL_IFLA_COST
	LKL_IFLA_PRIORITY,
#define LKL_IFLA_PRIORITY LKL_IFLA_PRIORITY
	LKL_IFLA_MASTER,
#define LKL_IFLA_MASTER LKL_IFLA_MASTER
	LKL_IFLA_WIRELESS,		/* Wireless Extension event - see wireless.h */
#define LKL_IFLA_WIRELESS LKL_IFLA_WIRELESS
	LKL_IFLA_PROTINFO,		/* Protocol specific information for a link */
#define LKL_IFLA_PROTINFO LKL_IFLA_PROTINFO
	LKL_IFLA_TXQLEN,
#define LKL_IFLA_TXQLEN LKL_IFLA_TXQLEN
	LKL_IFLA_MAP,
#define LKL_IFLA_MAP LKL_IFLA_MAP
	LKL_IFLA_WEIGHT,
#define LKL_IFLA_WEIGHT LKL_IFLA_WEIGHT
	LKL_IFLA_OPERSTATE,
	LKL_IFLA_LINKMODE,
	LKL_IFLA_LINKINFO,
#define LKL_IFLA_LINKINFO LKL_IFLA_LINKINFO
	LKL_IFLA_NET_NS_PID,
	LKL_IFLA_IFALIAS,
	LKL_IFLA_NUM_VF,		/* Number of VFs if device is SR-IOV PF */
	LKL_IFLA_VFINFO_LIST,
	LKL_IFLA_STATS64,
	LKL_IFLA_VF_PORTS,
	LKL_IFLA_PORT_SELF,
	LKL_IFLA_AF_SPEC,
	LKL_IFLA_GROUP,		/* Group the device belongs to */
	LKL_IFLA_NET_NS_FD,
	LKL_IFLA_EXT_MASK,		/* Extended info mask, VFs, etc */
	LKL_IFLA_PROMISCUITY,	/* Promiscuity count: > 0 means acts PROMISC */
#define LKL_IFLA_PROMISCUITY LKL_IFLA_PROMISCUITY
	LKL_IFLA_NUM_TX_QUEUES,
	LKL_IFLA_NUM_RX_QUEUES,
	LKL_IFLA_CARRIER,
	LKL_IFLA_PHYS_PORT_ID,
	LKL_IFLA_CARRIER_CHANGES,
	LKL_IFLA_PHYS_SWITCH_ID,
	LKL_IFLA_LINK_NETNSID,
	LKL_IFLA_PHYS_PORT_NAME,
	LKL_IFLA_PROTO_DOWN,
	LKL_IFLA_GSO_MAX_SEGS,
	LKL_IFLA_GSO_MAX_SIZE,
	LKL_IFLA_PAD,
	LKL_IFLA_XDP,
	LKL_IFLA_EVENT,
	LKL_IFLA_NEW_NETNSID,
	LKL_IFLA_IF_NETNSID,
	LKL_IFLA_TARGET_NETNSID = LKL_IFLA_IF_NETNSID, /* new alias */
	LKL_IFLA_CARRIER_UP_COUNT,
	LKL_IFLA_CARRIER_DOWN_COUNT,
	LKL_IFLA_NEW_IFINDEX,
	LKL_IFLA_MIN_MTU,
	LKL_IFLA_MAX_MTU,
	LKL_IFLA_PROP_LIST,
	LKL_IFLA_ALT_IFNAME, /* Alternative ifname */
	LKL_IFLA_PERM_ADDRESS,
	LKL_IFLA_PROTO_DOWN_REASON,

	/* device (sysfs) name as parent, used instead
	 * of LKL_IFLA_LINK where there's no parent netdev
	 */
	LKL_IFLA_PARENT_DEV_NAME,
	LKL_IFLA_PARENT_DEV_BUS_NAME,
	LKL_IFLA_GRO_MAX_SIZE,
	LKL_IFLA_TSO_MAX_SIZE,
	LKL_IFLA_TSO_MAX_SEGS,
	LKL_IFLA_ALLMULTI,		/* Allmulti count: > 0 means acts ALLMULTI */

	__LKL__IFLA_MAX
};


#define LKL_IFLA_MAX (__LKL__IFLA_MAX - 1)

enum {
	LKL_IFLA_PROTO_DOWN_REASON_UNSPEC,
	LKL_IFLA_PROTO_DOWN_REASON_MASK,	/* lkl_u32, mask for reason bits */
	LKL_IFLA_PROTO_DOWN_REASON_VALUE,   /* lkl_u32, reason bit value */

	__LKL__IFLA_PROTO_DOWN_REASON_CNT,
	LKL_IFLA_PROTO_DOWN_REASON_MAX = __LKL__IFLA_PROTO_DOWN_REASON_CNT - 1
};

/* backwards compatibility for userspace */
#define LKL_IFLA_RTA(r)  ((struct lkl_rtattr*)(((char*)(r)) + LKL_NLMSG_ALIGN(sizeof(struct lkl_ifinfomsg))))
#define LKL_IFLA_PAYLOAD(n) LKL_NLMSG_PAYLOAD(n,sizeof(struct lkl_ifinfomsg))

enum {
	LKL_IFLA_INET_UNSPEC,
	LKL_IFLA_INET_CONF,
	__LKL__IFLA_INET_MAX,
};

#define LKL_IFLA_INET_MAX (__LKL__IFLA_INET_MAX - 1)

/* ifi_flags.

   IFF_* flags.

   The only change is:
   LKL_IFF_LOOPBACK, LKL_IFF_BROADCAST and LKL_IFF_POINTOPOINT are
   more not changeable by user. They describe link media
   characteristics and set by device driver.

   Comments:
   - Combination LKL_IFF_BROADCAST|LKL_IFF_POINTOPOINT is invalid
   - If neither of these three flags are set;
     the interface is NBMA.

   - LKL_IFF_MULTICAST does not mean anything special:
   multicasts can be used on all not-NBMA links.
   LKL_IFF_MULTICAST means that this media uses special encapsulation
   for multicast frames. Apparently, all LKL_IFF_POINTOPOINT and
   LKL_IFF_BROADCAST devices are able to use multicasts too.
 */

/* LKL_IFLA_LINK.
   For usual devices it is equal ifi_index.
   If it is a "virtual interface" (f.e. tunnel), ifi_link
   can point to real physical interface (f.e. for bandwidth calculations),
   or maybe 0, what means, that real media is unknown (usual
   for IPIP tunnels, when route to endpoint is allowed to change)
 */

/* Subtype attributes for LKL_IFLA_PROTINFO */
enum {
	LKL_IFLA_INET6_UNSPEC,
	LKL_IFLA_INET6_FLAGS,	/* link flags			*/
	LKL_IFLA_INET6_CONF,	/* sysctl parameters		*/
	LKL_IFLA_INET6_STATS,	/* statistics			*/
	LKL_IFLA_INET6_MCAST,	/* MC things. What of them?	*/
	LKL_IFLA_INET6_CACHEINFO,	/* time values and max reasm size */
	LKL_IFLA_INET6_ICMP6STATS,	/* statistics (icmpv6)		*/
	LKL_IFLA_INET6_TOKEN,	/* device token			*/
	LKL_IFLA_INET6_ADDR_GEN_MODE, /* implicit address generator mode */
	LKL_IFLA_INET6_RA_MTU,	/* mtu carried in the RA message */
	__LKL__IFLA_INET6_MAX
};

#define LKL_IFLA_INET6_MAX	(__LKL__IFLA_INET6_MAX - 1)

enum lkl_in6_addr_gen_mode {
	LKL_IN6_ADDR_GEN_MODE_EUI64,
	LKL_IN6_ADDR_GEN_MODE_NONE,
	LKL_IN6_ADDR_GEN_MODE_STABLE_PRIVACY,
	LKL_IN6_ADDR_GEN_MODE_RANDOM,
};

/* Bridge section */

enum {
	LKL_IFLA_BR_UNSPEC,
	LKL_IFLA_BR_FORWARD_DELAY,
	LKL_IFLA_BR_HELLO_TIME,
	LKL_IFLA_BR_MAX_AGE,
	LKL_IFLA_BR_AGEING_TIME,
	LKL_IFLA_BR_STP_STATE,
	LKL_IFLA_BR_PRIORITY,
	LKL_IFLA_BR_VLAN_FILTERING,
	LKL_IFLA_BR_VLAN_PROTOCOL,
	LKL_IFLA_BR_GROUP_FWD_MASK,
	LKL_IFLA_BR_ROOT_ID,
	LKL_IFLA_BR_BRIDGE_ID,
	LKL_IFLA_BR_ROOT_PORT,
	LKL_IFLA_BR_ROOT_PATH_COST,
	LKL_IFLA_BR_TOPOLOGY_CHANGE,
	LKL_IFLA_BR_TOPOLOGY_CHANGE_DETECTED,
	LKL_IFLA_BR_HELLO_TIMER,
	LKL_IFLA_BR_TCN_TIMER,
	LKL_IFLA_BR_TOPOLOGY_CHANGE_TIMER,
	LKL_IFLA_BR_GC_TIMER,
	LKL_IFLA_BR_GROUP_ADDR,
	LKL_IFLA_BR_FDB_FLUSH,
	LKL_IFLA_BR_MCAST_ROUTER,
	LKL_IFLA_BR_MCAST_SNOOPING,
	LKL_IFLA_BR_MCAST_QUERY_USE_IFADDR,
	LKL_IFLA_BR_MCAST_QUERIER,
	LKL_IFLA_BR_MCAST_HASH_ELASTICITY,
	LKL_IFLA_BR_MCAST_HASH_MAX,
	LKL_IFLA_BR_MCAST_LAST_MEMBER_CNT,
	LKL_IFLA_BR_MCAST_STARTUP_QUERY_CNT,
	LKL_IFLA_BR_MCAST_LAST_MEMBER_INTVL,
	LKL_IFLA_BR_MCAST_MEMBERSHIP_INTVL,
	LKL_IFLA_BR_MCAST_QUERIER_INTVL,
	LKL_IFLA_BR_MCAST_QUERY_INTVL,
	LKL_IFLA_BR_MCAST_QUERY_RESPONSE_INTVL,
	LKL_IFLA_BR_MCAST_STARTUP_QUERY_INTVL,
	LKL_IFLA_BR_NF_CALL_IPTABLES,
	LKL_IFLA_BR_NF_CALL_IP6TABLES,
	LKL_IFLA_BR_NF_CALL_ARPTABLES,
	LKL_IFLA_BR_VLAN_DEFAULT_PVID,
	LKL_IFLA_BR_PAD,
	LKL_IFLA_BR_VLAN_STATS_ENABLED,
	LKL_IFLA_BR_MCAST_STATS_ENABLED,
	LKL_IFLA_BR_MCAST_IGMP_VERSION,
	LKL_IFLA_BR_MCAST_MLD_VERSION,
	LKL_IFLA_BR_VLAN_STATS_PER_PORT,
	LKL_IFLA_BR_MULTI_BOOLOPT,
	LKL_IFLA_BR_MCAST_QUERIER_STATE,
	__LKL__IFLA_BR_MAX,
};

#define LKL_IFLA_BR_MAX	(__LKL__IFLA_BR_MAX - 1)

struct lkl_ifla_bridge_id {
	__lkl__u8	prio[2];
	__lkl__u8	addr[6]; /* LKL_ETH_ALEN */
};

enum {
	LKL_BRIDGE_MODE_UNSPEC,
	LKL_BRIDGE_MODE_HAIRPIN,
};

enum {
	LKL_IFLA_BRPORT_UNSPEC,
	LKL_IFLA_BRPORT_STATE,	/* Spanning tree state     */
	LKL_IFLA_BRPORT_PRIORITY,	/* "             priority  */
	LKL_IFLA_BRPORT_COST,	/* "             cost      */
	LKL_IFLA_BRPORT_MODE,	/* mode (hairpin)          */
	LKL_IFLA_BRPORT_GUARD,	/* bpdu guard              */
	LKL_IFLA_BRPORT_PROTECT,	/* root port protection    */
	LKL_IFLA_BRPORT_FAST_LEAVE,	/* multicast fast leave    */
	LKL_IFLA_BRPORT_LEARNING,	/* mac learning */
	LKL_IFLA_BRPORT_UNICAST_FLOOD, /* flood unicast traffic */
	LKL_IFLA_BRPORT_PROXYARP,	/* proxy ARP */
	LKL_IFLA_BRPORT_LEARNING_SYNC, /* mac learning sync from device */
	LKL_IFLA_BRPORT_PROXYARP_WIFI, /* proxy ARP for Wi-Fi */
	LKL_IFLA_BRPORT_ROOT_ID,	/* designated root */
	LKL_IFLA_BRPORT_BRIDGE_ID,	/* designated bridge */
	LKL_IFLA_BRPORT_DESIGNATED_PORT,
	LKL_IFLA_BRPORT_DESIGNATED_COST,
	LKL_IFLA_BRPORT_ID,
	LKL_IFLA_BRPORT_NO,
	LKL_IFLA_BRPORT_TOPOLOGY_CHANGE_ACK,
	LKL_IFLA_BRPORT_CONFIG_PENDING,
	LKL_IFLA_BRPORT_MESSAGE_AGE_TIMER,
	LKL_IFLA_BRPORT_FORWARD_DELAY_TIMER,
	LKL_IFLA_BRPORT_HOLD_TIMER,
	LKL_IFLA_BRPORT_FLUSH,
	LKL_IFLA_BRPORT_MULTICAST_ROUTER,
	LKL_IFLA_BRPORT_PAD,
	LKL_IFLA_BRPORT_MCAST_FLOOD,
	LKL_IFLA_BRPORT_MCAST_TO_UCAST,
	LKL_IFLA_BRPORT_VLAN_TUNNEL,
	LKL_IFLA_BRPORT_BCAST_FLOOD,
	LKL_IFLA_BRPORT_GROUP_FWD_MASK,
	LKL_IFLA_BRPORT_NEIGH_SUPPRESS,
	LKL_IFLA_BRPORT_ISOLATED,
	LKL_IFLA_BRPORT_BACKUP_PORT,
	LKL_IFLA_BRPORT_MRP_RING_OPEN,
	LKL_IFLA_BRPORT_MRP_IN_OPEN,
	LKL_IFLA_BRPORT_MCAST_EHT_HOSTS_LIMIT,
	LKL_IFLA_BRPORT_MCAST_EHT_HOSTS_CNT,
	LKL_IFLA_BRPORT_LOCKED,
	__LKL__IFLA_BRPORT_MAX
};
#define LKL_IFLA_BRPORT_MAX (__LKL__IFLA_BRPORT_MAX - 1)

struct lkl_ifla_cacheinfo {
	__lkl__u32	max_reasm_len;
	__lkl__u32	tstamp;		/* ipv6InterfaceTable updated timestamp */
	__lkl__u32	reachable_time;
	__lkl__u32	retrans_time;
};

enum {
	LKL_IFLA_INFO_UNSPEC,
	LKL_IFLA_INFO_KIND,
	LKL_IFLA_INFO_DATA,
	LKL_IFLA_INFO_XSTATS,
	LKL_IFLA_INFO_SLAVE_KIND,
	LKL_IFLA_INFO_SLAVE_DATA,
	__LKL__IFLA_INFO_MAX,
};

#define LKL_IFLA_INFO_MAX	(__LKL__IFLA_INFO_MAX - 1)

/* VLAN section */

enum {
	LKL_IFLA_VLAN_UNSPEC,
	LKL_IFLA_VLAN_ID,
	LKL_IFLA_VLAN_FLAGS,
	LKL_IFLA_VLAN_EGRESS_QOS,
	LKL_IFLA_VLAN_INGRESS_QOS,
	LKL_IFLA_VLAN_PROTOCOL,
	__LKL__IFLA_VLAN_MAX,
};

#define LKL_IFLA_VLAN_MAX	(__LKL__IFLA_VLAN_MAX - 1)

struct lkl_ifla_vlan_flags {
	__lkl__u32	flags;
	__lkl__u32	mask;
};

enum {
	LKL_IFLA_VLAN_QOS_UNSPEC,
	LKL_IFLA_VLAN_QOS_MAPPING,
	__LKL__IFLA_VLAN_QOS_MAX
};

#define LKL_IFLA_VLAN_QOS_MAX	(__LKL__IFLA_VLAN_QOS_MAX - 1)

struct lkl_ifla_vlan_qos_mapping {
	__lkl__u32 from;
	__lkl__u32 to;
};

/* MACVLAN section */
enum {
	LKL_IFLA_MACVLAN_UNSPEC,
	LKL_IFLA_MACVLAN_MODE,
	LKL_IFLA_MACVLAN_FLAGS,
	LKL_IFLA_MACVLAN_MACADDR_MODE,
	LKL_IFLA_MACVLAN_MACADDR,
	LKL_IFLA_MACVLAN_MACADDR_DATA,
	LKL_IFLA_MACVLAN_MACADDR_COUNT,
	LKL_IFLA_MACVLAN_BC_QUEUE_LEN,
	LKL_IFLA_MACVLAN_BC_QUEUE_LEN_USED,
	__LKL__IFLA_MACVLAN_MAX,
};

#define LKL_IFLA_MACVLAN_MAX (__LKL__IFLA_MACVLAN_MAX - 1)

enum lkl_macvlan_mode {
	LKL_MACVLAN_MODE_PRIVATE = 1, /* don't talk to other macvlans */
	LKL_MACVLAN_MODE_VEPA    = 2, /* talk to other ports through ext bridge */
	LKL_MACVLAN_MODE_BRIDGE  = 4, /* talk to bridge ports directly */
	LKL_MACVLAN_MODE_PASSTHRU = 8,/* take over the underlying device */
	LKL_MACVLAN_MODE_SOURCE  = 16,/* use source MAC address list to assign */
};

enum lkl_macvlan_macaddr_mode {
	LKL_MACVLAN_MACADDR_ADD,
	LKL_MACVLAN_MACADDR_DEL,
	LKL_MACVLAN_MACADDR_FLUSH,
	LKL_MACVLAN_MACADDR_SET,
};

#define LKL_MACVLAN_FLAG_NOPROMISC	1
#define LKL_MACVLAN_FLAG_NODST	2 /* skip dst macvlan if matching src macvlan */

/* VRF section */
enum {
	LKL_IFLA_VRF_UNSPEC,
	LKL_IFLA_VRF_TABLE,
	__LKL__IFLA_VRF_MAX
};

#define LKL_IFLA_VRF_MAX (__LKL__IFLA_VRF_MAX - 1)

enum {
	LKL_IFLA_VRF_PORT_UNSPEC,
	LKL_IFLA_VRF_PORT_TABLE,
	__LKL__IFLA_VRF_PORT_MAX
};

#define LKL_IFLA_VRF_PORT_MAX (__LKL__IFLA_VRF_PORT_MAX - 1)

/* MACSEC section */
enum {
	LKL_IFLA_MACSEC_UNSPEC,
	LKL_IFLA_MACSEC_SCI,
	LKL_IFLA_MACSEC_PORT,
	LKL_IFLA_MACSEC_ICV_LEN,
	LKL_IFLA_MACSEC_CIPHER_SUITE,
	LKL_IFLA_MACSEC_WINDOW,
	LKL_IFLA_MACSEC_ENCODING_SA,
	LKL_IFLA_MACSEC_ENCRYPT,
	LKL_IFLA_MACSEC_PROTECT,
	LKL_IFLA_MACSEC_INC_SCI,
	LKL_IFLA_MACSEC_ES,
	LKL_IFLA_MACSEC_SCB,
	LKL_IFLA_MACSEC_REPLAY_PROTECT,
	LKL_IFLA_MACSEC_VALIDATION,
	LKL_IFLA_MACSEC_PAD,
	LKL_IFLA_MACSEC_OFFLOAD,
	__LKL__IFLA_MACSEC_MAX,
};

#define LKL_IFLA_MACSEC_MAX (__LKL__IFLA_MACSEC_MAX - 1)

/* XFRM section */
enum {
	LKL_IFLA_XFRM_UNSPEC,
	LKL_IFLA_XFRM_LINK,
	LKL_IFLA_XFRM_IF_ID,
	LKL_IFLA_XFRM_COLLECT_METADATA,
	__LKL__IFLA_XFRM_MAX
};

#define LKL_IFLA_XFRM_MAX (__LKL__IFLA_XFRM_MAX - 1)

enum lkl_macsec_validation_type {
	LKL_MACSEC_VALIDATE_DISABLED = 0,
	LKL_MACSEC_VALIDATE_CHECK = 1,
	LKL_MACSEC_VALIDATE_STRICT = 2,
	__LKL__MACSEC_VALIDATE_END,
	LKL_MACSEC_VALIDATE_MAX = __LKL__MACSEC_VALIDATE_END - 1,
};

enum lkl_macsec_offload {
	LKL_MACSEC_OFFLOAD_OFF = 0,
	LKL_MACSEC_OFFLOAD_PHY = 1,
	LKL_MACSEC_OFFLOAD_MAC = 2,
	__LKL__MACSEC_OFFLOAD_END,
	LKL_MACSEC_OFFLOAD_MAX = __LKL__MACSEC_OFFLOAD_END - 1,
};

/* IPVLAN section */
enum {
	LKL_IFLA_IPVLAN_UNSPEC,
	LKL_IFLA_IPVLAN_MODE,
	LKL_IFLA_IPVLAN_FLAGS,
	__LKL__IFLA_IPVLAN_MAX
};

#define LKL_IFLA_IPVLAN_MAX (__LKL__IFLA_IPVLAN_MAX - 1)

enum lkl_ipvlan_mode {
	LKL_IPVLAN_MODE_L2 = 0,
	LKL_IPVLAN_MODE_L3,
	LKL_IPVLAN_MODE_L3S,
	LKL_IPVLAN_MODE_MAX
};

#define LKL_IPVLAN_F_PRIVATE	0x01
#define LKL_IPVLAN_F_VEPA		0x02

/* Tunnel RTM header */
struct lkl_tunnel_msg {
	__lkl__u8 family;
	__lkl__u8 flags;
	__lkl__u16 reserved2;
	__lkl__u32 ifindex;
};

/* VXLAN section */

/* include statistics in the dump */
#define LKL_TUNNEL_MSG_FLAG_STATS	0x01

#define LKL_TUNNEL_MSG_VALID_USER_FLAGS LKL_TUNNEL_MSG_FLAG_STATS

/* Embedded inside LKL_VXLAN_VNIFILTER_ENTRY_STATS */
enum {
	LKL_VNIFILTER_ENTRY_STATS_UNSPEC,
	LKL_VNIFILTER_ENTRY_STATS_RX_BYTES,
	LKL_VNIFILTER_ENTRY_STATS_RX_PKTS,
	LKL_VNIFILTER_ENTRY_STATS_RX_DROPS,
	LKL_VNIFILTER_ENTRY_STATS_RX_ERRORS,
	LKL_VNIFILTER_ENTRY_STATS_TX_BYTES,
	LKL_VNIFILTER_ENTRY_STATS_TX_PKTS,
	LKL_VNIFILTER_ENTRY_STATS_TX_DROPS,
	LKL_VNIFILTER_ENTRY_STATS_TX_ERRORS,
	LKL_VNIFILTER_ENTRY_STATS_PAD,
	__LKL__VNIFILTER_ENTRY_STATS_MAX
};
#define LKL_VNIFILTER_ENTRY_STATS_MAX (__LKL__VNIFILTER_ENTRY_STATS_MAX - 1)

enum {
	LKL_VXLAN_VNIFILTER_ENTRY_UNSPEC,
	LKL_VXLAN_VNIFILTER_ENTRY_START,
	LKL_VXLAN_VNIFILTER_ENTRY_END,
	LKL_VXLAN_VNIFILTER_ENTRY_GROUP,
	LKL_VXLAN_VNIFILTER_ENTRY_GROUP6,
	LKL_VXLAN_VNIFILTER_ENTRY_STATS,
	__LKL__VXLAN_VNIFILTER_ENTRY_MAX
};
#define LKL_VXLAN_VNIFILTER_ENTRY_MAX	(__LKL__VXLAN_VNIFILTER_ENTRY_MAX - 1)

enum {
	LKL_VXLAN_VNIFILTER_UNSPEC,
	LKL_VXLAN_VNIFILTER_ENTRY,
	__LKL__VXLAN_VNIFILTER_MAX
};
#define LKL_VXLAN_VNIFILTER_MAX	(__LKL__VXLAN_VNIFILTER_MAX - 1)

enum {
	LKL_IFLA_VXLAN_UNSPEC,
	LKL_IFLA_VXLAN_ID,
	LKL_IFLA_VXLAN_GROUP,	/* group or remote address */
	LKL_IFLA_VXLAN_LINK,
	LKL_IFLA_VXLAN_LOCAL,
	LKL_IFLA_VXLAN_TTL,
	LKL_IFLA_VXLAN_TOS,
	LKL_IFLA_VXLAN_LEARNING,
	LKL_IFLA_VXLAN_AGEING,
	LKL_IFLA_VXLAN_LIMIT,
	LKL_IFLA_VXLAN_PORT_RANGE,	/* source port */
	LKL_IFLA_VXLAN_PROXY,
	LKL_IFLA_VXLAN_RSC,
	LKL_IFLA_VXLAN_L2MISS,
	LKL_IFLA_VXLAN_L3MISS,
	LKL_IFLA_VXLAN_PORT,	/* destination port */
	LKL_IFLA_VXLAN_GROUP6,
	LKL_IFLA_VXLAN_LOCAL6,
	LKL_IFLA_VXLAN_UDP_CSUM,
	LKL_IFLA_VXLAN_UDP_ZERO_CSUM6_TX,
	LKL_IFLA_VXLAN_UDP_ZERO_CSUM6_RX,
	LKL_IFLA_VXLAN_REMCSUM_TX,
	LKL_IFLA_VXLAN_REMCSUM_RX,
	LKL_IFLA_VXLAN_GBP,
	LKL_IFLA_VXLAN_REMCSUM_NOPARTIAL,
	LKL_IFLA_VXLAN_COLLECT_METADATA,
	LKL_IFLA_VXLAN_LABEL,
	LKL_IFLA_VXLAN_GPE,
	LKL_IFLA_VXLAN_TTL_INHERIT,
	LKL_IFLA_VXLAN_DF,
	LKL_IFLA_VXLAN_VNIFILTER, /* only applicable with COLLECT_METADATA mode */
	__LKL__IFLA_VXLAN_MAX
};
#define LKL_IFLA_VXLAN_MAX	(__LKL__IFLA_VXLAN_MAX - 1)

struct lkl_ifla_vxlan_port_range {
	__lkl__be16	low;
	__lkl__be16	high;
};

enum lkl_ifla_vxlan_df {
	LKL_VXLAN_DF_UNSET = 0,
	LKL_VXLAN_DF_SET,
	LKL_VXLAN_DF_INHERIT,
	__LKL__VXLAN_DF_END,
	LKL_VXLAN_DF_MAX = __LKL__VXLAN_DF_END - 1,
};

/* GENEVE section */
enum {
	LKL_IFLA_GENEVE_UNSPEC,
	LKL_IFLA_GENEVE_ID,
	LKL_IFLA_GENEVE_REMOTE,
	LKL_IFLA_GENEVE_TTL,
	LKL_IFLA_GENEVE_TOS,
	LKL_IFLA_GENEVE_PORT,	/* destination port */
	LKL_IFLA_GENEVE_COLLECT_METADATA,
	LKL_IFLA_GENEVE_REMOTE6,
	LKL_IFLA_GENEVE_UDP_CSUM,
	LKL_IFLA_GENEVE_UDP_ZERO_CSUM6_TX,
	LKL_IFLA_GENEVE_UDP_ZERO_CSUM6_RX,
	LKL_IFLA_GENEVE_LABEL,
	LKL_IFLA_GENEVE_TTL_INHERIT,
	LKL_IFLA_GENEVE_DF,
	LKL_IFLA_GENEVE_INNER_PROTO_INHERIT,
	__LKL__IFLA_GENEVE_MAX
};
#define LKL_IFLA_GENEVE_MAX	(__LKL__IFLA_GENEVE_MAX - 1)

enum lkl_ifla_geneve_df {
	LKL_GENEVE_DF_UNSET = 0,
	LKL_GENEVE_DF_SET,
	LKL_GENEVE_DF_INHERIT,
	__LKL__GENEVE_DF_END,
	LKL_GENEVE_DF_MAX = __LKL__GENEVE_DF_END - 1,
};

/* Bareudp section  */
enum {
	LKL_IFLA_BAREUDP_UNSPEC,
	LKL_IFLA_BAREUDP_PORT,
	LKL_IFLA_BAREUDP_ETHERTYPE,
	LKL_IFLA_BAREUDP_SRCPORT_MIN,
	LKL_IFLA_BAREUDP_MULTIPROTO_MODE,
	__LKL__IFLA_BAREUDP_MAX
};

#define LKL_IFLA_BAREUDP_MAX (__LKL__IFLA_BAREUDP_MAX - 1)

/* PPP section */
enum {
	LKL_IFLA_PPP_UNSPEC,
	LKL_IFLA_PPP_DEV_FD,
	__LKL__IFLA_PPP_MAX
};
#define LKL_IFLA_PPP_MAX (__LKL__IFLA_PPP_MAX - 1)

/* GTP section */

enum lkl_ifla_gtp_role {
	LKL_GTP_ROLE_GGSN = 0,
	LKL_GTP_ROLE_SGSN,
};

enum {
	LKL_IFLA_GTP_UNSPEC,
	LKL_IFLA_GTP_FD0,
	LKL_IFLA_GTP_FD1,
	LKL_IFLA_GTP_PDP_HASHSIZE,
	LKL_IFLA_GTP_ROLE,
	LKL_IFLA_GTP_CREATE_SOCKETS,
	LKL_IFLA_GTP_RESTART_COUNT,
	__LKL__IFLA_GTP_MAX,
};
#define LKL_IFLA_GTP_MAX (__LKL__IFLA_GTP_MAX - 1)

/* Bonding section */

enum {
	LKL_IFLA_BOND_UNSPEC,
	LKL_IFLA_BOND_MODE,
	LKL_IFLA_BOND_ACTIVE_SLAVE,
	LKL_IFLA_BOND_MIIMON,
	LKL_IFLA_BOND_UPDELAY,
	LKL_IFLA_BOND_DOWNDELAY,
	LKL_IFLA_BOND_USE_CARRIER,
	LKL_IFLA_BOND_ARP_INTERVAL,
	LKL_IFLA_BOND_ARP_IP_TARGET,
	LKL_IFLA_BOND_ARP_VALIDATE,
	LKL_IFLA_BOND_ARP_ALL_TARGETS,
	LKL_IFLA_BOND_PRIMARY,
	LKL_IFLA_BOND_PRIMARY_RESELECT,
	LKL_IFLA_BOND_FAIL_OVER_MAC,
	LKL_IFLA_BOND_XMIT_HASH_POLICY,
	LKL_IFLA_BOND_RESEND_IGMP,
	LKL_IFLA_BOND_NUM_PEER_NOTIF,
	LKL_IFLA_BOND_ALL_SLAVES_ACTIVE,
	LKL_IFLA_BOND_MIN_LINKS,
	LKL_IFLA_BOND_LP_INTERVAL,
	LKL_IFLA_BOND_PACKETS_PER_SLAVE,
	LKL_IFLA_BOND_AD_LACP_RATE,
	LKL_IFLA_BOND_AD_SELECT,
	LKL_IFLA_BOND_AD_INFO,
	LKL_IFLA_BOND_AD_ACTOR_SYS_PRIO,
	LKL_IFLA_BOND_AD_USER_PORT_KEY,
	LKL_IFLA_BOND_AD_ACTOR_SYSTEM,
	LKL_IFLA_BOND_TLB_DYNAMIC_LB,
	LKL_IFLA_BOND_PEER_NOTIF_DELAY,
	LKL_IFLA_BOND_AD_LACP_ACTIVE,
	LKL_IFLA_BOND_MISSED_MAX,
	LKL_IFLA_BOND_NS_IP6_TARGET,
	__LKL__IFLA_BOND_MAX,
};

#define LKL_IFLA_BOND_MAX	(__LKL__IFLA_BOND_MAX - 1)

enum {
	LKL_IFLA_BOND_AD_INFO_UNSPEC,
	LKL_IFLA_BOND_AD_INFO_AGGREGATOR,
	LKL_IFLA_BOND_AD_INFO_NUM_PORTS,
	LKL_IFLA_BOND_AD_INFO_ACTOR_KEY,
	LKL_IFLA_BOND_AD_INFO_PARTNER_KEY,
	LKL_IFLA_BOND_AD_INFO_PARTNER_MAC,
	__LKL__IFLA_BOND_AD_INFO_MAX,
};

#define LKL_IFLA_BOND_AD_INFO_MAX	(__LKL__IFLA_BOND_AD_INFO_MAX - 1)

enum {
	LKL_IFLA_BOND_SLAVE_UNSPEC,
	LKL_IFLA_BOND_SLAVE_STATE,
	LKL_IFLA_BOND_SLAVE_MII_STATUS,
	LKL_IFLA_BOND_SLAVE_LINK_FAILURE_COUNT,
	LKL_IFLA_BOND_SLAVE_PERM_HWADDR,
	LKL_IFLA_BOND_SLAVE_QUEUE_ID,
	LKL_IFLA_BOND_SLAVE_AD_AGGREGATOR_ID,
	LKL_IFLA_BOND_SLAVE_AD_ACTOR_OPER_PORT_STATE,
	LKL_IFLA_BOND_SLAVE_AD_PARTNER_OPER_PORT_STATE,
	LKL_IFLA_BOND_SLAVE_PRIO,
	__LKL__IFLA_BOND_SLAVE_MAX,
};

#define LKL_IFLA_BOND_SLAVE_MAX	(__LKL__IFLA_BOND_SLAVE_MAX - 1)

/* SR-IOV virtual function management section */

enum {
	LKL_IFLA_VF_INFO_UNSPEC,
	LKL_IFLA_VF_INFO,
	__LKL__IFLA_VF_INFO_MAX,
};

#define LKL_IFLA_VF_INFO_MAX (__LKL__IFLA_VF_INFO_MAX - 1)

enum {
	LKL_IFLA_VF_UNSPEC,
	LKL_IFLA_VF_MAC,		/* Hardware queue specific attributes */
	LKL_IFLA_VF_VLAN,		/* VLAN ID and QoS */
	LKL_IFLA_VF_TX_RATE,	/* Max TX Bandwidth Allocation */
	LKL_IFLA_VF_SPOOFCHK,	/* Spoof Checking on/off switch */
	LKL_IFLA_VF_LINK_STATE,	/* link state enable/disable/auto switch */
	LKL_IFLA_VF_RATE,		/* Min and Max TX Bandwidth Allocation */
	LKL_IFLA_VF_RSS_QUERY_EN,	/* RSS Redirection Table and Hash Key query
				 * on/off switch
				 */
	LKL_IFLA_VF_STATS,		/* network device statistics */
	LKL_IFLA_VF_TRUST,		/* Trust VF */
	LKL_IFLA_VF_IB_NODE_GUID,	/* VF Infiniband node GUID */
	LKL_IFLA_VF_IB_PORT_GUID,	/* VF Infiniband port GUID */
	LKL_IFLA_VF_VLAN_LIST,	/* nested list of vlans, option for QinQ */
	LKL_IFLA_VF_BROADCAST,	/* VF broadcast */
	__LKL__IFLA_VF_MAX,
};

#define LKL_IFLA_VF_MAX (__LKL__IFLA_VF_MAX - 1)

struct lkl_ifla_vf_mac {
	__lkl__u32 vf;
	__lkl__u8 mac[32]; /* MAX_ADDR_LEN */
};

struct lkl_ifla_vf_broadcast {
	__lkl__u8 broadcast[32];
};

struct lkl_ifla_vf_vlan {
	__lkl__u32 vf;
	__lkl__u32 vlan; /* 0 - 4095, 0 disables VLAN filter */
	__lkl__u32 qos;
};

enum {
	LKL_IFLA_VF_VLAN_INFO_UNSPEC,
	LKL_IFLA_VF_VLAN_INFO,	/* VLAN ID, QoS and VLAN protocol */
	__LKL__IFLA_VF_VLAN_INFO_MAX,
};

#define LKL_IFLA_VF_VLAN_INFO_MAX (__LKL__IFLA_VF_VLAN_INFO_MAX - 1)
#define LKL_MAX_VLAN_LIST_LEN 1

struct lkl_ifla_vf_vlan_info {
	__lkl__u32 vf;
	__lkl__u32 vlan; /* 0 - 4095, 0 disables VLAN filter */
	__lkl__u32 qos;
	__lkl__be16 vlan_proto; /* VLAN protocol either 802.1Q or 802.1ad */
};

struct lkl_ifla_vf_tx_rate {
	__lkl__u32 vf;
	__lkl__u32 rate; /* Max TX bandwidth in Mbps, 0 disables throttling */
};

struct lkl_ifla_vf_rate {
	__lkl__u32 vf;
	__lkl__u32 min_tx_rate; /* Min Bandwidth in Mbps */
	__lkl__u32 max_tx_rate; /* Max Bandwidth in Mbps */
};

struct lkl_ifla_vf_spoofchk {
	__lkl__u32 vf;
	__lkl__u32 setting;
};

struct lkl_ifla_vf_guid {
	__lkl__u32 vf;
	__lkl__u64 guid;
};

enum {
	LKL_IFLA_VF_LINK_STATE_AUTO,	/* link state of the uplink */
	LKL_IFLA_VF_LINK_STATE_ENABLE,	/* link always up */
	LKL_IFLA_VF_LINK_STATE_DISABLE,	/* link always down */
	__LKL__IFLA_VF_LINK_STATE_MAX,
};

struct lkl_ifla_vf_link_state {
	__lkl__u32 vf;
	__lkl__u32 link_state;
};

struct lkl_ifla_vf_rss_query_en {
	__lkl__u32 vf;
	__lkl__u32 setting;
};

enum {
	LKL_IFLA_VF_STATS_RX_PACKETS,
	LKL_IFLA_VF_STATS_TX_PACKETS,
	LKL_IFLA_VF_STATS_RX_BYTES,
	LKL_IFLA_VF_STATS_TX_BYTES,
	LKL_IFLA_VF_STATS_BROADCAST,
	LKL_IFLA_VF_STATS_MULTICAST,
	LKL_IFLA_VF_STATS_PAD,
	LKL_IFLA_VF_STATS_RX_DROPPED,
	LKL_IFLA_VF_STATS_TX_DROPPED,
	__LKL__IFLA_VF_STATS_MAX,
};

#define LKL_IFLA_VF_STATS_MAX (__LKL__IFLA_VF_STATS_MAX - 1)

struct lkl_ifla_vf_trust {
	__lkl__u32 vf;
	__lkl__u32 setting;
};

/* VF ports management section
 *
 *	Nested layout of set/get msg is:
 *
 *		[LKL_IFLA_NUM_VF]
 *		[LKL_IFLA_VF_PORTS]
 *			[LKL_IFLA_VF_PORT]
 *				[IFLA_PORT_*], ...
 *			[LKL_IFLA_VF_PORT]
 *				[IFLA_PORT_*], ...
 *			...
 *		[LKL_IFLA_PORT_SELF]
 *			[IFLA_PORT_*], ...
 */

enum {
	LKL_IFLA_VF_PORT_UNSPEC,
	LKL_IFLA_VF_PORT,			/* nest */
	__LKL__IFLA_VF_PORT_MAX,
};

#define LKL_IFLA_VF_PORT_MAX (__LKL__IFLA_VF_PORT_MAX - 1)

enum {
	LKL_IFLA_PORT_UNSPEC,
	LKL_IFLA_PORT_VF,			/* __lkl__u32 */
	LKL_IFLA_PORT_PROFILE,		/* string */
	LKL_IFLA_PORT_VSI_TYPE,		/* 802.1Qbg (pre-)standard VDP */
	LKL_IFLA_PORT_INSTANCE_UUID,	/* binary UUID */
	LKL_IFLA_PORT_HOST_UUID,		/* binary UUID */
	LKL_IFLA_PORT_REQUEST,		/* __lkl__u8 */
	LKL_IFLA_PORT_RESPONSE,		/* __lkl__u16, output only */
	__LKL__IFLA_PORT_MAX,
};

#define LKL_IFLA_PORT_MAX (__LKL__IFLA_PORT_MAX - 1)

#define LKL_PORT_PROFILE_MAX	40
#define LKL_PORT_UUID_MAX		16
#define LKL_PORT_SELF_VF		-1

enum {
	LKL_PORT_REQUEST_PREASSOCIATE = 0,
	LKL_PORT_REQUEST_PREASSOCIATE_RR,
	LKL_PORT_REQUEST_ASSOCIATE,
	LKL_PORT_REQUEST_DISASSOCIATE,
};

enum {
	LKL_PORT_VDP_RESPONSE_SUCCESS = 0,
	LKL_PORT_VDP_RESPONSE_INVALID_FORMAT,
	LKL_PORT_VDP_RESPONSE_INSUFFICIENT_RESOURCES,
	LKL_PORT_VDP_RESPONSE_UNUSED_VTID,
	LKL_PORT_VDP_RESPONSE_VTID_VIOLATION,
	LKL_PORT_VDP_RESPONSE_VTID_VERSION_VIOALTION,
	LKL_PORT_VDP_RESPONSE_OUT_OF_SYNC,
	/* 0x08-0xFF reserved for future VDP use */
	LKL_PORT_PROFILE_RESPONSE_SUCCESS = 0x100,
	LKL_PORT_PROFILE_RESPONSE_INPROGRESS,
	LKL_PORT_PROFILE_RESPONSE_INVALID,
	LKL_PORT_PROFILE_RESPONSE_BADSTATE,
	LKL_PORT_PROFILE_RESPONSE_INSUFFICIENT_RESOURCES,
	LKL_PORT_PROFILE_RESPONSE_ERROR,
};

struct lkl_ifla_port_vsi {
	__lkl__u8 vsi_mgr_id;
	__lkl__u8 vsi_type_id[3];
	__lkl__u8 vsi_type_version;
	__lkl__u8 pad[3];
};


/* IPoIB section */

enum {
	LKL_IFLA_IPOIB_UNSPEC,
	LKL_IFLA_IPOIB_PKEY,
	LKL_IFLA_IPOIB_MODE,
	LKL_IFLA_IPOIB_UMCAST,
	__LKL__IFLA_IPOIB_MAX
};

enum {
	LKL_IPOIB_MODE_DATAGRAM  = 0, /* using unreliable datagram QPs */
	LKL_IPOIB_MODE_CONNECTED = 1, /* using connected QPs */
};

#define LKL_IFLA_IPOIB_MAX (__LKL__IFLA_IPOIB_MAX - 1)


/* HSR/PRP section, both uses same interface */

/* Different redundancy protocols for hsr device */
enum {
	LKL_HSR_PROTOCOL_HSR,
	LKL_HSR_PROTOCOL_PRP,
	LKL_HSR_PROTOCOL_MAX,
};

enum {
	LKL_IFLA_HSR_UNSPEC,
	LKL_IFLA_HSR_SLAVE1,
	LKL_IFLA_HSR_SLAVE2,
	LKL_IFLA_HSR_MULTICAST_SPEC,	/* Last byte of supervision addr */
	LKL_IFLA_HSR_SUPERVISION_ADDR,	/* Supervision frame multicast addr */
	LKL_IFLA_HSR_SEQ_NR,
	LKL_IFLA_HSR_VERSION,		/* HSR version */
	LKL_IFLA_HSR_PROTOCOL,		/* Indicate different protocol than
					 * HSR. For example PRP.
					 */
	__LKL__IFLA_HSR_MAX,
};

#define LKL_IFLA_HSR_MAX (__LKL__IFLA_HSR_MAX - 1)

/* STATS section */

struct lkl_if_stats_msg {
	__lkl__u8  family;
	__lkl__u8  pad1;
	__lkl__u16 pad2;
	__lkl__u32 ifindex;
	__lkl__u32 filter_mask;
};

/* A stats attribute can be netdev specific or a global stat.
 * For netdev stats, lets use the prefix IFLA_STATS_LINK_*
 */
enum {
	LKL_IFLA_STATS_UNSPEC, /* also used as 64bit pad attribute */
	LKL_IFLA_STATS_LINK_64,
	LKL_IFLA_STATS_LINK_XSTATS,
	LKL_IFLA_STATS_LINK_XSTATS_SLAVE,
	LKL_IFLA_STATS_LINK_OFFLOAD_XSTATS,
	LKL_IFLA_STATS_AF_SPEC,
	__LKL__IFLA_STATS_MAX,
};

#define LKL_IFLA_STATS_MAX (__LKL__IFLA_STATS_MAX - 1)

#define LKL_IFLA_STATS_FILTER_BIT(ATTR)	(1 << (ATTR - 1))

enum {
	LKL_IFLA_STATS_GETSET_UNSPEC,
	LKL_IFLA_STATS_GET_FILTERS, /* Nest of IFLA_STATS_LINK_xxx, each a lkl_u32 with
				 * a filter mask for the corresponding group.
				 */
	LKL_IFLA_STATS_SET_OFFLOAD_XSTATS_L3_STATS, /* 0 or 1 as u8 */
	__LKL__IFLA_STATS_GETSET_MAX,
};

#define LKL_IFLA_STATS_GETSET_MAX (__LKL__IFLA_STATS_GETSET_MAX - 1)

/* These are embedded into LKL_IFLA_STATS_LINK_XSTATS:
 * [LKL_IFLA_STATS_LINK_XSTATS]
 * -> [LINK_XSTATS_TYPE_xxx]
 *    -> [rtnl link type specific attributes]
 */
enum {
	LKL_LINK_XSTATS_TYPE_UNSPEC,
	LKL_LINK_XSTATS_TYPE_BRIDGE,
	LKL_LINK_XSTATS_TYPE_BOND,
	__LKL__LINK_XSTATS_TYPE_MAX
};
#define LKL_LINK_XSTATS_TYPE_MAX (__LKL__LINK_XSTATS_TYPE_MAX - 1)

/* These are stats embedded into LKL_IFLA_STATS_LINK_OFFLOAD_XSTATS */
enum {
	LKL_IFLA_OFFLOAD_XSTATS_UNSPEC,
	LKL_IFLA_OFFLOAD_XSTATS_CPU_HIT, /* struct lkl_rtnl_link_stats64 */
	LKL_IFLA_OFFLOAD_XSTATS_HW_S_INFO,	/* HW stats info. A nest */
	LKL_IFLA_OFFLOAD_XSTATS_L3_STATS,	/* struct lkl_rtnl_hw_stats64 */
	__LKL__IFLA_OFFLOAD_XSTATS_MAX
};
#define LKL_IFLA_OFFLOAD_XSTATS_MAX (__LKL__IFLA_OFFLOAD_XSTATS_MAX - 1)

enum {
	LKL_IFLA_OFFLOAD_XSTATS_HW_S_INFO_UNSPEC,
	LKL_IFLA_OFFLOAD_XSTATS_HW_S_INFO_REQUEST,		/* u8 */
	LKL_IFLA_OFFLOAD_XSTATS_HW_S_INFO_USED,		/* u8 */
	__LKL__IFLA_OFFLOAD_XSTATS_HW_S_INFO_MAX,
};
#define LKL_IFLA_OFFLOAD_XSTATS_HW_S_INFO_MAX \
	(__LKL__IFLA_OFFLOAD_XSTATS_HW_S_INFO_MAX - 1)

/* XDP section */

#define LKL_XDP_FLAGS_UPDATE_IF_NOEXIST	(1U << 0)
#define LKL_XDP_FLAGS_SKB_MODE		(1U << 1)
#define LKL_XDP_FLAGS_DRV_MODE		(1U << 2)
#define LKL_XDP_FLAGS_HW_MODE		(1U << 3)
#define LKL_XDP_FLAGS_REPLACE		(1U << 4)
#define LKL_XDP_FLAGS_MODES			(LKL_XDP_FLAGS_SKB_MODE | \
					 LKL_XDP_FLAGS_DRV_MODE | \
					 LKL_XDP_FLAGS_HW_MODE)
#define LKL_XDP_FLAGS_MASK			(LKL_XDP_FLAGS_UPDATE_IF_NOEXIST | \
					 LKL_XDP_FLAGS_MODES | LKL_XDP_FLAGS_REPLACE)

/* These are stored into LKL_IFLA_XDP_ATTACHED on dump. */
enum {
	LKL_XDP_ATTACHED_NONE = 0,
	LKL_XDP_ATTACHED_DRV,
	LKL_XDP_ATTACHED_SKB,
	LKL_XDP_ATTACHED_HW,
	LKL_XDP_ATTACHED_MULTI,
};

enum {
	LKL_IFLA_XDP_UNSPEC,
	LKL_IFLA_XDP_FD,
	LKL_IFLA_XDP_ATTACHED,
	LKL_IFLA_XDP_FLAGS,
	LKL_IFLA_XDP_PROG_ID,
	LKL_IFLA_XDP_DRV_PROG_ID,
	LKL_IFLA_XDP_SKB_PROG_ID,
	LKL_IFLA_XDP_HW_PROG_ID,
	LKL_IFLA_XDP_EXPECTED_FD,
	__LKL__IFLA_XDP_MAX,
};

#define LKL_IFLA_XDP_MAX (__LKL__IFLA_XDP_MAX - 1)

enum {
	LKL_IFLA_EVENT_NONE,
	LKL_IFLA_EVENT_REBOOT,		/* internal reset / reboot */
	LKL_IFLA_EVENT_FEATURES,		/* change in offload features */
	LKL_IFLA_EVENT_BONDING_FAILOVER,	/* change in active slave */
	LKL_IFLA_EVENT_NOTIFY_PEERS,	/* re-sent grat. arp/ndisc */
	LKL_IFLA_EVENT_IGMP_RESEND,		/* re-sent IGMP JOIN */
	LKL_IFLA_EVENT_BONDING_OPTIONS,	/* change in bonding options */
};

/* tun section */

enum {
	LKL_IFLA_TUN_UNSPEC,
	LKL_IFLA_TUN_OWNER,
	LKL_IFLA_TUN_GROUP,
	LKL_IFLA_TUN_TYPE,
	LKL_IFLA_TUN_PI,
	LKL_IFLA_TUN_VNET_HDR,
	LKL_IFLA_TUN_PERSIST,
	LKL_IFLA_TUN_MULTI_QUEUE,
	LKL_IFLA_TUN_NUM_QUEUES,
	LKL_IFLA_TUN_NUM_DISABLED_QUEUES,
	__LKL__IFLA_TUN_MAX,
};

#define LKL_IFLA_TUN_MAX (__LKL__IFLA_TUN_MAX - 1)

/* rmnet section */

#define LKL_RMNET_FLAGS_INGRESS_DEAGGREGATION         (1U << 0)
#define LKL_RMNET_FLAGS_INGRESS_MAP_COMMANDS          (1U << 1)
#define LKL_RMNET_FLAGS_INGRESS_MAP_CKSUMV4           (1U << 2)
#define LKL_RMNET_FLAGS_EGRESS_MAP_CKSUMV4            (1U << 3)
#define LKL_RMNET_FLAGS_INGRESS_MAP_CKSUMV5           (1U << 4)
#define LKL_RMNET_FLAGS_EGRESS_MAP_CKSUMV5            (1U << 5)

enum {
	LKL_IFLA_RMNET_UNSPEC,
	LKL_IFLA_RMNET_MUX_ID,
	LKL_IFLA_RMNET_FLAGS,
	__LKL__IFLA_RMNET_MAX,
};

#define LKL_IFLA_RMNET_MAX	(__LKL__IFLA_RMNET_MAX - 1)

struct lkl_ifla_rmnet_flags {
	__lkl__u32	flags;
	__lkl__u32	mask;
};

/* MCTP section */

enum {
	LKL_IFLA_MCTP_UNSPEC,
	LKL_IFLA_MCTP_NET,
	__LKL__IFLA_MCTP_MAX,
};

#define LKL_IFLA_MCTP_MAX (__LKL__IFLA_MCTP_MAX - 1)

/* DSA section */

enum {
	LKL_IFLA_DSA_UNSPEC,
	LKL_IFLA_DSA_MASTER,
	__LKL__IFLA_DSA_MAX,
};

#define LKL_IFLA_DSA_MAX	(__LKL__IFLA_DSA_MAX - 1)

#endif /* _LKL_LINUX_IF_LINK_H */
