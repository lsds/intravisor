/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__LINUX_FIB_RULES_H
#define __LKL__LINUX_FIB_RULES_H

#include <lkl/linux/types.h>
#include <lkl/linux/rtnetlink.h>

/* rule is permanent, and cannot be deleted */
#define LKL_FIB_RULE_PERMANENT	0x00000001
#define LKL_FIB_RULE_INVERT		0x00000002
#define LKL_FIB_RULE_UNRESOLVED	0x00000004
#define LKL_FIB_RULE_IIF_DETACHED	0x00000008
#define LKL_FIB_RULE_DEV_DETACHED	LKL_FIB_RULE_IIF_DETACHED
#define LKL_FIB_RULE_OIF_DETACHED	0x00000010

/* try to find source address in routing lookups */
#define LKL_FIB_RULE_FIND_SADDR	0x00010000

struct lkl_fib_rule_hdr {
	__lkl__u8		family;
	__lkl__u8		dst_len;
	__lkl__u8		src_len;
	__lkl__u8		tos;

	__lkl__u8		table;
	__lkl__u8		res1;   /* reserved */
	__lkl__u8		res2;	/* reserved */
	__lkl__u8		action;

	__lkl__u32		flags;
};

struct lkl_fib_rule_uid_range {
	__lkl__u32		start;
	__lkl__u32		end;
};

struct lkl_fib_rule_port_range {
	__lkl__u16		start;
	__lkl__u16		end;
};

enum {
	LKL_FRA_UNSPEC,
	LKL_FRA_DST,	/* destination address */
	LKL_FRA_SRC,	/* source address */
	LKL_FRA_IIFNAME,	/* interface name */
#define LKL_FRA_IFNAME	LKL_FRA_IIFNAME
	LKL_FRA_GOTO,	/* target to jump to (LKL_FR_ACT_GOTO) */
	LKL_FRA_UNUSED2,
	LKL_FRA_PRIORITY,	/* priority/preference */
	LKL_FRA_UNUSED3,
	LKL_FRA_UNUSED4,
	LKL_FRA_UNUSED5,
	LKL_FRA_FWMARK,	/* mark */
	LKL_FRA_FLOW,	/* flow/class id */
	LKL_FRA_TUN_ID,
	LKL_FRA_SUPPRESS_IFGROUP,
	LKL_FRA_SUPPRESS_PREFIXLEN,
	LKL_FRA_TABLE,	/* Extended table id */
	LKL_FRA_FWMASK,	/* mask for netfilter mark */
	LKL_FRA_OIFNAME,
	LKL_FRA_PAD,
	LKL_FRA_L3MDEV,	/* iif or oif is l3mdev goto its table */
	LKL_FRA_UID_RANGE,	/* UID range */
	LKL_FRA_PROTOCOL,   /* Originator of the rule */
	LKL_FRA_IP_PROTO,	/* ip proto */
	LKL_FRA_SPORT_RANGE, /* sport */
	LKL_FRA_DPORT_RANGE, /* dport */
	__LKL__FRA_MAX
};

#define LKL_FRA_MAX (__LKL__FRA_MAX - 1)

enum {
	LKL_FR_ACT_UNSPEC,
	LKL_FR_ACT_TO_TBL,		/* Pass to fixed table */
	LKL_FR_ACT_GOTO,		/* Jump to another rule */
	LKL_FR_ACT_NOP,		/* No operation */
	LKL_FR_ACT_RES3,
	LKL_FR_ACT_RES4,
	LKL_FR_ACT_BLACKHOLE,	/* Drop without notification */
	LKL_FR_ACT_UNREACHABLE,	/* Drop with LKL_ENETUNREACH */
	LKL_FR_ACT_PROHIBIT,	/* Drop with LKL_EACCES */
	__LKL__FR_ACT_MAX,
};

#define LKL_FR_ACT_MAX (__LKL__FR_ACT_MAX - 1)

#endif
