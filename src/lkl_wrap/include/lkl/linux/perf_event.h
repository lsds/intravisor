/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Performance events:
 *
 *    Copyright (C) 2008-2009, Thomas Gleixner <tglx@linutronix.de>
 *    Copyright (C) 2008-2011, Red Hat, Inc., Ingo Molnar
 *    Copyright (C) 2008-2011, Red Hat, Inc., Peter Zijlstra
 *
 * Data type definitions, declarations, prototypes.
 *
 *    Started by: Thomas Gleixner and Ingo Molnar
 *
 * For licencing details see kernel-base/COPYING
 */
#ifndef _LKL_LINUX_PERF_EVENT_H
#define _LKL_LINUX_PERF_EVENT_H

#include <lkl/linux/types.h>
#include <lkl/linux/ioctl.h>
#include <lkl/asm/byteorder.h>

/*
 * User-space ABI bits:
 */

/*
 * attr.type
 */
enum lkl_perf_type_id {
	LKL_PERF_TYPE_HARDWARE			= 0,
	LKL_PERF_TYPE_SOFTWARE			= 1,
	LKL_PERF_TYPE_TRACEPOINT			= 2,
	LKL_PERF_TYPE_HW_CACHE			= 3,
	LKL_PERF_TYPE_RAW				= 4,
	LKL_PERF_TYPE_BREAKPOINT			= 5,

	LKL_PERF_TYPE_MAX,				/* non-ABI */
};

/*
 * attr.config layout for type LKL_PERF_TYPE_HARDWARE and LKL_PERF_TYPE_HW_CACHE
 * LKL_PERF_TYPE_HARDWARE:			0xEEEEEEEE000000AA
 *					AA: hardware event ID
 *					EEEEEEEE: PMU type ID
 * LKL_PERF_TYPE_HW_CACHE:			0xEEEEEEEE00DDCCBB
 *					BB: hardware cache ID
 *					CC: hardware cache op ID
 *					DD: hardware cache op result ID
 *					EEEEEEEE: PMU type ID
 * If the PMU type ID is 0, the LKL_PERF_TYPE_RAW will be applied.
 */
#define LKL_PERF_PMU_TYPE_SHIFT		32
#define LKL_PERF_HW_EVENT_MASK		0xffffffff

/*
 * Generalized performance event event_id types, used by the
 * attr.event_id parameter of the sys_perf_event_open()
 * syscall:
 */
enum lkl_perf_hw_id {
	/*
	 * Common hardware events, generalized by the kernel:
	 */
	LKL_PERF_COUNT_HW_CPU_CYCLES		= 0,
	LKL_PERF_COUNT_HW_INSTRUCTIONS		= 1,
	LKL_PERF_COUNT_HW_CACHE_REFERENCES		= 2,
	LKL_PERF_COUNT_HW_CACHE_MISSES		= 3,
	LKL_PERF_COUNT_HW_BRANCH_INSTRUCTIONS	= 4,
	LKL_PERF_COUNT_HW_BRANCH_MISSES		= 5,
	LKL_PERF_COUNT_HW_BUS_CYCLES		= 6,
	LKL_PERF_COUNT_HW_STALLED_CYCLES_FRONTEND	= 7,
	LKL_PERF_COUNT_HW_STALLED_CYCLES_BACKEND	= 8,
	LKL_PERF_COUNT_HW_REF_CPU_CYCLES		= 9,

	LKL_PERF_COUNT_HW_MAX,			/* non-ABI */
};

/*
 * Generalized hardware cache events:
 *
 *       { L1-D, L1-I, LLC, ITLB, DTLB, BPU, NODE } x
 *       { read, write, prefetch } x
 *       { accesses, misses }
 */
enum lkl_perf_hw_cache_id {
	LKL_PERF_COUNT_HW_CACHE_L1D			= 0,
	LKL_PERF_COUNT_HW_CACHE_L1I			= 1,
	LKL_PERF_COUNT_HW_CACHE_LL			= 2,
	LKL_PERF_COUNT_HW_CACHE_DTLB		= 3,
	LKL_PERF_COUNT_HW_CACHE_ITLB		= 4,
	LKL_PERF_COUNT_HW_CACHE_BPU			= 5,
	LKL_PERF_COUNT_HW_CACHE_NODE		= 6,

	LKL_PERF_COUNT_HW_CACHE_MAX,		/* non-ABI */
};

enum lkl_perf_hw_cache_op_id {
	LKL_PERF_COUNT_HW_CACHE_OP_READ		= 0,
	LKL_PERF_COUNT_HW_CACHE_OP_WRITE		= 1,
	LKL_PERF_COUNT_HW_CACHE_OP_PREFETCH		= 2,

	LKL_PERF_COUNT_HW_CACHE_OP_MAX,		/* non-ABI */
};

enum lkl_perf_hw_cache_op_result_id {
	LKL_PERF_COUNT_HW_CACHE_RESULT_ACCESS	= 0,
	LKL_PERF_COUNT_HW_CACHE_RESULT_MISS		= 1,

	LKL_PERF_COUNT_HW_CACHE_RESULT_MAX,		/* non-ABI */
};

/*
 * Special "software" events provided by the kernel, even if the hardware
 * does not support performance events. These events measure various
 * physical and sw events of the kernel (and allow the profiling of them as
 * well):
 */
enum lkl_perf_sw_ids {
	LKL_PERF_COUNT_SW_CPU_CLOCK			= 0,
	LKL_PERF_COUNT_SW_TASK_CLOCK		= 1,
	LKL_PERF_COUNT_SW_PAGE_FAULTS		= 2,
	LKL_PERF_COUNT_SW_CONTEXT_SWITCHES		= 3,
	LKL_PERF_COUNT_SW_CPU_MIGRATIONS		= 4,
	LKL_PERF_COUNT_SW_PAGE_FAULTS_MIN		= 5,
	LKL_PERF_COUNT_SW_PAGE_FAULTS_MAJ		= 6,
	LKL_PERF_COUNT_SW_ALIGNMENT_FAULTS		= 7,
	LKL_PERF_COUNT_SW_EMULATION_FAULTS		= 8,
	LKL_PERF_COUNT_SW_DUMMY			= 9,
	LKL_PERF_COUNT_SW_BPF_OUTPUT		= 10,
	LKL_PERF_COUNT_SW_CGROUP_SWITCHES		= 11,

	LKL_PERF_COUNT_SW_MAX,			/* non-ABI */
};

/*
 * Bits that can be set in attr.sample_type to request information
 * in the overflow packets.
 */
enum lkl_perf_event_sample_format {
	LKL_PERF_SAMPLE_IP				= 1U << 0,
	LKL_PERF_SAMPLE_TID				= 1U << 1,
	LKL_PERF_SAMPLE_TIME			= 1U << 2,
	LKL_PERF_SAMPLE_ADDR			= 1U << 3,
	LKL_PERF_SAMPLE_READ			= 1U << 4,
	LKL_PERF_SAMPLE_CALLCHAIN			= 1U << 5,
	LKL_PERF_SAMPLE_ID				= 1U << 6,
	LKL_PERF_SAMPLE_CPU				= 1U << 7,
	LKL_PERF_SAMPLE_PERIOD			= 1U << 8,
	LKL_PERF_SAMPLE_STREAM_ID			= 1U << 9,
	LKL_PERF_SAMPLE_RAW				= 1U << 10,
	LKL_PERF_SAMPLE_BRANCH_STACK		= 1U << 11,
	LKL_PERF_SAMPLE_REGS_USER			= 1U << 12,
	LKL_PERF_SAMPLE_STACK_USER			= 1U << 13,
	LKL_PERF_SAMPLE_WEIGHT			= 1U << 14,
	LKL_PERF_SAMPLE_DATA_SRC			= 1U << 15,
	LKL_PERF_SAMPLE_IDENTIFIER			= 1U << 16,
	LKL_PERF_SAMPLE_TRANSACTION			= 1U << 17,
	LKL_PERF_SAMPLE_REGS_INTR			= 1U << 18,
	LKL_PERF_SAMPLE_PHYS_ADDR			= 1U << 19,
	LKL_PERF_SAMPLE_AUX				= 1U << 20,
	LKL_PERF_SAMPLE_CGROUP			= 1U << 21,
	LKL_PERF_SAMPLE_DATA_PAGE_SIZE		= 1U << 22,
	LKL_PERF_SAMPLE_CODE_PAGE_SIZE		= 1U << 23,
	LKL_PERF_SAMPLE_WEIGHT_STRUCT		= 1U << 24,

