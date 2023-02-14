/* SPDX-License-Identifier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Global definitions for the INET interface module.
 *
 * Version:	@(#)if.h	1.0.2	04/18/93
 *
 * Authors:	Original taken from Berkeley UNIX 4.3, (c) UCB 1982-1988
 *		Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#ifndef _LKL_LINUX_IF_H
#define _LKL_LINUX_IF_H

#include <lkl/linux/libc-compat.h>          /* for compatibility with glibc */
#include <lkl/linux/types.h>		/* for "__lkl__kernel_caddr_t" et al	*/
#include <lkl/linux/socket.h>		/* for "struct lkl_sockaddr" et al	*/
		/* for "__lkl__user" et al           */

#include <sys/socket.h>			/* for struct lkl_sockaddr.		*/

#if __LKL__UAPI_DEF_IF_IFNAMSIZ
#define	LKL_IFNAMSIZ	16
#endif /* __LKL__UAPI_DEF_IF_IFNAMSIZ */
#define	LKL_IFALIASZ	256
#include <lkl/linux/hdlc/ioctl.h>

/* For glibc compatibility. An empty enum does not compile. */
#if __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO != 0 || \
    __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS != 0
/**
 * enum lkl_net_device_flags - &struct net_device flags
 *
 * These are the &struct net_device flags, they can be set by drivers, the
 * kernel and some can be triggered by userspace. Userspace can query and
 * set these flags using userspace utilities but there is also a sysfs
 * entry available for all dev flags which can be queried and set. These flags
 * are shared for all types of net_devices. The sysfs entries are available
 * via /sys/class/net/<dev>/flags. Flags which can be toggled through sysfs
 * are annotated below, note that only a few flags can be toggled and some
 * other flags are always preserved from the original net_device flags
 * even if you try to set them via sysfs. Flags which are always preserved
 * are kept under the flag grouping @LKL_IFF_VOLATILE. Flags which are __volatile__
 * are annotated below as such.
 *
 * You should have a pretty good reason to be extending these flags.
 *
 * @LKL_IFF_UP: interface is up. Can be toggled through sysfs.
 * @LKL_IFF_BROADCAST: broadcast address valid. Volatile.
 * @LKL_IFF_DEBUG: turn on debugging. Can be toggled through sysfs.
 * @LKL_IFF_LOOPBACK: is a loopback net. Volatile.
 * @LKL_IFF_POINTOPOINT: interface is has p-p link. Volatile.
 * @LKL_IFF_NOTRAILERS: avoid use of trailers. Can be toggled through sysfs.
 *	Volatile.
 * @LKL_IFF_RUNNING: interface RFC2863 OPER_UP. Volatile.
 * @LKL_IFF_NOARP: no ARP protocol. Can be toggled through sysfs. Volatile.
 * @LKL_IFF_PROMISC: receive all packets. Can be toggled through sysfs.
 * @LKL_IFF_ALLMULTI: receive all multicast packets. Can be toggled through
 *	sysfs.
 * @LKL_IFF_MASTER: master of a load balancer. Volatile.
 * @LKL_IFF_SLAVE: slave of a load balancer. Volatile.
 * @LKL_IFF_MULTICAST: Supports multicast. Can be toggled through sysfs.
 * @LKL_IFF_PORTSEL: can set media type. Can be toggled through sysfs.
 * @LKL_IFF_AUTOMEDIA: auto media select active. Can be toggled through sysfs.
 * @LKL_IFF_DYNAMIC: dialup device with changing addresses. Can be toggled
 *	through sysfs.
 * @LKL_IFF_LOWER_UP: driver signals L1 up. Volatile.
 * @LKL_IFF_DORMANT: driver signals dormant. Volatile.
 * @LKL_IFF_ECHO: echo sent packets. Volatile.
 */
