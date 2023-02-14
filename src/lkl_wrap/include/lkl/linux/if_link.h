/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_IF_LINK_H
#define _LKL_LINUX_IF_LINK_H

#include <lkl/linux/types.h>
#include <lkl/linux/netlink.h>

/* This struct should be in sync with struct lkl_rtnl_link_stats64 */
struct lkl_rtnl_link_stats {
	__lkl__u32	rx_packets;		/* total packets received	*/
	__lkl__u32	tx_packets;		/* total packets transmitted	*/
	__lkl__u32	rx_bytes;		/* total bytes received 	*/
	__lkl__u32	tx_bytes;		/* total bytes transmitted	*/
	__lkl__u32	rx_errors;		/* bad packets received		*/
	__lkl__u32	tx_errors;		/* packet transmit problems	*/
	__lkl__u32	rx_dropped;		/* no space in linux buffers	*/
	__lkl__u32	tx_dropped;		/* no space available in linux	*/
	__lkl__u32	multicast;		/* multicast packets received	*/
	__lkl__u32	collisions;

	/* detailed rx_errors: */
	__lkl__u32	rx_length_errors;
	__lkl__u32	rx_over_errors;		/* receiver ring buff overflow	*/
	__lkl__u32	rx_crc_errors;		/* recved pkt with crc error	*/
	__lkl__u32	rx_frame_errors;	/* recv'd frame alignment error */
	__lkl__u32	rx_fifo_errors;		/* recv'r fifo overrun		*/
	__lkl__u32	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	__lkl__u32	tx_aborted_errors;
	__lkl__u32	tx_carrier_errors;
	__lkl__u32	tx_fifo_errors;
	__lkl__u32	tx_heartbeat_errors;
	__lkl__u32	tx_window_errors;

	/* for cslip etc */
	__lkl__u32	rx_compressed;
	__lkl__u32	tx_compressed;

	__lkl__u32	rx_nohandler;		/* dropped, no handler found	*/
};

/* The main device statistics structure */
struct lkl_rtnl_link_stats64 {
	__lkl__u64	rx_packets;		/* total packets received	*/
	__lkl__u64	tx_packets;		/* total packets transmitted	*/
	__lkl__u64	rx_bytes;		/* total bytes received 	*/
	__lkl__u64	tx_bytes;		/* total bytes transmitted	*/
	__lkl__u64	rx_errors;		/* bad packets received		*/
	__lkl__u64	tx_errors;		/* packet transmit problems	*/
	__lkl__u64	rx_dropped;		/* no space in linux buffers	*/
	__lkl__u64	tx_dropped;		/* no space available in linux	*/
	__lkl__u64	multicast;		/* multicast packets received	*/
	__lkl__u64	collisions;

	/* detailed rx_errors: */
	__lkl__u64	rx_length_errors;
	__lkl__u64	rx_over_errors;		/* receiver ring buff overflow	*/
	__lkl__u64	rx_crc_errors;		/* recved pkt with crc error	*/
	__lkl__u64	rx_frame_errors;	/* recv'd frame alignment error */
	__lkl__u64	rx_fifo_errors;		/* recv'r fifo overrun		*/
	__lkl__u64	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	__lkl__u64	tx_aborted_errors;
	__lkl__u64	tx_carrier_errors;
	__lkl__u64	tx_fifo_errors;
	__lkl__u64	tx_heartbeat_errors;
	__lkl__u64	tx_window_errors;

	/* for cslip etc */
	__lkl__u64	rx_compressed;
	__lkl__u64	tx_compressed;

	__lkl__u64	rx_nohandler;		/* dropped, no handler found	*/
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
	LKL_IFLA_CARRIER_UP_COUNT,
	LKL_IFLA_CARRIER_DOWN_COUNT,
	LKL_IFLA_NEW_IFINDEX,
	__LKL__IFLA_MAX
};


#define LKL_IFLA_MAX (__LKL__IFLA_MAX - 1)

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
	__LKL__IFLA_MACSEC_MAX,
};

#define LKL_IFLA_MACSEC_MAX (__LKL__IFLA_MACSEC_MAX - 1)