	LKL_PERF_SAMPLE_MAX = 1U << 25,		/* non-ABI */
};

#define LKL_PERF_SAMPLE_WEIGHT_TYPE	(LKL_PERF_SAMPLE_WEIGHT | LKL_PERF_SAMPLE_WEIGHT_STRUCT)
/*
 * values to program into branch_sample_type when PERF_SAMPLE_BRANCH is set
 *
 * If the user does not pass priv level information via branch_sample_type,
 * the kernel uses the event's priv level. Branch and event priv levels do
 * not have to match. Branch priv level is checked for permissions.
 *
 * The branch types can be combined, however BRANCH_ANY covers all types
 * of branches and therefore it supersedes all the other types.
 */
enum lkl_perf_branch_sample_type_shift {
	LKL_PERF_SAMPLE_BRANCH_USER_SHIFT		= 0, /* user branches */
	LKL_PERF_SAMPLE_BRANCH_KERNEL_SHIFT		= 1, /* kernel branches */
	LKL_PERF_SAMPLE_BRANCH_HV_SHIFT		= 2, /* hypervisor branches */

	LKL_PERF_SAMPLE_BRANCH_ANY_SHIFT		= 3, /* any branch types */
	LKL_PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT	= 4, /* any call branch */
	LKL_PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT	= 5, /* any return branch */
	LKL_PERF_SAMPLE_BRANCH_IND_CALL_SHIFT	= 6, /* indirect calls */
	LKL_PERF_SAMPLE_BRANCH_ABORT_TX_SHIFT	= 7, /* transaction aborts */
	LKL_PERF_SAMPLE_BRANCH_IN_TX_SHIFT		= 8, /* in transaction */
	LKL_PERF_SAMPLE_BRANCH_NO_TX_SHIFT		= 9, /* not in transaction */
	LKL_PERF_SAMPLE_BRANCH_COND_SHIFT		= 10, /* conditional branches */

	LKL_PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT	= 11, /* call/ret stack */
	LKL_PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT	= 12, /* indirect jumps */
	LKL_PERF_SAMPLE_BRANCH_CALL_SHIFT		= 13, /* direct call */

	LKL_PERF_SAMPLE_BRANCH_NO_FLAGS_SHIFT	= 14, /* no flags */
	LKL_PERF_SAMPLE_BRANCH_NO_CYCLES_SHIFT	= 15, /* no cycles */

	LKL_PERF_SAMPLE_BRANCH_TYPE_SAVE_SHIFT	= 16, /* save branch type */

	LKL_PERF_SAMPLE_BRANCH_HW_INDEX_SHIFT	= 17, /* save low level index of raw branch records */

	LKL_PERF_SAMPLE_BRANCH_PRIV_SAVE_SHIFT	= 18, /* save privilege mode */

	LKL_PERF_SAMPLE_BRANCH_MAX_SHIFT		/* non-ABI */
};

enum lkl_perf_branch_sample_type {
	LKL_PERF_SAMPLE_BRANCH_USER		= 1U << LKL_PERF_SAMPLE_BRANCH_USER_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_KERNEL	= 1U << LKL_PERF_SAMPLE_BRANCH_KERNEL_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_HV		= 1U << LKL_PERF_SAMPLE_BRANCH_HV_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_ANY		= 1U << LKL_PERF_SAMPLE_BRANCH_ANY_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_ANY_CALL	= 1U << LKL_PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_ANY_RETURN	= 1U << LKL_PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_IND_CALL	= 1U << LKL_PERF_SAMPLE_BRANCH_IND_CALL_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_ABORT_TX	= 1U << LKL_PERF_SAMPLE_BRANCH_ABORT_TX_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_IN_TX	= 1U << LKL_PERF_SAMPLE_BRANCH_IN_TX_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_NO_TX	= 1U << LKL_PERF_SAMPLE_BRANCH_NO_TX_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_COND		= 1U << LKL_PERF_SAMPLE_BRANCH_COND_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_CALL_STACK	= 1U << LKL_PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_IND_JUMP	= 1U << LKL_PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_CALL		= 1U << LKL_PERF_SAMPLE_BRANCH_CALL_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_NO_FLAGS	= 1U << LKL_PERF_SAMPLE_BRANCH_NO_FLAGS_SHIFT,
	LKL_PERF_SAMPLE_BRANCH_NO_CYCLES	= 1U << LKL_PERF_SAMPLE_BRANCH_NO_CYCLES_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_TYPE_SAVE	=
		1U << LKL_PERF_SAMPLE_BRANCH_TYPE_SAVE_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_HW_INDEX	= 1U << LKL_PERF_SAMPLE_BRANCH_HW_INDEX_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_PRIV_SAVE	= 1U << LKL_PERF_SAMPLE_BRANCH_PRIV_SAVE_SHIFT,

	LKL_PERF_SAMPLE_BRANCH_MAX		= 1U << LKL_PERF_SAMPLE_BRANCH_MAX_SHIFT,
};

/*
 * Common flow change classification
 */
enum {
	LKL_PERF_BR_UNKNOWN		= 0,	/* unknown */
	LKL_PERF_BR_COND		= 1,	/* conditional */
	LKL_PERF_BR_UNCOND		= 2,	/* unconditional  */
	LKL_PERF_BR_IND		= 3,	/* indirect */
	LKL_PERF_BR_CALL		= 4,	/* function call */
	LKL_PERF_BR_IND_CALL	= 5,	/* indirect function call */
	LKL_PERF_BR_RET		= 6,	/* function return */
	LKL_PERF_BR_SYSCALL		= 7,	/* syscall */
	LKL_PERF_BR_SYSRET		= 8,	/* syscall return */
	LKL_PERF_BR_COND_CALL	= 9,	/* conditional function call */
	LKL_PERF_BR_COND_RET	= 10,	/* conditional function return */
	LKL_PERF_BR_ERET		= 11,	/* exception return */
	LKL_PERF_BR_IRQ		= 12,	/* irq */
	LKL_PERF_BR_SERROR		= 13,	/* system error */
	LKL_PERF_BR_NO_TX		= 14,	/* not in transaction */
	LKL_PERF_BR_EXTEND_ABI	= 15,	/* extend ABI */
	LKL_PERF_BR_MAX,
};

/*
 * Common branch speculation outcome classification
 */
enum {
	LKL_PERF_BR_SPEC_NA			= 0,	/* Not available */
	LKL_PERF_BR_SPEC_WRONG_PATH		= 1,	/* Speculative but on wrong path */
	LKL_PERF_BR_NON_SPEC_CORRECT_PATH	= 2,	/* Non-speculative but on correct path */
	LKL_PERF_BR_SPEC_CORRECT_PATH	= 3,	/* Speculative and on correct path */
	LKL_PERF_BR_SPEC_MAX,
};

enum {
	LKL_PERF_BR_NEW_FAULT_ALGN		= 0,    /* Alignment fault */
	LKL_PERF_BR_NEW_FAULT_DATA		= 1,    /* Data fault */
	LKL_PERF_BR_NEW_FAULT_INST		= 2,    /* Inst fault */
	LKL_PERF_BR_NEW_ARCH_1		= 3,    /* Architecture specific */
	LKL_PERF_BR_NEW_ARCH_2		= 4,    /* Architecture specific */
	LKL_PERF_BR_NEW_ARCH_3		= 5,    /* Architecture specific */
	LKL_PERF_BR_NEW_ARCH_4		= 6,    /* Architecture specific */
	LKL_PERF_BR_NEW_ARCH_5		= 7,    /* Architecture specific */
	LKL_PERF_BR_NEW_MAX,
};

