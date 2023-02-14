/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#ifndef __LKL__LINUX_BPF_H__
#define __LKL__LINUX_BPF_H__

#include <lkl/linux/types.h>
#include <lkl/linux/bpf_common.h>

/* Extended instruction set based on top of classic BPF */

/* instruction classes */
#define LKL_BPF_ALU64	0x07	/* alu mode in double word width */

/* ld/ldx fields */
#define LKL_BPF_DW		0x18	/* double word (64-bit) */
#define LKL_BPF_XADD	0xc0	/* exclusive add */

/* alu/jmp fields */
#define LKL_BPF_MOV		0xb0	/* mov reg to reg */
#define LKL_BPF_ARSH	0xc0	/* sign extending arithmetic shift right */

/* change endianness of a register */
#define LKL_BPF_END		0xd0	/* flags for endianness conversion: */
#define LKL_BPF_TO_LE	0x00	/* convert to little-endian */
#define LKL_BPF_TO_BE	0x08	/* convert to big-endian */
#define LKL_BPF_FROM_LE	LKL_BPF_TO_LE
#define LKL_BPF_FROM_BE	LKL_BPF_TO_BE

/* jmp encodings */
#define LKL_BPF_JNE		0x50	/* jump != */
#define LKL_BPF_JLT		0xa0	/* LT is unsigned, '<' */
#define LKL_BPF_JLE		0xb0	/* LE is unsigned, '<=' */
#define LKL_BPF_JSGT	0x60	/* SGT is signed '>', GT in x86 */
#define LKL_BPF_JSGE	0x70	/* SGE is signed '>=', GE in x86 */
#define LKL_BPF_JSLT	0xc0	/* SLT is signed, '<' */
#define LKL_BPF_JSLE	0xd0	/* SLE is signed, '<=' */
#define LKL_BPF_CALL	0x80	/* function call */
#define LKL_BPF_EXIT	0x90	/* function return */

/* Register numbers */
enum {
	LKL_BPF_REG_0 = 0,
	LKL_BPF_REG_1,
	LKL_BPF_REG_2,
	LKL_BPF_REG_3,
	LKL_BPF_REG_4,
	LKL_BPF_REG_5,
	LKL_BPF_REG_6,
	LKL_BPF_REG_7,
	LKL_BPF_REG_8,
	LKL_BPF_REG_9,
	LKL_BPF_REG_10,
	__LKL__MAX_BPF_REG,
};

/* BPF has 10 general purpose 64-bit registers and stack frame. */
#define LKL_MAX_BPF_REG	__LKL__MAX_BPF_REG

struct lkl_bpf_insn {
	__lkl__u8	code;		/* opcode */
	__lkl__u8	dst_reg:4;	/* dest register */
	__lkl__u8	src_reg:4;	/* source register */
	__lkl__s16	off;		/* signed offset */
	__lkl__s32	imm;		/* signed immediate constant */
};

/* Key of an a LKL_BPF_MAP_TYPE_LPM_TRIE entry */
struct lkl_bpf_lpm_trie_key {
	__lkl__u32	prefixlen;	/* up to 32 for LKL_AF_INET, 128 for LKL_AF_INET6 */
	__lkl__u8	data[0];	/* Arbitrary size */
};

/* BPF syscall commands, see bpf(2) man-page for details. */
enum lkl_bpf_cmd {
	LKL_BPF_MAP_CREATE,
	LKL_BPF_MAP_LOOKUP_ELEM,
	LKL_BPF_MAP_UPDATE_ELEM,
	LKL_BPF_MAP_DELETE_ELEM,
	LKL_BPF_MAP_GET_NEXT_KEY,
	LKL_BPF_PROG_LOAD,
	LKL_BPF_OBJ_PIN,
	LKL_BPF_OBJ_GET,
	LKL_BPF_PROG_ATTACH,
	LKL_BPF_PROG_DETACH,
	LKL_BPF_PROG_TEST_RUN,
	LKL_BPF_PROG_GET_NEXT_ID,
	LKL_BPF_MAP_GET_NEXT_ID,
	LKL_BPF_PROG_GET_FD_BY_ID,
	LKL_BPF_MAP_GET_FD_BY_ID,
	LKL_BPF_OBJ_GET_INFO_BY_FD,
	LKL_BPF_PROG_QUERY,
	LKL_BPF_RAW_TRACEPOINT_OPEN,
};

enum lkl_bpf_map_type {
	LKL_BPF_MAP_TYPE_UNSPEC,
	LKL_BPF_MAP_TYPE_HASH,
	LKL_BPF_MAP_TYPE_ARRAY,
	LKL_BPF_MAP_TYPE_PROG_ARRAY,
	LKL_BPF_MAP_TYPE_PERF_EVENT_ARRAY,
	LKL_BPF_MAP_TYPE_PERCPU_HASH,
	LKL_BPF_MAP_TYPE_PERCPU_ARRAY,
	LKL_BPF_MAP_TYPE_STACK_TRACE,
	LKL_BPF_MAP_TYPE_CGROUP_ARRAY,
	LKL_BPF_MAP_TYPE_LRU_HASH,
	LKL_BPF_MAP_TYPE_LRU_PERCPU_HASH,
	LKL_BPF_MAP_TYPE_LPM_TRIE,
	LKL_BPF_MAP_TYPE_ARRAY_OF_MAPS,
	LKL_BPF_MAP_TYPE_HASH_OF_MAPS,
	LKL_BPF_MAP_TYPE_DEVMAP,
	LKL_BPF_MAP_TYPE_SOCKMAP,
	LKL_BPF_MAP_TYPE_CPUMAP,
};

enum lkl_bpf_prog_type {
	LKL_BPF_PROG_TYPE_UNSPEC,
	LKL_BPF_PROG_TYPE_SOCKET_FILTER,
	LKL_BPF_PROG_TYPE_KPROBE,
	LKL_BPF_PROG_TYPE_SCHED_CLS,
	LKL_BPF_PROG_TYPE_SCHED_ACT,
	LKL_BPF_PROG_TYPE_TRACEPOINT,
	LKL_BPF_PROG_TYPE_XDP,
	LKL_BPF_PROG_TYPE_PERF_EVENT,
	LKL_BPF_PROG_TYPE_CGROUP_SKB,
	LKL_BPF_PROG_TYPE_CGROUP_SOCK,
	LKL_BPF_PROG_TYPE_LWT_IN,
	LKL_BPF_PROG_TYPE_LWT_OUT,
	LKL_BPF_PROG_TYPE_LWT_XMIT,
	LKL_BPF_PROG_TYPE_SOCK_OPS,
	LKL_BPF_PROG_TYPE_SK_SKB,
	LKL_BPF_PROG_TYPE_CGROUP_DEVICE,
	LKL_BPF_PROG_TYPE_SK_MSG,
	LKL_BPF_PROG_TYPE_RAW_TRACEPOINT,
	LKL_BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
};

