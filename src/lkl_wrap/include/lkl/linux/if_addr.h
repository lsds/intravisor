/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__LINUX_IF_ADDR_H
#define __LKL__LINUX_IF_ADDR_H

#include <lkl/linux/types.h>
#include <lkl/linux/netlink.h>

struct lkl_ifaddrmsg {
	__lkl__u8		ifa_family;
	__lkl__u8		ifa_prefixlen;	/* The prefix length		*/
	__lkl__u8		ifa_flags;	/* Flags			*/
	__lkl__u8		ifa_scope;	/* Address scope		*/
	__lkl__u32		ifa_index;	/* Link index			*/
};

/*
 * Important comment:
 * LKL_IFA_ADDRESS is prefix address, rather than local interface address.
 * It makes no difference for normally configured broadcast interfaces,
 * but for point-to-point LKL_IFA_ADDRESS is DESTINATION address,
 * local address is supplied in LKL_IFA_LOCAL attribute.
 *
 * LKL_IFA_FLAGS is a lkl_u32 attribute that extends the u8 field ifa_flags.
 * If present, the value from struct lkl_ifaddrmsg will be ignored.
 */
enum {
	LKL_IFA_UNSPEC,
	LKL_IFA_ADDRESS,
	LKL_IFA_LOCAL,
	LKL_IFA_LABEL,
	LKL_IFA_BROADCAST,
	LKL_IFA_ANYCAST,
	LKL_IFA_CACHEINFO,
	LKL_IFA_MULTICAST,
	LKL_IFA_FLAGS,
	__LKL__IFA_MAX,
};

#define LKL_IFA_MAX (__LKL__IFA_MAX - 1)

/* ifa_flags */
#define LKL_IFA_F_SECONDARY		0x01
#define LKL_IFA_F_TEMPORARY		LKL_IFA_F_SECONDARY

#define	LKL_IFA_F_NODAD		0x02
#define LKL_IFA_F_OPTIMISTIC	0x04
#define LKL_IFA_F_DADFAILED		0x08
#define	LKL_IFA_F_HOMEADDRESS	0x10
#define LKL_IFA_F_DEPRECATED	0x20
#define LKL_IFA_F_TENTATIVE		0x40
#define LKL_IFA_F_PERMANENT		0x80
#define LKL_IFA_F_MANAGETEMPADDR	0x100
#define LKL_IFA_F_NOPREFIXROUTE	0x200
#define LKL_IFA_F_MCAUTOJOIN	0x400
#define LKL_IFA_F_STABLE_PRIVACY	0x800

struct lkl_ifa_cacheinfo {
	__lkl__u32	ifa_prefered;
	__lkl__u32	ifa_valid;
	__lkl__u32	cstamp; /* created timestamp, hundredths of seconds */
	__lkl__u32	tstamp; /* updated timestamp, hundredths of seconds */
};

/* backwards compatibility for userspace */
#define LKL_IFA_RTA(r)  ((struct lkl_rtattr*)(((char*)(r)) + LKL_NLMSG_ALIGN(sizeof(struct lkl_ifaddrmsg))))
#define LKL_IFA_PAYLOAD(n) LKL_NLMSG_PAYLOAD(n,sizeof(struct lkl_ifaddrmsg))

#endif