enum lkl_net_device_flags {
/* for compatibility with glibc net/if.h */
#if __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS
	LKL_IFF_UP				= 1<<0,  /* sysfs */
	LKL_IFF_BROADCAST			= 1<<1,  /* __volatile__ */
	LKL_IFF_DEBUG			= 1<<2,  /* sysfs */
	LKL_IFF_LOOPBACK			= 1<<3,  /* __volatile__ */
	LKL_IFF_POINTOPOINT			= 1<<4,  /* __volatile__ */
	LKL_IFF_NOTRAILERS			= 1<<5,  /* sysfs */
	LKL_IFF_RUNNING			= 1<<6,  /* __volatile__ */
	LKL_IFF_NOARP			= 1<<7,  /* sysfs */
	LKL_IFF_PROMISC			= 1<<8,  /* sysfs */
	LKL_IFF_ALLMULTI			= 1<<9,  /* sysfs */
	LKL_IFF_MASTER			= 1<<10, /* __volatile__ */
	LKL_IFF_SLAVE			= 1<<11, /* __volatile__ */
	LKL_IFF_MULTICAST			= 1<<12, /* sysfs */
	LKL_IFF_PORTSEL			= 1<<13, /* sysfs */
	LKL_IFF_AUTOMEDIA			= 1<<14, /* sysfs */
	LKL_IFF_DYNAMIC			= 1<<15, /* sysfs */
#endif /* __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS */
#if __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO
	LKL_IFF_LOWER_UP			= 1<<16, /* __volatile__ */
	LKL_IFF_DORMANT			= 1<<17, /* __volatile__ */
	LKL_IFF_ECHO			= 1<<18, /* __volatile__ */
#endif /* __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO */
};
#endif /* __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO != 0 || __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS != 0 */

/* for compatibility with glibc net/if.h */
#if __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS
#define LKL_IFF_UP				LKL_IFF_UP
#define LKL_IFF_BROADCAST			LKL_IFF_BROADCAST
#define LKL_IFF_DEBUG			LKL_IFF_DEBUG
#define LKL_IFF_LOOPBACK			LKL_IFF_LOOPBACK
#define LKL_IFF_POINTOPOINT			LKL_IFF_POINTOPOINT
#define LKL_IFF_NOTRAILERS			LKL_IFF_NOTRAILERS
#define LKL_IFF_RUNNING			LKL_IFF_RUNNING
#define LKL_IFF_NOARP			LKL_IFF_NOARP
#define LKL_IFF_PROMISC			LKL_IFF_PROMISC
#define LKL_IFF_ALLMULTI			LKL_IFF_ALLMULTI
#define LKL_IFF_MASTER			LKL_IFF_MASTER
#define LKL_IFF_SLAVE			LKL_IFF_SLAVE
#define LKL_IFF_MULTICAST			LKL_IFF_MULTICAST
#define LKL_IFF_PORTSEL			LKL_IFF_PORTSEL
#define LKL_IFF_AUTOMEDIA			LKL_IFF_AUTOMEDIA
#define LKL_IFF_DYNAMIC			LKL_IFF_DYNAMIC
#endif /* __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS */

#if __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO
#define LKL_IFF_LOWER_UP			LKL_IFF_LOWER_UP
#define LKL_IFF_DORMANT			LKL_IFF_DORMANT
#define LKL_IFF_ECHO			LKL_IFF_ECHO
#endif /* __LKL__UAPI_DEF_IF_NET_DEVICE_FLAGS_LOWER_UP_DORMANT_ECHO */

#define LKL_IFF_VOLATILE	(LKL_IFF_LOOPBACK|LKL_IFF_POINTOPOINT|LKL_IFF_BROADCAST|LKL_IFF_ECHO|\
		LKL_IFF_MASTER|LKL_IFF_SLAVE|LKL_IFF_RUNNING|LKL_IFF_LOWER_UP|LKL_IFF_DORMANT)

#define LKL_IF_GET_IFACE	0x0001		/* for querying only */
#define LKL_IF_GET_PROTO	0x0002