enum lkl_bpf_attach_type {
	LKL_BPF_CGROUP_INET_INGRESS,
	LKL_BPF_CGROUP_INET_EGRESS,
	LKL_BPF_CGROUP_INET_SOCK_CREATE,
	LKL_BPF_CGROUP_SOCK_OPS,
	LKL_BPF_SK_SKB_STREAM_PARSER,
	LKL_BPF_SK_SKB_STREAM_VERDICT,
	LKL_BPF_CGROUP_DEVICE,
	LKL_BPF_SK_MSG_VERDICT,
	LKL_BPF_CGROUP_INET4_BIND,
	LKL_BPF_CGROUP_INET6_BIND,
	LKL_BPF_CGROUP_INET4_CONNECT,
	LKL_BPF_CGROUP_INET6_CONNECT,
	LKL_BPF_CGROUP_INET4_POST_BIND,
	LKL_BPF_CGROUP_INET6_POST_BIND,
	__LKL__MAX_BPF_ATTACH_TYPE
};

#define LKL_MAX_BPF_ATTACH_TYPE __LKL__MAX_BPF_ATTACH_TYPE

/* cgroup-bpf attach flags used in LKL_BPF_PROG_ATTACH command
 *
 * NONE(default): No further bpf programs allowed in the subtree.
 *
 * LKL_BPF_F_ALLOW_OVERRIDE: If a sub-cgroup installs some bpf program,
 * the program in this cgroup yields to sub-cgroup program.
 *
 * LKL_BPF_F_ALLOW_MULTI: If a sub-cgroup installs some bpf program,
 * that cgroup program gets run in addition to the program in this cgroup.
 *
 * Only one program is allowed to be attached to a cgroup with
 * NONE or LKL_BPF_F_ALLOW_OVERRIDE flag.
 * Attaching another program on top of NONE or LKL_BPF_F_ALLOW_OVERRIDE will
 * release old program and attach the new one. Attach flags has to match.
 *
 * Multiple programs are allowed to be attached to a cgroup with
 * LKL_BPF_F_ALLOW_MULTI flag. They are executed in FIFO order
 * (those that were attached first, run first)
 * The programs of sub-cgroup are executed first, then programs of
 * this cgroup and then programs of parent cgroup.
 * When children program makes decision (like picking TCP CA or sock bind)
 * parent program has a chance to override it.
 *
 * A cgroup with MULTI or OVERRIDE flag allows any attach flags in sub-cgroups.
 * A cgroup with NONE doesn't allow any programs in sub-cgroups.
 * Ex1:
 * cgrp1 (MULTI progs A, B) ->
 *    cgrp2 (OVERRIDE prog C) ->
 *      cgrp3 (MULTI prog D) ->
 *        cgrp4 (OVERRIDE prog E) ->
 *          cgrp5 (NONE prog F)
 * the event in cgrp5 triggers execution of F,D,A,B in that order.
 * if prog F is detached, the execution is E,D,A,B
 * if prog F and D are detached, the execution is E,A,B
 * if prog F, E and D are detached, the execution is C,A,B
 *
 * All eligible programs are executed regardless of return code from
 * earlier programs.
 */
#define LKL_BPF_F_ALLOW_OVERRIDE	(1U << 0)
#define LKL_BPF_F_ALLOW_MULTI	(1U << 1)

/* If LKL_BPF_F_STRICT_ALIGNMENT is used in LKL_BPF_PROG_LOAD command, the
 * verifier will perform strict alignment checking as if the kernel
 * has been built with CONFIG_EFFICIENT_UNALIGNED_ACCESS not set,
 * and NET_IP_ALIGN defined to 2.
 */
#define LKL_BPF_F_STRICT_ALIGNMENT	(1U << 0)

/* when bpf_ldimm64->src_reg == LKL_BPF_PSEUDO_MAP_FD, bpf_ldimm64->imm == fd */
#define LKL_BPF_PSEUDO_MAP_FD	1

/* when bpf_call->src_reg == LKL_BPF_PSEUDO_CALL, bpf_call->imm == pc-relative
 * offset to another bpf function
 */
#define LKL_BPF_PSEUDO_CALL		1

/* flags for LKL_BPF_MAP_UPDATE_ELEM command */
#define LKL_BPF_ANY		0 /* create new element or update existing */
#define LKL_BPF_NOEXIST	1 /* create new element if it didn't exist */
#define LKL_BPF_EXIST	2 /* update existing element */

/* flags for LKL_BPF_MAP_CREATE command */
#define LKL_BPF_F_NO_PREALLOC	(1U << 0)
/* Instead of having one common LRU list in the
 * BPF_MAP_TYPE_LRU_[PERCPU_]HASH map, use a percpu LRU list
 * which can scale and perform better.
 * Note, the LRU nodes (including free nodes) cannot be moved
 * across different LRU lists.
 */
#define LKL_BPF_F_NO_COMMON_LRU	(1U << 1)
/* Specify numa node during map creation */
#define LKL_BPF_F_NUMA_NODE		(1U << 2)

/* flags for LKL_BPF_PROG_QUERY */
#define LKL_BPF_F_QUERY_EFFECTIVE	(1U << 0)

#define LKL_BPF_OBJ_NAME_LEN 16U

/* Flags for accessing BPF object */
#define LKL_BPF_F_RDONLY		(1U << 3)
#define LKL_BPF_F_WRONLY		(1U << 4)

/* Flag for stack_map, store build_id+offset instead of pointer */
#define LKL_BPF_F_STACK_BUILD_ID	(1U << 5)

enum lkl_bpf_stack_build_id_status {
	/* user space need an empty entry to identify end of a trace */
	LKL_BPF_STACK_BUILD_ID_EMPTY = 0,
	/* with valid build_id and offset */
	LKL_BPF_STACK_BUILD_ID_VALID = 1,
	/* couldn't get build_id, fallback to ip */
	LKL_BPF_STACK_BUILD_ID_IP = 2,
};

#define LKL_BPF_BUILD_ID_SIZE 20
struct lkl_bpf_stack_build_id {
	__lkl__s32		status;
	unsigned char	build_id[LKL_BPF_BUILD_ID_SIZE];
	union {
		__lkl__u64	offset;
		__lkl__u64	ip;
	};
};