enum {
	LKL_PERF_BR_PRIV_UNKNOWN	= 0,
	LKL_PERF_BR_PRIV_USER	= 1,
	LKL_PERF_BR_PRIV_KERNEL	= 2,
	LKL_PERF_BR_PRIV_HV		= 3,
};

#define LKL_PERF_BR_ARM64_FIQ		LKL_PERF_BR_NEW_ARCH_1
#define LKL_PERF_BR_ARM64_DEBUG_HALT	LKL_PERF_BR_NEW_ARCH_2
#define LKL_PERF_BR_ARM64_DEBUG_EXIT	LKL_PERF_BR_NEW_ARCH_3
#define LKL_PERF_BR_ARM64_DEBUG_INST	LKL_PERF_BR_NEW_ARCH_4
#define LKL_PERF_BR_ARM64_DEBUG_DATA	LKL_PERF_BR_NEW_ARCH_5

#define LKL_PERF_SAMPLE_BRANCH_PLM_ALL \
	(LKL_PERF_SAMPLE_BRANCH_USER|\
	 LKL_PERF_SAMPLE_BRANCH_KERNEL|\
	 LKL_PERF_SAMPLE_BRANCH_HV)

/*
 * Values to determine ABI of the registers dump.
 */
enum lkl_perf_sample_regs_abi {
	LKL_PERF_SAMPLE_REGS_ABI_NONE	= 0,
	LKL_PERF_SAMPLE_REGS_ABI_32		= 1,
	LKL_PERF_SAMPLE_REGS_ABI_64		= 2,
};

/*
 * Values for the memory transaction event qualifier, mostly for
 * abort events. Multiple bits can be set.
 */
enum {
	LKL_PERF_TXN_ELISION        = (1 << 0), /* From elision */
	LKL_PERF_TXN_TRANSACTION    = (1 << 1), /* From transaction */
	LKL_PERF_TXN_SYNC           = (1 << 2), /* Instruction is related */
	LKL_PERF_TXN_ASYNC          = (1 << 3), /* Instruction not related */
	LKL_PERF_TXN_RETRY          = (1 << 4), /* Retry possible */
	LKL_PERF_TXN_CONFLICT       = (1 << 5), /* Conflict abort */
	LKL_PERF_TXN_CAPACITY_WRITE = (1 << 6), /* Capacity write abort */
	LKL_PERF_TXN_CAPACITY_READ  = (1 << 7), /* Capacity read abort */

	LKL_PERF_TXN_MAX	        = (1 << 8), /* non-ABI */

	/* bits 32..63 are reserved for the abort code */

	LKL_PERF_TXN_ABORT_MASK  = (0xffffffffULL << 32),
	LKL_PERF_TXN_ABORT_SHIFT = 32,
};

/*
 * The format of the data returned by read() on a perf event fd,
 * as specified by attr.read_format:
 *
 * struct lkl_read_format {
 *	{ lkl_u64		value;
 *	  { lkl_u64		time_enabled; } && LKL_PERF_FORMAT_TOTAL_TIME_ENABLED
 *	  { lkl_u64		time_running; } && LKL_PERF_FORMAT_TOTAL_TIME_RUNNING
 *	  { lkl_u64		id;           } && LKL_PERF_FORMAT_ID
 *	  { lkl_u64		lost;         } && LKL_PERF_FORMAT_LOST
 *	} && !LKL_PERF_FORMAT_GROUP
 *
 *	{ lkl_u64		nr;
 *	  { lkl_u64		time_enabled; } && LKL_PERF_FORMAT_TOTAL_TIME_ENABLED
 *	  { lkl_u64		time_running; } && LKL_PERF_FORMAT_TOTAL_TIME_RUNNING
 *	  { lkl_u64		value;
 *	    { lkl_u64	id;           } && LKL_PERF_FORMAT_ID
 *	    { lkl_u64	lost;         } && LKL_PERF_FORMAT_LOST
 *	  }		cntr[nr];
 *	} && LKL_PERF_FORMAT_GROUP
 * };
 */
enum lkl_perf_event_read_format {
	LKL_PERF_FORMAT_TOTAL_TIME_ENABLED		= 1U << 0,
	LKL_PERF_FORMAT_TOTAL_TIME_RUNNING		= 1U << 1,
	LKL_PERF_FORMAT_ID				= 1U << 2,
	LKL_PERF_FORMAT_GROUP			= 1U << 3,
	LKL_PERF_FORMAT_LOST			= 1U << 4,

	LKL_PERF_FORMAT_MAX = 1U << 5,		/* non-ABI */
};

#define LKL_PERF_ATTR_SIZE_VER0	64	/* sizeof first published struct */
#define LKL_PERF_ATTR_SIZE_VER1	72	/* add: config2 */
#define LKL_PERF_ATTR_SIZE_VER2	80	/* add: branch_sample_type */
#define LKL_PERF_ATTR_SIZE_VER3	96	/* add: sample_regs_user */
					/* add: sample_stack_user */
#define LKL_PERF_ATTR_SIZE_VER4	104	/* add: sample_regs_intr */
#define LKL_PERF_ATTR_SIZE_VER5	112	/* add: aux_watermark */
#define LKL_PERF_ATTR_SIZE_VER6	120	/* add: aux_sample_size */
#define LKL_PERF_ATTR_SIZE_VER7	128	/* add: sig_data */

/*
 * Hardware event_id to monitor via a performance monitoring event:
 *
 * @sample_max_stack: Max number of frame pointers in a callchain,
 *		      should be < /proc/sys/kernel/perf_event_max_stack
 */
struct lkl_perf_event_attr {

	/*
	 * Major type: hardware/software/tracepoint/etc.
	 */
	__lkl__u32			type;

	/*
	 * Size of the attr structure, for fwd/bwd compat.
	 */
	__lkl__u32			size;

	/*
	 * Type specific configuration information.
	 */
	__lkl__u64			config;

	union {
		__lkl__u64		sample_period;
		__lkl__u64		sample_freq;
	};

	__lkl__u64			sample_type;
	__lkl__u64			read_format;

	__lkl__u64			disabled       :  1, /* off by default        */
				inherit	       :  1, /* children inherit it   */
				pinned	       :  1, /* must always be on PMU */
				exclusive      :  1, /* only group on PMU     */
				exclude_user   :  1, /* don't count user      */
				exclude_kernel :  1, /* ditto kernel          */
				exclude_hv     :  1, /* ditto hypervisor      */
				exclude_idle   :  1, /* don't count when idle */
				mmap           :  1, /* include mmap data     */
				comm	       :  1, /* include comm data     */
				freq           :  1, /* use freq, not period  */
				inherit_stat   :  1, /* per task counts       */
				enable_on_exec :  1, /* next exec enables     */
				task           :  1, /* trace fork/exit       */
				watermark      :  1, /* wakeup_watermark      */
				/*
				 * precise_ip:
				 *
				 *  0 - SAMPLE_IP can have arbitrary skid
				 *  1 - SAMPLE_IP must have constant skid
				 *  2 - SAMPLE_IP requested to have 0 skid
				 *  3 - SAMPLE_IP must have 0 skid
				 *
				 *  See also LKL_PERF_RECORD_MISC_EXACT_IP
				 */
				precise_ip     :  2, /* skid constraint       */
				mmap_data      :  1, /* non-exec mmap data    */
				sample_id_all  :  1, /* sample_type all events */

				exclude_host   :  1, /* don't count in host   */
				exclude_guest  :  1, /* don't count in guest  */