/* For definitions see hdlc.h */
#define LKL_IF_IFACE_V35	0x1000		/* V.35 serial interface	*/
#define LKL_IF_IFACE_V24	0x1001		/* V.24 serial interface	*/
#define LKL_IF_IFACE_X21	0x1002		/* X.21 serial interface	*/
#define LKL_IF_IFACE_T1	0x1003		/* T1 telco serial interface	*/
#define LKL_IF_IFACE_E1	0x1004		/* E1 telco serial interface	*/
#define LKL_IF_IFACE_SYNC_SERIAL 0x1005	/* can't be set by software	*/
#define LKL_IF_IFACE_X21D   0x1006          /* X.21 Dual Clocking (FarSite) */

/* For definitions see hdlc.h */
#define LKL_IF_PROTO_HDLC	0x2000		/* raw HDLC protocol		*/
#define LKL_IF_PROTO_PPP	0x2001		/* PPP protocol			*/
#define LKL_IF_PROTO_CISCO	0x2002		/* Cisco HDLC protocol		*/
#define LKL_IF_PROTO_FR	0x2003		/* Frame Relay protocol		*/
#define LKL_IF_PROTO_FR_ADD_PVC 0x2004	/*    Create FR PVC		*/
#define LKL_IF_PROTO_FR_DEL_PVC 0x2005	/*    Delete FR PVC		*/
#define LKL_IF_PROTO_X25	0x2006		/* X.25				*/
#define LKL_IF_PROTO_HDLC_ETH 0x2007	/* raw HDLC, Ethernet emulation	*/
#define LKL_IF_PROTO_FR_ADD_ETH_PVC 0x2008	/*  Create FR Ethernet-bridged PVC */
#define LKL_IF_PROTO_FR_DEL_ETH_PVC 0x2009	/*  Delete FR Ethernet-bridged PVC */
#define LKL_IF_PROTO_FR_PVC	0x200A		/* for reading PVC status	*/
#define LKL_IF_PROTO_FR_ETH_PVC 0x200B
#define LKL_IF_PROTO_RAW    0x200C          /* RAW Socket                   */

/* RFC 2863 operational status */
enum {
	LKL_IF_OPER_UNKNOWN,
	LKL_IF_OPER_NOTPRESENT,
	LKL_IF_OPER_DOWN,
	LKL_IF_OPER_LOWERLAYERDOWN,
	LKL_IF_OPER_TESTING,
	LKL_IF_OPER_DORMANT,
	LKL_IF_OPER_UP,
};

/* link modes */
enum {
	LKL_IF_LINK_MODE_DEFAULT,
	LKL_IF_LINK_MODE_DORMANT,	/* limit upward transition to dormant */
};

/*
 *	Device mapping structure. I'd just gone off and designed a 
 *	beautiful scheme using only loadable modules with arguments
 *	for driver options and along come the PCMCIA people 8)
 *
 *	Ah well. The get() side of this is good for WDSETUP, and it'll
 *	be handy for debugging things. The set side is fine for now and
 *	being very small might be worth keeping for clean configuration.
 */

/* for compatibility with glibc net/if.h */
#if __LKL__UAPI_DEF_IF_IFMAP
struct lkl_ifmap {
	unsigned long mem_start;
	unsigned long mem_end;
	unsigned short base_addr; 
	unsigned char irq;
	unsigned char dma;
	unsigned char port;
	/* 3 bytes spare */
};
#endif /* __LKL__UAPI_DEF_IF_IFMAP */

struct lkl_if_settings {
	unsigned int type;	/* Type of physical device or protocol */
	unsigned int size;	/* Size of the data allocated by the caller */
	union {
		/* {atm/eth/dsl}_settings anyone ? */
		lkl_raw_hdlc_proto		*raw_hdlc;
		lkl_cisco_proto		*cisco;
		lkl_fr_proto		*fr;
		lkl_fr_proto_pvc		*fr_pvc;
		lkl_fr_proto_pvc_info	*fr_pvc_info;