union lkl_bpf_attr {
	struct { /* anonymous struct used by LKL_BPF_MAP_CREATE command */
		__lkl__u32	map_type;	/* one of enum lkl_bpf_map_type */
		__lkl__u32	key_size;	/* size of key in bytes */
		__lkl__u32	value_size;	/* size of value in bytes */
		__lkl__u32	max_entries;	/* max number of entries in a map */
		__lkl__u32	map_flags;	/* LKL_BPF_MAP_CREATE related
					 * flags defined above.
					 */
		__lkl__u32	inner_map_fd;	/* fd pointing to the inner map */
		__lkl__u32	numa_node;	/* numa node (effective only if
					 * LKL_BPF_F_NUMA_NODE is set).
					 */
		char	map_name[LKL_BPF_OBJ_NAME_LEN];
		__lkl__u32	map_ifindex;	/* ifindex of netdev to create on */
	};

	struct { /* anonymous struct used by BPF_MAP_*_ELEM commands */
		__lkl__u32		map_fd;
		__lkl__aligned_u64	key;
		union {
			__lkl__aligned_u64 value;
			__lkl__aligned_u64 next_key;
		};
		__lkl__u64		flags;
	};

	struct { /* anonymous struct used by LKL_BPF_PROG_LOAD command */
		__lkl__u32		prog_type;	/* one of enum lkl_bpf_prog_type */
		__lkl__u32		insn_cnt;
		__lkl__aligned_u64	insns;
		__lkl__aligned_u64	license;
		__lkl__u32		log_level;	/* verbosity level of verifier */
		__lkl__u32		log_size;	/* size of user buffer */
		__lkl__aligned_u64	log_buf;	/* user supplied buffer */
		__lkl__u32		kern_version;	/* checked when prog_type=kprobe */
		__lkl__u32		prog_flags;
		char		prog_name[LKL_BPF_OBJ_NAME_LEN];
		__lkl__u32		prog_ifindex;	/* ifindex of netdev to prep for */
		/* For some prog types expected attach type must be known at
		 * load time to verify attach type specific parts of prog
		 * (context accesses, allowed helpers, etc).
		 */
		__lkl__u32		expected_attach_type;
	};

	struct { /* anonymous struct used by BPF_OBJ_* commands */
		__lkl__aligned_u64	pathname;
		__lkl__u32		bpf_fd;
		__lkl__u32		file_flags;
	};

	struct { /* anonymous struct used by LKL_BPF_PROG_ATTACH/DETACH commands */
		__lkl__u32		target_fd;	/* container object to attach to */
		__lkl__u32		attach_bpf_fd;	/* eBPF program to attach */
		__lkl__u32		attach_type;
		__lkl__u32		attach_flags;
	};

	struct { /* anonymous struct used by LKL_BPF_PROG_TEST_RUN command */
		__lkl__u32		prog_fd;
		__lkl__u32		retval;
		__lkl__u32		data_size_in;
		__lkl__u32		data_size_out;
		__lkl__aligned_u64	data_in;
		__lkl__aligned_u64	data_out;
		__lkl__u32		repeat;
		__lkl__u32		duration;
	} test;

	struct { /* anonymous struct used by BPF_*_GET_*_ID */
		union {
			__lkl__u32		start_id;
			__lkl__u32		prog_id;
			__lkl__u32		map_id;
		};
		__lkl__u32		next_id;
		__lkl__u32		open_flags;
	};

	struct { /* anonymous struct used by LKL_BPF_OBJ_GET_INFO_BY_FD */
		__lkl__u32		bpf_fd;
		__lkl__u32		info_len;
		__lkl__aligned_u64	info;
	} info;

	struct { /* anonymous struct used by LKL_BPF_PROG_QUERY command */
		__lkl__u32		target_fd;	/* container object to query */
		__lkl__u32		attach_type;
		__lkl__u32		query_flags;
		__lkl__u32		attach_flags;
		__lkl__aligned_u64	prog_ids;
		__lkl__u32		prog_cnt;
	} query;

	struct {
		__lkl__u64 name;
		__lkl__u32 prog_fd;
	} raw_tracepoint;
} __attribute__((aligned(8)));