				exclude_callchain_kernel : 1, /* exclude kernel callchains */
				exclude_callchain_user   : 1, /* exclude user callchains */
				mmap2          :  1, /* include mmap with inode data     */
				comm_exec      :  1, /* flag comm events that are due to an exec */
				use_clockid    :  1, /* use @clockid for time fields */
				context_switch :  1, /* context switch data */
				write_backward :  1, /* Write ring buffer from end to beginning */
				namespaces     :  1, /* include namespaces data */
				ksymbol        :  1, /* include ksymbol events */
				bpf_event      :  1, /* include bpf events */
				aux_output     :  1, /* generate AUX records instead of events */
				cgroup         :  1, /* include cgroup events */
				text_poke      :  1, /* include text poke events */
				build_id       :  1, /* use build id in mmap2 events */
				inherit_thread :  1, /* children only inherit if cloned with CLONE_THREAD */
				remove_on_exec :  1, /* event is removed from task on exec */
				sigtrap        :  1, /* send synchronous LKL_SIGTRAP on event */
				__reserved_1   : 26;

	union {
		__lkl__u32		wakeup_events;	  /* wakeup every n events */
		__lkl__u32		wakeup_watermark; /* bytes before wakeup   */
	};

	__lkl__u32			bp_type;
	union {
		__lkl__u64		bp_addr;
		__lkl__u64		kprobe_func; /* for perf_kprobe */
		__lkl__u64		uprobe_path; /* for perf_uprobe */
		__lkl__u64		config1; /* extension of config */
	};
	union {
		__lkl__u64		bp_len;
		__lkl__u64		kprobe_addr; /* when kprobe_func == NULL */
		__lkl__u64		probe_offset; /* for perf_[k,u]probe */
		__lkl__u64		config2; /* extension of config1 */
	};
	__lkl__u64	branch_sample_type; /* enum lkl_perf_branch_sample_type */

	/*
	 * Defines set of user regs to dump on samples.
	 * See asm/perf_regs.h for details.
	 */
	__lkl__u64	sample_regs_user;

	/*
	 * Defines size of the user stack to dump on samples.
	 */
	__lkl__u32	sample_stack_user;

	__lkl__s32	clockid;
	/*
	 * Defines set of regs to dump for each sample
	 * state captured on:
	 *  - precise = 0: PMU interrupt
	 *  - precise > 0: sampled instruction
	 *
	 * See asm/perf_regs.h for details.
	 */
	__lkl__u64	sample_regs_intr;

	/*
	 * Wakeup watermark for AUX area
	 */
	__lkl__u32	aux_watermark;
	__lkl__u16	sample_max_stack;
	__lkl__u16	__reserved_2;
	__lkl__u32	aux_sample_size;
	__lkl__u32	__reserved_3;

	/*
	 * User provided data if sigtrap=1, passed back to user via
	 * lkl_siginfo_t::lkl_si_perf_data, e.g. to permit user to identify the event.
	 * Note, lkl_siginfo_t::lkl_si_perf_data is long-sized, and sig_data will be
	 * truncated accordingly on 32 bit architectures.
	 */
	__lkl__u64	sig_data;
};

/*
 * Structure used by below LKL_PERF_EVENT_IOC_QUERY_BPF command
 * to query bpf programs attached to the same perf tracepoint
 * as the given perf event.
 */
struct lkl_perf_event_query_bpf {
	/*
	 * The below ids array length
	 */
	__lkl__u32	ids_len;
	/*
	 * Set by the kernel to indicate the number of
	 * available programs
	 */
	__lkl__u32	prog_cnt;
	/*
	 * User provided buffer to store program ids
	 */
	__lkl__u32	ids[];
};

/*
 * Ioctls that can be done on a perf event fd:
 */
#define LKL_PERF_EVENT_IOC_ENABLE			_LKL_IO ('$', 0)
#define LKL_PERF_EVENT_IOC_DISABLE			_LKL_IO ('$', 1)
#define LKL_PERF_EVENT_IOC_REFRESH			_LKL_IO ('$', 2)
#define LKL_PERF_EVENT_IOC_RESET			_LKL_IO ('$', 3)
#define LKL_PERF_EVENT_IOC_PERIOD			_LKL_IOW('$', 4, __lkl__u64)
#define LKL_PERF_EVENT_IOC_SET_OUTPUT		_LKL_IO ('$', 5)
#define LKL_PERF_EVENT_IOC_SET_FILTER		_LKL_IOW('$', 6, char *)
#define LKL_PERF_EVENT_IOC_ID			_LKL_IOR('$', 7, __lkl__u64 *)
#define LKL_PERF_EVENT_IOC_SET_BPF			_LKL_IOW('$', 8, __lkl__u32)
#define LKL_PERF_EVENT_IOC_PAUSE_OUTPUT		_LKL_IOW('$', 9, __lkl__u32)
#define LKL_PERF_EVENT_IOC_QUERY_BPF		_LKL_IOWR('$', 10, struct lkl_perf_event_query_bpf *)
#define LKL_PERF_EVENT_IOC_MODIFY_ATTRIBUTES	_LKL_IOW('$', 11, struct lkl_perf_event_attr *)

enum lkl_perf_event_ioc_flags {
	LKL_PERF_IOC_FLAG_GROUP		= 1U << 0,
};

/*
 * Structure of the page that can be mapped via mmap
 */
struct lkl_perf_event_mmap_page {
	__lkl__u32	version;		/* version number of this structure */
	__lkl__u32	compat_version;		/* lowest version this is compat with */

	/*
	 * Bits needed to read the hw events in user-space.
	 *
	 *   lkl_u32 seq, time_mult, time_shift, index, width;
	 *   lkl_u64 count, enabled, running;
	 *   lkl_u64 cyc, time_offset;
	 *   lkl_s64 pmc = 0;
	 *
	 *   do {
	 *     seq = pc->lock;
	 *     barrier()
	 *
	 *     enabled = pc->time_enabled;
	 *     running = pc->time_running;
	 *
	 *     if (pc->cap_usr_time && enabled != running) {
	 *       cyc = rdtsc();
	 *       time_offset = pc->time_offset;
	 *       time_mult   = pc->time_mult;
	 *       time_shift  = pc->time_shift;
	 *     }
	 *
	 *     index = pc->index;
	 *     count = pc->offset;
	 *     if (pc->cap_user_rdpmc && index) {
	 *       width = pc->pmc_width;
	 *       pmc = rdpmc(index - 1);
	 *     }
	 *
	 *     barrier();
	 *   } while (pc->lock != seq);
	 *
	 * NOTE: for obvious reason this only works on self-monitoring
	 *       processes.
	 */
	__lkl__u32	lock;			/* seqlock for synchronization */
	__lkl__u32	index;			/* hardware event identifier */
	__lkl__s64	offset;			/* add to hardware event value */
	__lkl__u64	time_enabled;		/* time event active */
	__lkl__u64	time_running;		/* time event on cpu */
	union {
		__lkl__u64	capabilities;
		struct {
			__lkl__u64	cap_bit0		: 1, /* Always 0, deprecated, see commit 860f085b74e9 */
				cap_bit0_is_deprecated	: 1, /* Always 1, signals that bit 0 is zero */

				cap_user_rdpmc		: 1, /* The RDPMC instruction can be used to read counts */
				cap_user_time		: 1, /* The time_{shift,mult,offset} fields are used */
				cap_user_time_zero	: 1, /* The time_zero field is used */
				cap_user_time_short	: 1, /* the time_{cycle,mask} fields are used */
				cap_____res		: 58;
		};
	};

	/*
	 * If cap_user_rdpmc this field provides the bit-width of the value
	 * read using the rdpmc() or equivalent instruction. This can be used
	 * to sign extend the result like:
	 *
	 *   pmc <<= 64 - width;
	 *   pmc >>= 64 - width; // signed shift right
	 *   count += pmc;
	 */
	__lkl__u16	pmc_width;