enum lkl_macsec_validation_type {
	LKL_MACSEC_VALIDATE_DISABLED = 0,
	LKL_MACSEC_VALIDATE_CHECK = 1,
	LKL_MACSEC_VALIDATE_STRICT = 2,
	__LKL__MACSEC_VALIDATE_END,
	LKL_MACSEC_VALIDATE_MAX = __LKL__MACSEC_VALIDATE_END - 1,
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

/* VXLAN section */
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
	__LKL__IFLA_VXLAN_MAX
};
#define LKL_IFLA_VXLAN_MAX	(__LKL__IFLA_VXLAN_MAX - 1)

struct lkl_ifla_vxlan_port_range {
	__lkl__be16	low;
	__lkl__be16	high;
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
	__LKL__IFLA_GENEVE_MAX
};
#define LKL_IFLA_GENEVE_MAX	(__LKL__IFLA_GENEVE_MAX - 1)

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
	__LKL__IFLA_VF_MAX,
};

#define LKL_IFLA_VF_MAX (__LKL__IFLA_VF_MAX - 1)

struct lkl_ifla_vf_mac {
	__lkl__u32 vf;
	__lkl__u8 mac[32]; /* MAX_ADDR_LEN */
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


/* HSR section */

enum {
	LKL_IFLA_HSR_UNSPEC,
	LKL_IFLA_HSR_SLAVE1,
	LKL_IFLA_HSR_SLAVE2,
	LKL_IFLA_HSR_MULTICAST_SPEC,	/* Last byte of supervision addr */
	LKL_IFLA_HSR_SUPERVISION_ADDR,	/* Supervision frame multicast addr */
	LKL_IFLA_HSR_SEQ_NR,
	LKL_IFLA_HSR_VERSION,		/* HSR version */
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

/* These are embedded into LKL_IFLA_STATS_LINK_XSTATS:
 * [LKL_IFLA_STATS_LINK_XSTATS]
 * -> [LINK_XSTATS_TYPE_xxx]
 *    -> [rtnl link type specific attributes]
 */
enum {
	LKL_LINK_XSTATS_TYPE_UNSPEC,
	LKL_LINK_XSTATS_TYPE_BRIDGE,
	__LKL__LINK_XSTATS_TYPE_MAX
};
#define LKL_LINK_XSTATS_TYPE_MAX (__LKL__LINK_XSTATS_TYPE_MAX - 1)

/* These are stats embedded into LKL_IFLA_STATS_LINK_OFFLOAD_XSTATS */
enum {
	LKL_IFLA_OFFLOAD_XSTATS_UNSPEC,
	LKL_IFLA_OFFLOAD_XSTATS_CPU_HIT, /* struct lkl_rtnl_link_stats64 */
	__LKL__IFLA_OFFLOAD_XSTATS_MAX
};
#define LKL_IFLA_OFFLOAD_XSTATS_MAX (__LKL__IFLA_OFFLOAD_XSTATS_MAX - 1)

/* XDP section */

#define LKL_XDP_FLAGS_UPDATE_IF_NOEXIST	(1U << 0)
#define LKL_XDP_FLAGS_SKB_MODE		(1U << 1)
#define LKL_XDP_FLAGS_DRV_MODE		(1U << 2)
#define LKL_XDP_FLAGS_HW_MODE		(1U << 3)
#define LKL_XDP_FLAGS_MODES			(LKL_XDP_FLAGS_SKB_MODE | \
					 LKL_XDP_FLAGS_DRV_MODE | \
					 LKL_XDP_FLAGS_HW_MODE)
#define LKL_XDP_FLAGS_MASK			(LKL_XDP_FLAGS_UPDATE_IF_NOEXIST | \
					 LKL_XDP_FLAGS_MODES)

/* These are stored into LKL_IFLA_XDP_ATTACHED on dump. */
enum {
	LKL_XDP_ATTACHED_NONE = 0,
	LKL_XDP_ATTACHED_DRV,
	LKL_XDP_ATTACHED_SKB,
	LKL_XDP_ATTACHED_HW,
};

enum {
	LKL_IFLA_XDP_UNSPEC,
	LKL_IFLA_XDP_FD,
	LKL_IFLA_XDP_ATTACHED,
	LKL_IFLA_XDP_FLAGS,
	LKL_IFLA_XDP_PROG_ID,
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

#endif /* _LKL_LINUX_IF_LINK_H */