/* BPF helper function descriptions:
 *
 * void *bpf_map_lookup_elem(&map, &key)
 *     Return: Map value or NULL
 *
 * int bpf_map_update_elem(&map, &key, &value, flags)
 *     Return: 0 on success or negative error
 *
 * int bpf_map_delete_elem(&map, &key)
 *     Return: 0 on success or negative error
 *
 * int bpf_probe_read(void *dst, int size, void *src)
 *     Return: 0 on success or negative error
 *
 * lkl_u64 bpf_ktime_get_ns(void)
 *     Return: current ktime
 *
 * int bpf_trace_printk(const char *fmt, int fmt_size, ...)
 *     Return: length of buffer written or negative error
 *
 * lkl_u32 bpf_prandom_u32(void)
 *     Return: random value
 *
 * lkl_u32 bpf_raw_smp_processor_id(void)
 *     Return: SMP processor ID
 *
 * int bpf_skb_store_bytes(skb, offset, from, len, flags)
 *     store bytes into packet
 *     @skb: pointer to skb
 *     @offset: offset within packet from skb->mac_header
 *     @from: pointer where to copy bytes from
 *     @len: number of bytes to store into packet
 *     @flags: bit 0 - if true, recompute skb->csum
 *             other bits - reserved
 *     Return: 0 on success or negative error
 *
 * int bpf_l3_csum_replace(skb, offset, from, to, flags)
 *     recompute IP checksum
 *     @skb: pointer to skb
 *     @offset: offset within packet where IP checksum is located
 *     @from: old value of header field
 *     @to: new value of header field
 *     @flags: bits 0-3 - size of header field
 *             other bits - reserved
 *     Return: 0 on success or negative error
 *
 * int bpf_l4_csum_replace(skb, offset, from, to, flags)
 *     recompute TCP/UDP checksum
 *     @skb: pointer to skb
 *     @offset: offset within packet where TCP/UDP checksum is located
 *     @from: old value of header field
 *     @to: new value of header field
 *     @flags: bits 0-3 - size of header field
 *             bit 4 - is pseudo header
 *             other bits - reserved
 *     Return: 0 on success or negative error
 *
 * int bpf_tail_call(ctx, prog_array_map, index)
 *     jump into another BPF program
 *     @ctx: context pointer passed to next program
 *     @prog_array_map: pointer to map which type is LKL_BPF_MAP_TYPE_PROG_ARRAY
 *     @index: 32-bit index inside array that selects specific program to run
 *     Return: 0 on success or negative error
 *
 * int bpf_clone_redirect(skb, ifindex, flags)
 *     redirect to another netdev
 *     @skb: pointer to skb
 *     @ifindex: ifindex of the net device
 *     @flags: bit 0 - if set, redirect to ingress instead of egress
 *             other bits - reserved
 *     Return: 0 on success or negative error
 *
 * lkl_u64 bpf_get_current_pid_tgid(void)
 *     Return: current->tgid << 32 | current->pid
 *
 * lkl_u64 bpf_get_current_uid_gid(void)
 *     Return: current_gid << 32 | current_uid
 *
 * int bpf_get_current_comm(char *buf, int size_of_buf)
 *     stores current->comm into buf
 *     Return: 0 on success or negative error
 *
 * lkl_u32 bpf_get_cgroup_classid(skb)
 *     retrieve a proc's classid
 *     @skb: pointer to skb
 *     Return: classid if != 0
 *
 * int bpf_skb_vlan_push(skb, vlan_proto, vlan_tci)
 *     Return: 0 on success or negative error
 *
 * int bpf_skb_vlan_pop(skb)
 *     Return: 0 on success or negative error
 *
 * int bpf_skb_get_tunnel_key(skb, key, size, flags)
 * int bpf_skb_set_tunnel_key(skb, key, size, flags)
 *     retrieve or populate tunnel metadata
 *     @skb: pointer to skb
 *     @key: pointer to 'struct lkl_bpf_tunnel_key'
 *     @size: size of 'struct lkl_bpf_tunnel_key'
 *     @flags: room for future extensions
 *     Return: 0 on success or negative error
 *
 * lkl_u64 bpf_perf_event_read(map, flags)
 *     read perf event counter value
 *     @map: pointer to perf_event_array map
 *     @flags: index of event in the map or bitmask flags
 *     Return: value of perf event counter read or error code
 *
 * int bpf_redirect(ifindex, flags)
 *     redirect to another netdev
 *     @ifindex: ifindex of the net device
 *     @flags:
 *	  cls_bpf:
 *          bit 0 - if set, redirect to ingress instead of egress
 *          other bits - reserved
 *	  xdp_bpf:
 *	    all bits - reserved
 *     Return: cls_bpf: TC_ACT_REDIRECT on success or TC_ACT_SHOT on error
 *	       xdp_bfp: LKL_XDP_REDIRECT on success or XDP_ABORT on error
 * int bpf_redirect_map(map, key, flags)
 *     redirect to endpoint in map
 *     @map: pointer to dev map
 *     @key: index in map to lookup
 *     @flags: --
 *     Return: LKL_XDP_REDIRECT on success or XDP_ABORT on error
 *
 * lkl_u32 bpf_get_route_realm(skb)
 *     retrieve a dst's tclassid
 *     @skb: pointer to skb
 *     Return: realm if != 0
 *
 * int bpf_perf_event_output(ctx, map, flags, data, size)
 *     output perf raw sample
 *     @ctx: struct pt_regs*
 *     @map: pointer to perf_event_array map
 *     @flags: index of event in the map or bitmask flags
 *     @data: data on stack to be output as raw data
 *     @size: size of data
 *     Return: 0 on success or negative error
 *
 * int bpf_get_stackid(ctx, map, flags)
 *     walk user or kernel stack and return id
 *     @ctx: struct pt_regs*
 *     @map: pointer to stack_trace map
 *     @flags: bits 0-7 - numer of stack frames to skip
 *             bit 8 - collect user stack instead of kernel
 *             bit 9 - compare stacks by hash only
 *             bit 10 - if two different stacks hash into the same stackid
 *                      discard old
 *             other bits - reserved
 *     Return: >= 0 stackid on success or negative error
 *
 * lkl_s64 bpf_csum_diff(from, from_size, to, to_size, seed)
 *     calculate csum diff
 *     @from: raw from buffer
 *     @from_size: length of from buffer
 *     @to: raw to buffer
 *     @to_size: length of to buffer
 *     @seed: optional seed
 *     Return: csum result or negative error code
 *
 * int bpf_skb_get_tunnel_opt(skb, opt, size)
 *     retrieve tunnel options metadata
 *     @skb: pointer to skb
 *     @opt: pointer to raw tunnel option data
 *     @size: size of @opt
 *     Return: option size
 *
 * int bpf_skb_set_tunnel_opt(skb, opt, size)
 *     populate tunnel options metadata
 *     @skb: pointer to skb
 *     @opt: pointer to raw tunnel option data
 *     @size: size of @opt
 *     Return: 0 on success or negative error
 *
 * int bpf_skb_change_proto(skb, proto, flags)
 *     Change protocol of the skb. Currently supported is v4 -> v6,
 *     v6 -> v4 transitions. The helper will also resize the skb. eBPF
 *     program is expected to fill the new headers via skb_store_bytes
 *     and lX_csum_replace.
 *     @skb: pointer to skb
 *     @proto: new skb->protocol type
 *     @flags: reserved
 *     Return: 0 on success or negative error
 *
 * int bpf_skb_change_type(skb, type)
 *     Change packet type of skb.
 *     @skb: pointer to skb
 *     @type: new skb->pkt_type type
 *     Return: 0 on success or negative error
 *
 * int bpf_skb_under_cgroup(skb, map, index)
 *     Check cgroup2 membership of skb
 *     @skb: pointer to skb
 *     @map: pointer to bpf_map in LKL_BPF_MAP_TYPE_CGROUP_ARRAY type
 *     @index: index of the cgroup in the bpf_map
 *     Return:
 *       == 0 skb failed the cgroup2 descendant test
 *       == 1 skb succeeded the cgroup2 descendant test
 *        < 0 error
 *
 * lkl_u32 bpf_get_hash_recalc(skb)
 *     Retrieve and possibly recalculate skb->hash.
 *     @skb: pointer to skb
 *     Return: hash
 *
 * lkl_u64 bpf_get_current_task(void)
 *     Returns current task_struct
 *     Return: current
 *
 * int bpf_probe_write_user(void *dst, void *src, int len)
 *     safely attempt to write to a location
 *     @dst: destination address in userspace
 *     @src: source address on stack
 *     @len: number of bytes to copy
 *     Return: 0 on success or negative error
 *
 * int bpf_current_task_under_cgroup(map, index)
 *     Check cgroup2 membership of current task
 *     @map: pointer to bpf_map in LKL_BPF_MAP_TYPE_CGROUP_ARRAY type
 *     @index: index of the cgroup in the bpf_map
 *     Return:
 *       == 0 current failed the cgroup2 descendant test
 *       == 1 current succeeded the cgroup2 descendant test
 *        < 0 error
 *
 * int bpf_skb_change_tail(skb, len, flags)
 *     The helper will resize the skb to the given new size, to be used f.e.
 *     with control messages.
 *     @skb: pointer to skb
 *     @len: new skb length
 *     @flags: reserved
 *     Return: 0 on success or negative error
 *
 * int bpf_skb_pull_data(skb, len)
 *     The helper will pull in non-linear data in case the skb is non-linear
 *     and not all of len are part of the linear section. Only needed for
 *     read/write with direct packet access.
 *     @skb: pointer to skb
 *     @len: len to make read/writeable
 *     Return: 0 on success or negative error
 *
 * lkl_s64 bpf_csum_update(skb, csum)
 *     Adds csum into skb->csum in case of CHECKSUM_COMPLETE.
 *     @skb: pointer to skb
 *     @csum: csum to add
 *     Return: csum on success or negative error
 *
 * void bpf_set_hash_invalid(skb)
 *     Invalidate current skb->hash.
 *     @skb: pointer to skb
 *
 * int bpf_get_numa_node_id()
 *     Return: Id of current NUMA node.
 *
 * int bpf_skb_change_head()
 *     Grows headroom of skb and adjusts MAC header offset accordingly.
 *     Will extends/reallocae as required automatically.
 *     May change skb data pointer and will thus invalidate any check
 *     performed for direct packet access.
 *     @skb: pointer to skb
 *     @len: length of header to be pushed in front
 *     @flags: Flags (unused for now)
 *     Return: 0 on success or negative error
 *
 * int bpf_xdp_adjust_head(xdp_md, delta)
 *     Adjust the xdp_md.data by delta
 *     @xdp_md: pointer to xdp_md
 *     @delta: An positive/negative integer to be added to xdp_md.data
 *     Return: 0 on success or negative on error
 *
 * int bpf_probe_read_str(void *dst, int size, const void *unsafe_ptr)
 *     Copy a NUL terminated string from unsafe address. In case the string
 *     length is smaller than size, the target is not padded with further NUL
 *     bytes. In case the string length is larger than size, just count-1
 *     bytes are copied and the last byte is set to NUL.
 *     @dst: destination address
 *     @size: maximum number of bytes to copy, including the trailing NUL
 *     @unsafe_ptr: unsafe address
 *     Return:
 *       > 0 length of the string including the trailing NUL on success
 *       < 0 error
 *
 * lkl_u64 bpf_get_socket_cookie(skb)
 *     Get the cookie for the socket stored inside sk_buff.
 *     @skb: pointer to skb
 *     Return: 8 Bytes non-decreasing number on success or 0 if the socket
 *     field is missing inside sk_buff
 *
 * lkl_u32 bpf_get_socket_uid(skb)
 *     Get the owner uid of the socket stored inside sk_buff.
 *     @skb: pointer to skb
 *     Return: uid of the socket owner on success or overflowuid if failed.
 *
 * lkl_u32 bpf_set_hash(skb, hash)
 *     Set full skb->hash.
 *     @skb: pointer to skb
 *     @hash: hash to set
 *
 * int bpf_setsockopt(bpf_socket, level, optname, optval, optlen)
 *     Calls setsockopt. Not all opts are available, only those with
 *     integer optvals plus TCP_CONGESTION.
 *     Supported levels: LKL_SOL_SOCKET and LKL_IPPROTO_TCP
 *     @bpf_socket: pointer to bpf_socket
 *     @level: LKL_SOL_SOCKET or LKL_IPPROTO_TCP
 *     @optname: option name
 *     @optval: pointer to option value
 *     @optlen: length of optval in bytes
 *     Return: 0 or negative error
 *
 * int bpf_getsockopt(bpf_socket, level, optname, optval, optlen)
 *     Calls getsockopt. Not all opts are available.
 *     Supported levels: LKL_IPPROTO_TCP
 *     @bpf_socket: pointer to bpf_socket
 *     @level: LKL_IPPROTO_TCP
 *     @optname: option name
 *     @optval: pointer to option value
 *     @optlen: length of optval in bytes
 *     Return: 0 or negative error
 *
 * int bpf_sock_ops_cb_flags_set(bpf_sock_ops, flags)
 *     Set callback flags for sock_ops
 *     @bpf_sock_ops: pointer to bpf_sock_ops_kern struct
 *     @flags: flags value
 *     Return: 0 for no error
 *             -LKL_EINVAL if there is no full tcp socket
 *             bits in flags that are not supported by current kernel
 *
 * int bpf_skb_adjust_room(skb, len_diff, mode, flags)
 *     Grow or shrink room in sk_buff.
 *     @skb: pointer to skb
 *     @len_diff: (signed) amount of room to grow/shrink
 *     @mode: operation mode (enum lkl_bpf_adj_room_mode)
 *     @flags: reserved for future use
 *     Return: 0 on success or negative error code
 *
 * int bpf_sk_redirect_map(map, key, flags)
 *     Redirect skb to a sock in map using key as a lookup key for the
 *     sock in map.
 *     @map: pointer to sockmap
 *     @key: key to lookup sock in map
 *     @flags: reserved for future use
 *     Return: LKL_SK_PASS
 *
 * int bpf_sock_map_update(skops, map, key, flags)
 *	@skops: pointer to bpf_sock_ops
 *	@map: pointer to sockmap to update
 *	@key: key to insert/update sock in map
 *	@flags: same flags as map update elem
 *
 * int bpf_xdp_adjust_meta(xdp_md, delta)
 *     Adjust the xdp_md.data_meta by delta
 *     @xdp_md: pointer to xdp_md
 *     @delta: An positive/negative integer to be added to xdp_md.data_meta
 *     Return: 0 on success or negative on error
 *
 * int bpf_perf_event_read_value(map, flags, buf, buf_size)
 *     read perf event counter value and perf event enabled/running time
 *     @map: pointer to perf_event_array map
 *     @flags: index of event in the map or bitmask flags
 *     @buf: buf to fill
 *     @buf_size: size of the buf
 *     Return: 0 on success or negative error code
 *
 * int bpf_perf_prog_read_value(ctx, buf, buf_size)
 *     read perf prog attached perf event counter and enabled/running time
 *     @ctx: pointer to ctx
 *     @buf: buf to fill
 *     @buf_size: size of the buf
 *     Return : 0 on success or negative error code
 *
 * int bpf_override_return(pt_regs, rc)
 *	@pt_regs: pointer to struct pt_regs
 *	@rc: the return value to set
 *
 * int bpf_msg_redirect_map(map, key, flags)
 *     Redirect msg to a sock in map using key as a lookup key for the
 *     sock in map.
 *     @map: pointer to sockmap
 *     @key: key to lookup sock in map
 *     @flags: reserved for future use
 *     Return: LKL_SK_PASS
 *
 * int bpf_bind(ctx, addr, addr_len)
 *     Bind socket to address. Only binding to IP is supported, no port can be
 *     set in addr.
 *     @ctx: pointer to context of type bpf_sock_addr
 *     @addr: pointer to struct lkl_sockaddr to bind socket to
 *     @addr_len: length of sockaddr structure
 *     Return: 0 on success or negative error code
 */