	/*
	 * If cap_usr_time the below fields can be used to compute the time
	 * delta since time_enabled (in ns) using rdtsc or similar.
	 *
	 *   lkl_u64 quot, rem;
	 *   lkl_u64 delta;
	 *
	 *   quot = (cyc >> time_shift);
	 *   rem = cyc & (((lkl_u64)1 << time_shift) - 1);
	 *   delta = time_offset + quot * time_mult +
	 *              ((rem * time_mult) >> time_shift);
	 *
	 * Where time_offset,time_mult,time_shift and cyc are read in the
	 * seqcount loop described above. This delta can then be added to
	 * enabled and possible running (if index), improving the scaling:
	 *
	 *   enabled += delta;
	 *   if (index)
	 *     running += delta;
	 *
	 *   quot = count / running;
	 *   rem  = count % running;
	 *   count = quot * enabled + (rem * enabled) / running;
	 */
	__lkl__u16	time_shift;
	__lkl__u32	time_mult;
	__lkl__u64	time_offset;
	/*
	 * If cap_usr_time_zero, the hardware clock (e.g. TSC) can be calculated
	 * from sample timestamps.
	 *
	 *   time = timestamp - time_zero;
	 *   quot = time / time_mult;
	 *   rem  = time % time_mult;
	 *   cyc = (quot << time_shift) + (rem << time_shift) / time_mult;
	 *
	 * And vice versa:
	 *
	 *   quot = cyc >> time_shift;
	 *   rem  = cyc & (((lkl_u64)1 << time_shift) - 1);
	 *   timestamp = time_zero + quot * time_mult +
	 *               ((rem * time_mult) >> time_shift);
	 */
	__lkl__u64	time_zero;

	__lkl__u32	size;			/* Header size up to __reserved[] fields. */
	__lkl__u32	__reserved_1;

	/*
	 * If cap_usr_time_short, the hardware clock is less than 64bit wide
	 * and we must compute the 'cyc' value, as used by cap_usr_time, as:
	 *
	 *   cyc = time_cycles + ((cyc - time_cycles) & time_mask)
	 *
	 * NOTE: this form is explicitly chosen such that cap_usr_time_short
	 *       is a correction on top of cap_usr_time, and code that doesn't
	 *       know about cap_usr_time_short still works under the assumption
	 *       the counter doesn't wrap.
	 */
	__lkl__u64	time_cycles;
	__lkl__u64	time_mask;

		/*
		 * Hole for extension of the self monitor capabilities
		 */

	__lkl__u8	__reserved[116*8];	/* align to 1k. */

	/*
	 * Control data for the mmap() data buffer.
	 *
	 * User-space reading the @data_head value should issue an smp_rmb(),
	 * after reading this value.
	 *
	 * When the mapping is PROT_WRITE the @data_tail value should be
	 * written by userspace to reflect the last read data, after issueing
	 * an smp_mb() to separate the data read from the ->data_tail store.
	 * In this case the kernel will not over-write unread data.
	 *
	 * See perf_output_put_handle() for the data ordering.
	 *
	 * data_{offset,size} indicate the location and size of the perf record
	 * buffer within the mmapped area.
	 */
	__lkl__u64   data_head;		/* head in the data section */
	__lkl__u64	data_tail;		/* user-space written tail */
	__lkl__u64	data_offset;		/* where the buffer starts */
	__lkl__u64	data_size;		/* data buffer size */

	/*
	 * AUX area is defined by aux_{offset,size} fields that should be set
	 * by the userspace, so that
	 *
	 *   aux_offset >= data_offset + data_size
	 *
	 * prior to mmap()ing it. Size of the mmap()ed area should be aux_size.
	 *
	 * Ring buffer pointers aux_{head,tail} have the same semantics as
	 * data_{head,tail} and same ordering rules apply.
	 */
	__lkl__u64	aux_head;
	__lkl__u64	aux_tail;
	__lkl__u64	aux_offset;
	__lkl__u64	aux_size;
};

/*
 * The current state of perf_event_header::misc bits usage:
 * ('|' used bit, '-' unused bit)
 *
 *  012         CDEF
 *  |||---------||||
 *
 *  Where:
 *    0-2     CPUMODE_MASK
 *
 *    C       PROC_MAP_PARSE_TIMEOUT
 *    D       MMAP_DATA / COMM_EXEC / FORK_EXEC / SWITCH_OUT
 *    E       MMAP_BUILD_ID / EXACT_IP / SCHED_OUT_PREEMPT
 *    F       (reserved)
 */

#define LKL_PERF_RECORD_MISC_CPUMODE_MASK		(7 << 0)
#define LKL_PERF_RECORD_MISC_CPUMODE_UNKNOWN	(0 << 0)
#define LKL_PERF_RECORD_MISC_KERNEL			(1 << 0)
#define LKL_PERF_RECORD_MISC_USER			(2 << 0)
#define LKL_PERF_RECORD_MISC_HYPERVISOR		(3 << 0)
#define LKL_PERF_RECORD_MISC_GUEST_KERNEL		(4 << 0)
#define LKL_PERF_RECORD_MISC_GUEST_USER		(5 << 0)

/*
 * Indicates that /proc/PID/maps parsing are truncated by time out.
 */
#define LKL_PERF_RECORD_MISC_PROC_MAP_PARSE_TIMEOUT	(1 << 12)
/*
 * Following PERF_RECORD_MISC_* are used on different
 * events, so can reuse the same bit position:
 *
 *   LKL_PERF_RECORD_MISC_MMAP_DATA  - LKL_PERF_RECORD_MMAP* events
 *   LKL_PERF_RECORD_MISC_COMM_EXEC  - LKL_PERF_RECORD_COMM event
 *   LKL_PERF_RECORD_MISC_FORK_EXEC  - LKL_PERF_RECORD_FORK event (perf internal)
 *   LKL_PERF_RECORD_MISC_SWITCH_OUT - LKL_PERF_RECORD_SWITCH* events
 */
#define LKL_PERF_RECORD_MISC_MMAP_DATA		(1 << 13)
#define LKL_PERF_RECORD_MISC_COMM_EXEC		(1 << 13)
#define LKL_PERF_RECORD_MISC_FORK_EXEC		(1 << 13)
#define LKL_PERF_RECORD_MISC_SWITCH_OUT		(1 << 13)
/*
 * These PERF_RECORD_MISC_* flags below are safely reused
 * for the following events:
 *
 *   LKL_PERF_RECORD_MISC_EXACT_IP           - LKL_PERF_RECORD_SAMPLE of precise events
 *   LKL_PERF_RECORD_MISC_SWITCH_OUT_PREEMPT - LKL_PERF_RECORD_SWITCH* events
 *   LKL_PERF_RECORD_MISC_MMAP_BUILD_ID      - LKL_PERF_RECORD_MMAP2 event
 *
 *
 * LKL_PERF_RECORD_MISC_EXACT_IP:
 *   Indicates that the content of LKL_PERF_SAMPLE_IP points to
 *   the actual instruction that triggered the event. See also
 *   perf_event_attr::precise_ip.
 *
 * LKL_PERF_RECORD_MISC_SWITCH_OUT_PREEMPT:
 *   Indicates that thread was preempted in TASK_RUNNING state.
 *
 * LKL_PERF_RECORD_MISC_MMAP_BUILD_ID:
 *   Indicates that mmap2 event carries build id data.
 */
#define LKL_PERF_RECORD_MISC_EXACT_IP		(1 << 14)
#define LKL_PERF_RECORD_MISC_SWITCH_OUT_PREEMPT	(1 << 14)
#define LKL_PERF_RECORD_MISC_MMAP_BUILD_ID		(1 << 14)
/*
 * Reserve the last bit to indicate some extended misc field
 */
#define LKL_PERF_RECORD_MISC_EXT_RESERVED		(1 << 15)

struct lkl_perf_event_header {
	__lkl__u32	type;
	__lkl__u16	misc;
	__lkl__u16	size;
};

struct lkl_perf_ns_link_info {
	__lkl__u64	dev;
	__lkl__u64	ino;
};

enum {
	LKL_NET_NS_INDEX		= 0,
	LKL_UTS_NS_INDEX		= 1,
	LKL_IPC_NS_INDEX		= 2,
	LKL_PID_NS_INDEX		= 3,
	LKL_USER_NS_INDEX		= 4,
	LKL_MNT_NS_INDEX		= 5,
	LKL_CGROUP_NS_INDEX		= 6,

	LKL_NR_NAMESPACES,		/* number of available namespaces */
};