		/* interface settings */
		lkl_sync_serial_settings	*sync;
		lkl_te1_settings		*te1;
	} ifs_ifsu;
};

/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with lkl_ifr_name.  The
 * remainder may be interface specific.
 */

/* for compatibility with glibc net/if.h */
#if __LKL__UAPI_DEF_IF_IFREQ
struct lkl_ifreq {
#define LKL_IFHWADDRLEN	6
	union
	{
		char	ifrn_name[LKL_IFNAMSIZ];		/* if name, e.g. "en0" */
	} ifr_ifrn;
	
	union {
		struct	lkl_sockaddr ifru_addr;
		struct	lkl_sockaddr ifru_dstaddr;
		struct	lkl_sockaddr ifru_broadaddr;
		struct	lkl_sockaddr ifru_netmask;
		struct  lkl_sockaddr ifru_hwaddr;
		short	ifru_flags;
		int	ifru_ivalue;
		int	ifru_mtu;
		struct  lkl_ifmap ifru_map;
		char	ifru_slave[LKL_IFNAMSIZ];	/* Just fits the size */
		char	ifru_newname[LKL_IFNAMSIZ];
		void *	ifru_data;
		struct	lkl_if_settings ifru_settings;
	} ifr_ifru;
};
#endif /* __LKL__UAPI_DEF_IF_IFREQ */

#define lkl_ifr_name	ifr_ifrn.ifrn_name	/* interface name 	*/
#define lkl_ifr_hwaddr	ifr_ifru.ifru_hwaddr	/* MAC address 		*/
#define	lkl_ifr_addr	ifr_ifru.ifru_addr	/* address		*/
#define	lkl_ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-p lnk	*/
#define	lkl_ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address	*/
#define	lkl_ifr_netmask	ifr_ifru.ifru_netmask	/* interface net mask	*/
#define	lkl_ifr_flags	ifr_ifru.ifru_flags	/* flags		*/
#define	lkl_ifr_metric	ifr_ifru.ifru_ivalue	/* metric		*/
#define	lkl_ifr_mtu		ifr_ifru.ifru_mtu	/* mtu			*/
#define lkl_ifr_map		ifr_ifru.ifru_map	/* device map		*/
#define lkl_ifr_slave	ifr_ifru.ifru_slave	/* slave device		*/
#define	lkl_ifr_data	ifr_ifru.ifru_data	/* for use by interface	*/
#define lkl_ifr_ifindex	ifr_ifru.ifru_ivalue	/* interface index	*/
#define lkl_ifr_bandwidth	ifr_ifru.ifru_ivalue    /* link bandwidth	*/
#define lkl_ifr_qlen	ifr_ifru.ifru_ivalue	/* Queue length 	*/
#define lkl_ifr_newname	ifr_ifru.ifru_newname	/* New name		*/
#define lkl_ifr_settings	ifr_ifru.ifru_settings	/* Device/proto settings*/

/*
 * Structure used in LKL_SIOCGIFCONF request.
 * Used to retrieve interface configuration
 * for machine (useful for programs which
 * must know all networks accessible).
 */

/* for compatibility with glibc net/if.h */
#if __LKL__UAPI_DEF_IF_IFCONF
struct lkl_ifconf  {
	int	ifc_len;			/* size of buffer	*/
	union {
		char *ifcu_buf;
		struct lkl_ifreq *ifcu_req;
	} ifc_ifcu;
};
#endif /* __LKL__UAPI_DEF_IF_IFCONF */

#define	lkl_ifc_buf	ifc_ifcu.ifcu_buf		/* buffer address	*/
#define	lkl_ifc_req	ifc_ifcu.ifcu_req		/* array of structures	*/

#endif /* _LKL_LINUX_IF_H */