#define __LKL__BPF_FUNC_MAPPER(FN)		\
	FN(unspec),			\
	FN(map_lookup_elem),		\
	FN(map_update_elem),		\
	FN(map_delete_elem),		\
	FN(probe_read),			\
	FN(ktime_get_ns),		\
	FN(trace_printk),		\
	FN(get_prandom_u32),		\
	FN(get_smp_processor_id),	\
	FN(skb_store_bytes),		\
	FN(l3_csum_replace),		\
	FN(l4_csum_replace),		\
	FN(tail_call),			\
	FN(clone_redirect),		\
	FN(get_current_pid_tgid),	\
	FN(get_current_uid_gid),	\
	FN(get_current_comm),		\
	FN(get_cgroup_classid),		\
	FN(skb_vlan_push),		\
	FN(skb_vlan_pop),		\
	FN(skb_get_tunnel_key),		\
	FN(skb_set_tunnel_key),		\
	FN(perf_event_read),		\
	FN(redirect),			\
	FN(get_route_realm),		\
	FN(perf_event_output),		\
	FN(skb_load_bytes),		\
	FN(get_stackid),		\
	FN(csum_diff),			\
	FN(skb_get_tunnel_opt),		\
	FN(skb_set_tunnel_opt),		\
	FN(skb_change_proto),		\
	FN(skb_change_type),		\
	FN(skb_under_cgroup),		\
	FN(get_hash_recalc),		\
	FN(get_current_task),		\
	FN(probe_write_user),		\
	FN(current_task_under_cgroup),	\
	FN(skb_change_tail),		\
	FN(skb_pull_data),		\
	FN(csum_update),		\
	FN(set_hash_invalid),		\
	FN(get_numa_node_id),		\
	FN(skb_change_head),		\
	FN(xdp_adjust_head),		\
	FN(probe_read_str),		\
	FN(get_socket_cookie),		\
	FN(get_socket_uid),		\
	FN(set_hash),			\
	FN(setsockopt),			\
	FN(skb_adjust_room),		\
	FN(redirect_map),		\
	FN(sk_redirect_map),		\
	FN(sock_map_update),		\
	FN(xdp_adjust_meta),		\
	FN(perf_event_read_value),	\
	FN(perf_prog_read_value),	\
	FN(getsockopt),			\
	FN(override_return),		\
	FN(sock_ops_cb_flags_set),	\
	FN(msg_redirect_map),		\
	FN(msg_apply_bytes),		\
	FN(msg_cork_bytes),		\
	FN(msg_pull_data),		\
	FN(bind),