enum lkl_perf_event_type {

	/*
	 * If perf_event_attr.sample_id_all is set then all event types will
	 * have the sample_type selected fields related to where/when
	 * (identity) an event took place (TID, TIME, ID, STREAM_ID, CPU,
	 * IDENTIFIER) described in LKL_PERF_RECORD_SAMPLE below, it will be stashed
	 * just after the perf_event_header and the fields already present for
	 * the existing fields, i.e. at the end of the payload. That way a newer
	 * perf.data file will be supported by older perf tools, with these new
	 * optional fields being ignored.
	 *
	 * struct lkl_sample_id {
	 * 	{ lkl_u32			pid, tid; } && LKL_PERF_SAMPLE_TID
	 * 	{ lkl_u64			time;     } && LKL_PERF_SAMPLE_TIME
	 * 	{ lkl_u64			id;       } && LKL_PERF_SAMPLE_ID
	 * 	{ lkl_u64			stream_id;} && LKL_PERF_SAMPLE_STREAM_ID
	 * 	{ lkl_u32			cpu, res; } && LKL_PERF_SAMPLE_CPU
	 *	{ lkl_u64			id;	  } && LKL_PERF_SAMPLE_IDENTIFIER
	 * } && perf_event_attr::sample_id_all
	 *
	 * Note that LKL_PERF_SAMPLE_IDENTIFIER duplicates LKL_PERF_SAMPLE_ID.  The
	 * advantage of LKL_PERF_SAMPLE_IDENTIFIER is that its position is fixed
	 * relative to header.size.
	 */

	/*
	 * The MMAP events record the PROT_EXEC mappings so that we can
	 * correlate userspace IPs to code. They have the following structure:
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *
	 *	lkl_u32				pid, tid;
	 *	lkl_u64				addr;
	 *	lkl_u64				len;
	 *	lkl_u64				pgoff;
	 *	char				filename[];
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_MMAP			= 1,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u64				id;
	 *	lkl_u64				lost;
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_LOST			= 2,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *
	 *	lkl_u32				pid, tid;
	 *	char				comm[];
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_COMM			= 3,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u32				pid, ppid;
	 *	lkl_u32				tid, ptid;
	 *	lkl_u64				time;
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_EXIT			= 4,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u64				time;
	 *	lkl_u64				id;
	 *	lkl_u64				stream_id;
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_THROTTLE			= 5,
	LKL_PERF_RECORD_UNTHROTTLE			= 6,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u32				pid, ppid;
	 *	lkl_u32				tid, ptid;
	 *	lkl_u64				time;
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_FORK			= 7,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u32				pid, tid;
	 *
	 *	struct lkl_read_format		values;
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_READ			= 8,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *
	 *	#
	 *	# Note that LKL_PERF_SAMPLE_IDENTIFIER duplicates LKL_PERF_SAMPLE_ID.
	 *	# The advantage of LKL_PERF_SAMPLE_IDENTIFIER is that its position
	 *	# is fixed relative to header.
	 *	#
	 *
	 *	{ lkl_u64			id;	  } && LKL_PERF_SAMPLE_IDENTIFIER
	 *	{ lkl_u64			ip;	  } && LKL_PERF_SAMPLE_IP
	 *	{ lkl_u32			pid, tid; } && LKL_PERF_SAMPLE_TID
	 *	{ lkl_u64			time;     } && LKL_PERF_SAMPLE_TIME
	 *	{ lkl_u64			addr;     } && LKL_PERF_SAMPLE_ADDR
	 *	{ lkl_u64			id;	  } && LKL_PERF_SAMPLE_ID
	 *	{ lkl_u64			stream_id;} && LKL_PERF_SAMPLE_STREAM_ID
	 *	{ lkl_u32			cpu, res; } && LKL_PERF_SAMPLE_CPU
	 *	{ lkl_u64			period;   } && LKL_PERF_SAMPLE_PERIOD
	 *
	 *	{ struct lkl_read_format	values;	  } && LKL_PERF_SAMPLE_READ
	 *
	 *	{ lkl_u64			nr,
	 *	  lkl_u64			ips[nr];  } && LKL_PERF_SAMPLE_CALLCHAIN
	 *
	 *	#
	 *	# The RAW record below is opaque data wrt the ABI
	 *	#
	 *	# That is, the ABI doesn't make any promises wrt to
	 *	# the stability of its content, it may vary depending
	 *	# on event, hardware, kernel version and phase of
	 *	# the moon.
	 *	#
	 *	# In other words, LKL_PERF_SAMPLE_RAW contents are not an ABI.
	 *	#
	 *
	 *	{ lkl_u32			size;
	 *	  char                  data[size];}&& LKL_PERF_SAMPLE_RAW
	 *
	 *	{ lkl_u64                   nr;
	 *	  { lkl_u64	hw_idx; } && LKL_PERF_SAMPLE_BRANCH_HW_INDEX
	 *        { lkl_u64 from, to, flags } lbr[nr];
	 *      } && LKL_PERF_SAMPLE_BRANCH_STACK
	 *
	 * 	{ lkl_u64			abi; # enum lkl_perf_sample_regs_abi
	 * 	  lkl_u64			regs[weight(mask)]; } && LKL_PERF_SAMPLE_REGS_USER
	 *
	 * 	{ lkl_u64			size;
	 * 	  char			data[size];
	 * 	  lkl_u64			dyn_size; } && LKL_PERF_SAMPLE_STACK_USER
	 *
	 *	{ union lkl_perf_sample_weight
	 *	 {
	 *		lkl_u64		full; && LKL_PERF_SAMPLE_WEIGHT
	 *	#if defined(__LKL__LITTLE_ENDIAN_BITFIELD)
	 *		struct {
	 *			lkl_u32	var1_dw;
	 *			u16	var2_w;
	 *			u16	var3_w;
	 *		} && LKL_PERF_SAMPLE_WEIGHT_STRUCT
	 *	#elif defined(__LKL__BIG_ENDIAN_BITFIELD)
	 *		struct {
	 *			u16	var3_w;
	 *			u16	var2_w;
	 *			lkl_u32	var1_dw;
	 *		} && LKL_PERF_SAMPLE_WEIGHT_STRUCT
	 *	#endif
	 *	 }
	 *	}
	 *	{ lkl_u64			data_src; } && LKL_PERF_SAMPLE_DATA_SRC
	 *	{ lkl_u64			transaction; } && LKL_PERF_SAMPLE_TRANSACTION
	 *	{ lkl_u64			abi; # enum lkl_perf_sample_regs_abi
	 *	  lkl_u64			regs[weight(mask)]; } && LKL_PERF_SAMPLE_REGS_INTR
	 *	{ lkl_u64			phys_addr;} && LKL_PERF_SAMPLE_PHYS_ADDR
	 *	{ lkl_u64			size;
	 *	  char			data[size]; } && LKL_PERF_SAMPLE_AUX
	 *	{ lkl_u64			data_page_size;} && LKL_PERF_SAMPLE_DATA_PAGE_SIZE
	 *	{ lkl_u64			code_page_size;} && LKL_PERF_SAMPLE_CODE_PAGE_SIZE
	 * };
	 */
	LKL_PERF_RECORD_SAMPLE			= 9,