/* integer value in 'imm' field of LKL_BPF_CALL instruction selects which helper
 * function eBPF program intends to call
 */
#define __LKL__BPF_ENUM_FN(x) BPF_FUNC_ ## x
enum lkl_bpf_func_id {
	__LKL__BPF_FUNC_MAPPER(__LKL__BPF_ENUM_FN)
	__LKL__BPF_FUNC_MAX_ID,
};
#undef __LKL__BPF_ENUM_FN

/* All flags used by eBPF helper functions, placed here. */

/* BPF_FUNC_skb_store_bytes flags. */
#define LKL_BPF_F_RECOMPUTE_CSUM		(1ULL << 0)
#define LKL_BPF_F_INVALIDATE_HASH		(1ULL << 1)

/* BPF_FUNC_l3_csum_replace and BPF_FUNC_l4_csum_replace flags.
 * First 4 bits are for passing the header field size.
 */
#define LKL_BPF_F_HDR_FIELD_MASK		0xfULL

/* BPF_FUNC_l4_csum_replace flags. */
#define LKL_BPF_F_PSEUDO_HDR		(1ULL << 4)
#define LKL_BPF_F_MARK_MANGLED_0		(1ULL << 5)
#define LKL_BPF_F_MARK_ENFORCE		(1ULL << 6)

/* BPF_FUNC_clone_redirect and BPF_FUNC_redirect flags. */
#define LKL_BPF_F_INGRESS			(1ULL << 0)

/* BPF_FUNC_skb_set_tunnel_key and BPF_FUNC_skb_get_tunnel_key flags. */
#define LKL_BPF_F_TUNINFO_IPV6		(1ULL << 0)

/* BPF_FUNC_get_stackid flags. */
#define LKL_BPF_F_SKIP_FIELD_MASK		0xffULL
#define LKL_BPF_F_USER_STACK		(1ULL << 8)
#define LKL_BPF_F_FAST_STACK_CMP		(1ULL << 9)
#define LKL_BPF_F_REUSE_STACKID		(1ULL << 10)

/* BPF_FUNC_skb_set_tunnel_key flags. */
#define LKL_BPF_F_ZERO_CSUM_TX		(1ULL << 1)
#define LKL_BPF_F_DONT_FRAGMENT		(1ULL << 2)
#define LKL_BPF_F_SEQ_NUMBER		(1ULL << 3)

/* BPF_FUNC_perf_event_output, BPF_FUNC_perf_event_read and
 * BPF_FUNC_perf_event_read_value flags.
 */
#define LKL_BPF_F_INDEX_MASK		0xffffffffULL
#define LKL_BPF_F_CURRENT_CPU		LKL_BPF_F_INDEX_MASK
/* BPF_FUNC_perf_event_output for sk_buff input context. */
#define LKL_BPF_F_CTXLEN_MASK		(0xfffffULL << 32)

/* Mode for BPF_FUNC_skb_adjust_room helper. */
enum lkl_bpf_adj_room_mode {
	LKL_BPF_ADJ_ROOM_NET,
};

/* user accessible mirror of in-kernel sk_buff.
 * new fields can only be added to the end of this structure
 */
struct __lkl__sk_buff {
	__lkl__u32 len;
	__lkl__u32 pkt_type;
	__lkl__u32 mark;
	__lkl__u32 queue_mapping;
	__lkl__u32 protocol;
	__lkl__u32 vlan_present;
	__lkl__u32 vlan_tci;
	__lkl__u32 vlan_proto;
	__lkl__u32 priority;
	__lkl__u32 ingress_ifindex;
	__lkl__u32 ifindex;
	__lkl__u32 tc_index;
	__lkl__u32 cb[5];
	__lkl__u32 hash;
	__lkl__u32 tc_classid;
	__lkl__u32 data;
	__lkl__u32 data_end;
	__lkl__u32 napi_id;

	/* Accessed by BPF_PROG_TYPE_sk_skb types from here to ... */
	__lkl__u32 family;
	__lkl__u32 remote_ip4;	/* Stored in network byte order */
	__lkl__u32 local_ip4;	/* Stored in network byte order */
	__lkl__u32 remote_ip6[4];	/* Stored in network byte order */
	__lkl__u32 local_ip6[4];	/* Stored in network byte order */
	__lkl__u32 remote_port;	/* Stored in network byte order */
	__lkl__u32 local_port;	/* stored in host byte order */
	/* ... here. */

	__lkl__u32 data_meta;
};

struct lkl_bpf_tunnel_key {
	__lkl__u32 tunnel_id;
	union {
		__lkl__u32 remote_ipv4;
		__lkl__u32 remote_ipv6[4];
	};
	__lkl__u8 tunnel_tos;
	__lkl__u8 tunnel_ttl;
	__lkl__u16 tunnel_ext;
	__lkl__u32 tunnel_label;
};

/* Generic BPF return codes which all BPF program types may support.
 * The values are binary compatible with their TC_ACT_* counter-part to
 * provide backwards compatibility with existing SCHED_CLS and SCHED_ACT
 * programs.
 *
 * XDP is handled seprately, see XDP_*.
 */
enum lkl_bpf_ret_code {
	LKL_BPF_OK = 0,
	/* 1 reserved */
	LKL_BPF_DROP = 2,
	/* 3-6 reserved */
	LKL_BPF_REDIRECT = 7,
	/* >127 are reserved for prog type specific return codes */
};

struct lkl_bpf_sock {
	__lkl__u32 bound_dev_if;
	__lkl__u32 family;
	__lkl__u32 type;
	__lkl__u32 protocol;
	__lkl__u32 mark;
	__lkl__u32 priority;
	__lkl__u32 src_ip4;		/* Allows 1,2,4-byte read.
				 * Stored in network byte order.
				 */
	__lkl__u32 src_ip6[4];	/* Allows 1,2,4-byte read.
				 * Stored in network byte order.
				 */
	__lkl__u32 src_port;		/* Allows 4-byte read.
				 * Stored in host byte order
				 */
};

#define LKL_XDP_PACKET_HEADROOM 256

/* User return codes for XDP prog type.
 * A valid XDP program must return one of these defined values. All other
 * return codes are reserved for future use. Unknown return codes will
 * result in packet drops and a warning via bpf_warn_invalid_xdp_action().
 */
enum lkl_xdp_action {
	LKL_XDP_ABORTED = 0,
	LKL_XDP_DROP,
	LKL_XDP_PASS,
	LKL_XDP_TX,
	LKL_XDP_REDIRECT,
};

/* user accessible metadata for XDP packet hook
 * new fields must be added to the end of this structure
 */
struct lkl_xdp_md {
	__lkl__u32 data;
	__lkl__u32 data_end;
	__lkl__u32 data_meta;
	/* Below access go through struct xdp_rxq_info */
	__lkl__u32 ingress_ifindex; /* rxq->dev->ifindex */
	__lkl__u32 rx_queue_index;  /* rxq->queue_index  */
};

enum lkl_sk_action {
	LKL_SK_DROP = 0,
	LKL_SK_PASS,
};

/* user accessible metadata for SK_MSG packet hook, new fields must
 * be added to the end of this structure
 */
struct lkl_sk_msg_md {
	void *data;
	void *data_end;
};

#define LKL_BPF_TAG_SIZE	8

struct lkl_bpf_prog_info {
	__lkl__u32 type;
	__lkl__u32 id;
	__lkl__u8  tag[LKL_BPF_TAG_SIZE];
	__lkl__u32 jited_prog_len;
	__lkl__u32 xlated_prog_len;
	__lkl__aligned_u64 jited_prog_insns;
	__lkl__aligned_u64 xlated_prog_insns;
	__lkl__u64 load_time;	/* ns since boottime */
	__lkl__u32 created_by_uid;
	__lkl__u32 nr_map_ids;
	__lkl__aligned_u64 map_ids;
	char name[LKL_BPF_OBJ_NAME_LEN];
	__lkl__u32 ifindex;
	__lkl__u32 :32;
	__lkl__u64 netns_dev;
	__lkl__u64 netns_ino;
} __attribute__((aligned(8)));

struct lkl_bpf_map_info {
	__lkl__u32 type;
	__lkl__u32 id;
	__lkl__u32 key_size;
	__lkl__u32 value_size;
	__lkl__u32 max_entries;
	__lkl__u32 map_flags;
	char  name[LKL_BPF_OBJ_NAME_LEN];
	__lkl__u32 ifindex;
	__lkl__u32 :32;
	__lkl__u64 netns_dev;
	__lkl__u64 netns_ino;
} __attribute__((aligned(8)));

/* User bpf_sock_addr struct to access socket fields and sockaddr struct passed
 * by user and intended to be used by socket (e.g. to bind to, depends on
 * attach attach type).
 */
struct lkl_bpf_sock_addr {
	__lkl__u32 user_family;	/* Allows 4-byte read, but no write. */
	__lkl__u32 user_ip4;		/* Allows 1,2,4-byte read and 4-byte write.
				 * Stored in network byte order.
				 */
	__lkl__u32 user_ip6[4];	/* Allows 1,2,4-byte read an 4-byte write.
				 * Stored in network byte order.
				 */
	__lkl__u32 user_port;	/* Allows 4-byte read and write.
				 * Stored in network byte order
				 */
	__lkl__u32 family;		/* Allows 4-byte read, but no write */
	__lkl__u32 type;		/* Allows 4-byte read, but no write */
	__lkl__u32 protocol;		/* Allows 4-byte read, but no write */
};

/* User bpf_sock_ops struct to access socket values and specify request ops
 * and their replies.
 * Some of this fields are in network (bigendian) byte order and may need
 * to be converted before use (bpf_ntohl() defined in samples/bpf/bpf_endian.h).
 * New fields can only be added at the end of this structure
 */