	/*
	 * The MMAP2 records are an augmented version of MMAP, they add
	 * maj, min, ino numbers to be used to uniquely identify each mapping
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *
	 *	lkl_u32				pid, tid;
	 *	lkl_u64				addr;
	 *	lkl_u64				len;
	 *	lkl_u64				pgoff;
	 *	union {
	 *		struct {
	 *			lkl_u32		maj;
	 *			lkl_u32		min;
	 *			lkl_u64		ino;
	 *			lkl_u64		ino_generation;
	 *		};
	 *		struct {
	 *			u8		build_id_size;
	 *			u8		__reserved_1;
	 *			u16		__reserved_2;
	 *			u8		build_id[20];
	 *		};
	 *	};
	 *	lkl_u32				prot, flags;
	 *	char				filename[];
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_MMAP2			= 10,

	/*
	 * Records that new data landed in the AUX buffer part.
	 *
	 * struct {
	 * 	struct lkl_perf_event_header	header;
	 *
	 * 	lkl_u64				aux_offset;
	 * 	lkl_u64				aux_size;
	 *	lkl_u64				flags;
	 * 	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_AUX				= 11,

	/*
	 * Indicates that instruction trace has started
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u32				pid;
	 *	lkl_u32				tid;
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_ITRACE_START		= 12,

	/*
	 * Records the dropped/lost sample number.
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *
	 *	lkl_u64				lost;
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_LOST_SAMPLES		= 13,

	/*
	 * Records a context switch in or out (flagged by
	 * LKL_PERF_RECORD_MISC_SWITCH_OUT). See also
	 * LKL_PERF_RECORD_SWITCH_CPU_WIDE.
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_SWITCH			= 14,

	/*
	 * CPU-wide version of LKL_PERF_RECORD_SWITCH with next_prev_pid and
	 * next_prev_tid that are the next (switching out) or previous
	 * (switching in) pid/tid.
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u32				next_prev_pid;
	 *	lkl_u32				next_prev_tid;
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_SWITCH_CPU_WIDE		= 15,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u32				pid;
	 *	lkl_u32				tid;
	 *	lkl_u64				nr_namespaces;
	 *	{ lkl_u64				dev, inode; } [nr_namespaces];
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_NAMESPACES			= 16,

	/*
	 * Record ksymbol register/unregister events:
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u64				addr;
	 *	lkl_u32				len;
	 *	u16				ksym_type;
	 *	u16				flags;
	 *	char				name[];
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_KSYMBOL			= 17,

	/*
	 * Record bpf events:
	 *  enum lkl_perf_bpf_event_type {
	 *	LKL_PERF_BPF_EVENT_UNKNOWN		= 0,
	 *	LKL_PERF_BPF_EVENT_PROG_LOAD	= 1,
	 *	LKL_PERF_BPF_EVENT_PROG_UNLOAD	= 2,
	 *  };
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	u16				type;
	 *	u16				flags;
	 *	lkl_u32				id;
	 *	u8				tag[LKL_BPF_TAG_SIZE];
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_BPF_EVENT			= 18,

	/*
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u64				id;
	 *	char				path[];
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_CGROUP			= 19,

	/*
	 * Records changes to kernel text i.e. self-modified code. 'old_len' is
	 * the number of old bytes, 'new_len' is the number of new bytes. Either
	 * 'old_len' or 'new_len' may be zero to indicate, for example, the
	 * addition or removal of a trampoline. 'bytes' contains the old bytes
	 * followed immediately by the new bytes.
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u64				addr;
	 *	u16				old_len;
	 *	u16				new_len;
	 *	u8				bytes[];
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_TEXT_POKE			= 20,

	/*
	 * Data written to the AUX area by hardware due to aux_output, may need
	 * to be matched to the event by an architecture-specific hardware ID.
	 * This records the hardware ID, but requires sample_id to provide the
	 * event ID. e.g. Intel PT uses this record to disambiguate PEBS-via-PT
	 * records from multiple events.
	 *
	 * struct {
	 *	struct lkl_perf_event_header	header;
	 *	lkl_u64				hw_id;
	 *	struct lkl_sample_id		sample_id;
	 * };
	 */
	LKL_PERF_RECORD_AUX_OUTPUT_HW_ID		= 21,

	LKL_PERF_RECORD_MAX,			/* non-ABI */
};

enum lkl_perf_record_ksymbol_type {
	LKL_PERF_RECORD_KSYMBOL_TYPE_UNKNOWN	= 0,
	LKL_PERF_RECORD_KSYMBOL_TYPE_BPF		= 1,
	/*
	 * Out of line code such as kprobe-replaced instructions or optimized
	 * kprobes or ftrace trampolines.
	 */
	LKL_PERF_RECORD_KSYMBOL_TYPE_OOL		= 2,
	LKL_PERF_RECORD_KSYMBOL_TYPE_MAX		/* non-ABI */
};

#define LKL_PERF_RECORD_KSYMBOL_FLAGS_UNREGISTER	(1 << 0)

enum lkl_perf_bpf_event_type {
	LKL_PERF_BPF_EVENT_UNKNOWN		= 0,
	LKL_PERF_BPF_EVENT_PROG_LOAD	= 1,
	LKL_PERF_BPF_EVENT_PROG_UNLOAD	= 2,
	LKL_PERF_BPF_EVENT_MAX,		/* non-ABI */
};

#define LKL_PERF_MAX_STACK_DEPTH		127
#define LKL_PERF_MAX_CONTEXTS_PER_STACK	  8

enum lkl_perf_callchain_context {
	LKL_PERF_CONTEXT_HV			= (__lkl__u64)-32,
	LKL_PERF_CONTEXT_KERNEL		= (__lkl__u64)-128,
	LKL_PERF_CONTEXT_USER		= (__lkl__u64)-512,

	LKL_PERF_CONTEXT_GUEST		= (__lkl__u64)-2048,
	LKL_PERF_CONTEXT_GUEST_KERNEL	= (__lkl__u64)-2176,
	LKL_PERF_CONTEXT_GUEST_USER		= (__lkl__u64)-2560,

	LKL_PERF_CONTEXT_MAX		= (__lkl__u64)-4095,
};

/**
 * LKL_PERF_RECORD_AUX::flags bits
 */
#define LKL_PERF_AUX_FLAG_TRUNCATED			0x01	/* record was truncated to fit */
#define LKL_PERF_AUX_FLAG_OVERWRITE			0x02	/* snapshot from overwrite mode */
#define LKL_PERF_AUX_FLAG_PARTIAL			0x04	/* record contains gaps */
#define LKL_PERF_AUX_FLAG_COLLISION			0x08	/* sample collided with another */
#define LKL_PERF_AUX_FLAG_PMU_FORMAT_TYPE_MASK	0xff00	/* PMU specific trace format type */

/* CoreSight PMU AUX buffer formats */
#define LKL_PERF_AUX_FLAG_CORESIGHT_FORMAT_CORESIGHT	0x0000 /* Default for backward compatibility */
#define LKL_PERF_AUX_FLAG_CORESIGHT_FORMAT_RAW		0x0100 /* Raw format of the source */

#define LKL_PERF_FLAG_FD_NO_GROUP		(1UL << 0)
#define LKL_PERF_FLAG_FD_OUTPUT		(1UL << 1)
#define LKL_PERF_FLAG_PID_CGROUP		(1UL << 2) /* pid=cgroup id, per-cpu mode only */
#define LKL_PERF_FLAG_FD_CLOEXEC		(1UL << 3) /* LKL_O_CLOEXEC */

#if defined(__LKL__LITTLE_ENDIAN_BITFIELD)
union lkl_perf_mem_data_src {
	__lkl__u64 val;
	struct {
		__lkl__u64   mem_op:5,	/* type of opcode */
			mem_lvl:14,	/* memory hierarchy level */
			mem_snoop:5,	/* snoop mode */
			mem_lock:2,	/* lock instr */
			mem_dtlb:7,	/* tlb access */
			mem_lvl_num:4,	/* memory hierarchy level number */
			mem_remote:1,   /* remote */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_blk:3,	/* access blocked */
			mem_hops:3,	/* hop level */
			mem_rsvd:18;
	};
};
#elif defined(__LKL__BIG_ENDIAN_BITFIELD)
union lkl_perf_mem_data_src {
	__lkl__u64 val;
	struct {
		__lkl__u64	mem_rsvd:18,
			mem_hops:3,	/* hop level */
			mem_blk:3,	/* access blocked */
			mem_snoopx:2,	/* snoop mode, ext */
			mem_remote:1,   /* remote */
			mem_lvl_num:4,	/* memory hierarchy level number */
			mem_dtlb:7,	/* tlb access */
			mem_lock:2,	/* lock instr */
			mem_snoop:5,	/* snoop mode */
			mem_lvl:14,	/* memory hierarchy level */
			mem_op:5;	/* type of opcode */
	};
};
#else
#error "Unknown endianness"
#endif