struct lkl_bpf_sock_ops {
	__lkl__u32 op;
	union {
		__lkl__u32 args[4];		/* Optionally passed to bpf program */
		__lkl__u32 reply;		/* Returned by bpf program	    */
		__lkl__u32 replylong[4];	/* Optionally returned by bpf prog  */
	};
	__lkl__u32 family;
	__lkl__u32 remote_ip4;	/* Stored in network byte order */
	__lkl__u32 local_ip4;	/* Stored in network byte order */
	__lkl__u32 remote_ip6[4];	/* Stored in network byte order */
	__lkl__u32 local_ip6[4];	/* Stored in network byte order */
	__lkl__u32 remote_port;	/* Stored in network byte order */
	__lkl__u32 local_port;	/* stored in host byte order */
	__lkl__u32 is_fullsock;	/* Some TCP fields are only valid if
				 * there is a full socket. If not, the
				 * fields read as zero.
				 */
	__lkl__u32 snd_cwnd;
	__lkl__u32 srtt_us;		/* Averaged RTT << 3 in usecs */
	__lkl__u32 bpf_sock_ops_cb_flags; /* flags defined in uapi/linux/tcp.h */
	__lkl__u32 state;
	__lkl__u32 rtt_min;
	__lkl__u32 snd_ssthresh;
	__lkl__u32 rcv_nxt;
	__lkl__u32 snd_nxt;
	__lkl__u32 snd_una;
	__lkl__u32 mss_cache;
	__lkl__u32 ecn_flags;
	__lkl__u32 rate_delivered;
	__lkl__u32 rate_interval_us;
	__lkl__u32 packets_out;
	__lkl__u32 retrans_out;
	__lkl__u32 total_retrans;
	__lkl__u32 segs_in;
	__lkl__u32 data_segs_in;
	__lkl__u32 segs_out;
	__lkl__u32 data_segs_out;
	__lkl__u32 lost_out;
	__lkl__u32 sacked_out;
	__lkl__u32 sk_txhash;
	__lkl__u64 bytes_received;
	__lkl__u64 bytes_acked;
};

/* Definitions for bpf_sock_ops_cb_flags */
#define LKL_BPF_SOCK_OPS_RTO_CB_FLAG	(1<<0)
#define LKL_BPF_SOCK_OPS_RETRANS_CB_FLAG	(1<<1)
#define LKL_BPF_SOCK_OPS_STATE_CB_FLAG	(1<<2)
#define LKL_BPF_SOCK_OPS_ALL_CB_FLAGS       0x7		/* Mask of all currently
							 * supported cb flags
							 */

/* List of known BPF sock_ops operators.
 * New entries can only be added at the end
 */
enum {
	LKL_BPF_SOCK_OPS_VOID,
	LKL_BPF_SOCK_OPS_TIMEOUT_INIT,	/* Should return SYN-RTO value to use or
					 * -1 if default value should be used
					 */
	LKL_BPF_SOCK_OPS_RWND_INIT,		/* Should return initial advertized
					 * window (in packets) or -1 if default
					 * value should be used
					 */
	LKL_BPF_SOCK_OPS_TCP_CONNECT_CB,	/* Calls BPF program right before an
					 * active connection is initialized
					 */
	LKL_BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB,	/* Calls BPF program when an
						 * active connection is
						 * established
						 */
	LKL_BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB,	/* Calls BPF program when a
						 * passive connection is
						 * established
						 */
	LKL_BPF_SOCK_OPS_NEEDS_ECN,		/* If connection's congestion control
					 * needs ECN
					 */
	LKL_BPF_SOCK_OPS_BASE_RTT,		/* Get base RTT. The correct value is
					 * based on the path and may be
					 * dependent on the congestion control
					 * algorithm. In general it indicates
					 * a congestion threshold. RTTs above
					 * this indicate congestion
					 */
	LKL_BPF_SOCK_OPS_RTO_CB,		/* Called when an RTO has triggered.
					 * Arg1: value of icsk_retransmits
					 * Arg2: value of icsk_rto
					 * Arg3: whether RTO has expired
					 */
	LKL_BPF_SOCK_OPS_RETRANS_CB,	/* Called when skb is retransmitted.
					 * Arg1: sequence number of 1st byte
					 * Arg2: # segments
					 * Arg3: return value of
					 *       tcp_transmit_skb (0 => success)
					 */
	LKL_BPF_SOCK_OPS_STATE_CB,		/* Called when TCP changes state.
					 * Arg1: old_state
					 * Arg2: new_state
					 */
};

/* List of TCP states. There is a build check in net/ipv4/tcp.c to detect
 * changes between the TCP and BPF versions. Ideally this should never happen.
 * If it does, we need to add code to convert them before calling
 * the BPF sock_ops function.
 */
enum {
	LKL_BPF_TCP_ESTABLISHED = 1,
	LKL_BPF_TCP_SYN_SENT,
	LKL_BPF_TCP_SYN_RECV,
	LKL_BPF_TCP_FIN_WAIT1,
	LKL_BPF_TCP_FIN_WAIT2,
	LKL_BPF_TCP_TIME_WAIT,
	LKL_BPF_TCP_CLOSE,
	LKL_BPF_TCP_CLOSE_WAIT,
	LKL_BPF_TCP_LAST_ACK,
	LKL_BPF_TCP_LISTEN,
	LKL_BPF_TCP_CLOSING,	/* Now a valid state */
	LKL_BPF_TCP_NEW_SYN_RECV,

	LKL_BPF_TCP_MAX_STATES	/* Leave at the end! */
};

#define LKL_TCP_BPF_IW		1001	/* Set TCP initial congestion window */
#define LKL_TCP_BPF_SNDCWND_CLAMP	1002	/* Set sndcwnd_clamp */

struct lkl_bpf_perf_event_value {
	__lkl__u64 counter;
	__lkl__u64 enabled;
	__lkl__u64 running;
};

#define LKL_BPF_DEVCG_ACC_MKNOD	(1ULL << 0)
#define LKL_BPF_DEVCG_ACC_READ	(1ULL << 1)
#define LKL_BPF_DEVCG_ACC_WRITE	(1ULL << 2)

#define LKL_BPF_DEVCG_DEV_BLOCK	(1ULL << 0)
#define LKL_BPF_DEVCG_DEV_CHAR	(1ULL << 1)

struct lkl_bpf_cgroup_dev_ctx {
	/* access_type encoded as (BPF_DEVCG_ACC_* << 16) | BPF_DEVCG_DEV_* */
	__lkl__u32 access_type;
	__lkl__u32 major;
	__lkl__u32 minor;
};

struct lkl_bpf_raw_tracepoint_args {
	__lkl__u64 args[0];
};

#endif /* __LKL__LINUX_BPF_H__ */