/* type of opcode (load/store/prefetch,code) */
#define LKL_PERF_MEM_OP_NA		0x01 /* not available */
#define LKL_PERF_MEM_OP_LOAD	0x02 /* load instruction */
#define LKL_PERF_MEM_OP_STORE	0x04 /* store instruction */
#define LKL_PERF_MEM_OP_PFETCH	0x08 /* prefetch */
#define LKL_PERF_MEM_OP_EXEC	0x10 /* code (execution) */
#define LKL_PERF_MEM_OP_SHIFT	0

/*
 * PERF_MEM_LVL_* namespace being depricated to some extent in the
 * favour of newer composite PERF_MEM_{LVLNUM_,REMOTE_,SNOOPX_} fields.
 * Supporting this namespace inorder to not break defined ABIs.
 *
 * memory hierarchy (memory level, hit or miss)
 */
#define LKL_PERF_MEM_LVL_NA		0x01  /* not available */
#define LKL_PERF_MEM_LVL_HIT	0x02  /* hit level */
#define LKL_PERF_MEM_LVL_MISS	0x04  /* miss level  */
#define LKL_PERF_MEM_LVL_L1		0x08  /* L1 */
#define LKL_PERF_MEM_LVL_LFB	0x10  /* Line Fill Buffer */
#define LKL_PERF_MEM_LVL_L2		0x20  /* L2 */
#define LKL_PERF_MEM_LVL_L3		0x40  /* L3 */
#define LKL_PERF_MEM_LVL_LOC_RAM	0x80  /* Local DRAM */
#define LKL_PERF_MEM_LVL_REM_RAM1	0x100 /* Remote DRAM (1 hop) */
#define LKL_PERF_MEM_LVL_REM_RAM2	0x200 /* Remote DRAM (2 hops) */
#define LKL_PERF_MEM_LVL_REM_CCE1	0x400 /* Remote Cache (1 hop) */
#define LKL_PERF_MEM_LVL_REM_CCE2	0x800 /* Remote Cache (2 hops) */
#define LKL_PERF_MEM_LVL_IO		0x1000 /* I/O memory */
#define LKL_PERF_MEM_LVL_UNC	0x2000 /* Uncached memory */
#define LKL_PERF_MEM_LVL_SHIFT	5

#define LKL_PERF_MEM_REMOTE_REMOTE	0x01  /* Remote */
#define LKL_PERF_MEM_REMOTE_SHIFT	37

#define LKL_PERF_MEM_LVLNUM_L1	0x01 /* L1 */
#define LKL_PERF_MEM_LVLNUM_L2	0x02 /* L2 */
#define LKL_PERF_MEM_LVLNUM_L3	0x03 /* L3 */
#define LKL_PERF_MEM_LVLNUM_L4	0x04 /* L4 */
/* 5-0x8 available */
#define LKL_PERF_MEM_LVLNUM_CXL	0x09 /* CXL */
#define LKL_PERF_MEM_LVLNUM_IO	0x0a /* I/O */
#define LKL_PERF_MEM_LVLNUM_ANY_CACHE 0x0b /* Any cache */
#define LKL_PERF_MEM_LVLNUM_LFB	0x0c /* LFB */
#define LKL_PERF_MEM_LVLNUM_RAM	0x0d /* RAM */
#define LKL_PERF_MEM_LVLNUM_PMEM	0x0e /* PMEM */
#define LKL_PERF_MEM_LVLNUM_NA	0x0f /* N/A */

#define LKL_PERF_MEM_LVLNUM_SHIFT	33

/* snoop mode */
#define LKL_PERF_MEM_SNOOP_NA	0x01 /* not available */
#define LKL_PERF_MEM_SNOOP_NONE	0x02 /* no snoop */
#define LKL_PERF_MEM_SNOOP_HIT	0x04 /* snoop hit */
#define LKL_PERF_MEM_SNOOP_MISS	0x08 /* snoop miss */
#define LKL_PERF_MEM_SNOOP_HITM	0x10 /* snoop hit modified */
#define LKL_PERF_MEM_SNOOP_SHIFT	19

#define LKL_PERF_MEM_SNOOPX_FWD	0x01 /* forward */
#define LKL_PERF_MEM_SNOOPX_PEER	0x02 /* xfer from peer */
#define LKL_PERF_MEM_SNOOPX_SHIFT  38

/* locked instruction */
#define LKL_PERF_MEM_LOCK_NA	0x01 /* not available */
#define LKL_PERF_MEM_LOCK_LOCKED	0x02 /* locked transaction */
#define LKL_PERF_MEM_LOCK_SHIFT	24

/* TLB access */
#define LKL_PERF_MEM_TLB_NA		0x01 /* not available */
#define LKL_PERF_MEM_TLB_HIT	0x02 /* hit level */
#define LKL_PERF_MEM_TLB_MISS	0x04 /* miss level */
#define LKL_PERF_MEM_TLB_L1		0x08 /* L1 */
#define LKL_PERF_MEM_TLB_L2		0x10 /* L2 */
#define LKL_PERF_MEM_TLB_WK		0x20 /* Hardware Walker*/
#define LKL_PERF_MEM_TLB_OS		0x40 /* OS fault handler */
#define LKL_PERF_MEM_TLB_SHIFT	26

/* Access blocked */
#define LKL_PERF_MEM_BLK_NA		0x01 /* not available */
#define LKL_PERF_MEM_BLK_DATA	0x02 /* data could not be forwarded */
#define LKL_PERF_MEM_BLK_ADDR	0x04 /* address conflict */
#define LKL_PERF_MEM_BLK_SHIFT	40

/* hop level */
#define LKL_PERF_MEM_HOPS_0		0x01 /* remote core, same node */
#define LKL_PERF_MEM_HOPS_1		0x02 /* remote node, same socket */
#define LKL_PERF_MEM_HOPS_2		0x03 /* remote socket, same board */
#define LKL_PERF_MEM_HOPS_3		0x04 /* remote board */
/* 5-7 available */
#define LKL_PERF_MEM_HOPS_SHIFT	43

#define LKL_PERF_MEM_S(a, s) \
	(((__lkl__u64)PERF_MEM_##a##_##s) << PERF_MEM_##a##_SHIFT)

/*
 * single taken branch record layout:
 *
 *      from: source instruction (may not always be a branch insn)
 *        to: branch target
 *   mispred: branch target was mispredicted
 * predicted: branch target was predicted
 *
 * support for mispred, predicted is optional. In case it
 * is not supported mispred = predicted = 0.
 *
 *     in_tx: running in a hardware transaction
 *     abort: aborting a hardware transaction
 *    cycles: cycles from last branch (or 0 if not supported)
 *      type: branch type
 *      spec: branch speculation info (or 0 if not supported)
 */
struct lkl_perf_branch_entry {
	__lkl__u64	from;
	__lkl__u64	to;
	__lkl__u64	mispred:1,  /* target mispredicted */
		predicted:1,/* target predicted */
		in_tx:1,    /* in transaction */
		abort:1,    /* transaction abort */
		cycles:16,  /* cycle count to last branch */
		type:4,     /* branch type */
		spec:2,     /* branch speculation info */
		new_type:4, /* additional branch type */
		priv:3,     /* privilege level */
		reserved:31;
};

union lkl_perf_sample_weight {
	__lkl__u64		full;
#if defined(__LKL__LITTLE_ENDIAN_BITFIELD)
	struct {
		__lkl__u32	var1_dw;
		__lkl__u16	var2_w;
		__lkl__u16	var3_w;
	};
#elif defined(__LKL__BIG_ENDIAN_BITFIELD)
	struct {
		__lkl__u16	var3_w;
		__lkl__u16	var2_w;
		__lkl__u32	var1_dw;
	};
#else
#error "Unknown endianness"
#endif
};

#endif /* _LKL_LINUX_PERF_EVENT_H */
