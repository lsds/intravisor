/* SPDX-License-Identifier: (GPL-2.0 WITH Linux-syscall-note) OR MIT */
/*
 * Header file for the io_uring interface.
 *
 * Copyright (C) 2019 Jens Axboe
 * Copyright (C) 2019 Christoph Hellwig
 */
#ifndef LKL_LINUX_IO_URING_H
#define LKL_LINUX_IO_URING_H

#include <lkl/linux/fs.h>
#include <lkl/linux/types.h>
#include <lkl/linux/time_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * IO submission data structure (Submission Queue Entry)
 */
struct lkl_io_uring_sqe {
	__lkl__u8	opcode;		/* type of operation for this sqe */
	__lkl__u8	flags;		/* IOSQE_ flags */
	__lkl__u16	ioprio;		/* ioprio for the request */
	__lkl__s32	fd;		/* file descriptor to do IO on */
	union {
		__lkl__u64	off;	/* offset into file */
		__lkl__u64	addr2;
		struct {
			__lkl__u32	cmd_op;
			__lkl__u32	__pad1;
		};
	};
	union {
		__lkl__u64	addr;	/* pointer to buffer or iovecs */
		__lkl__u64	splice_off_in;
	};
	__lkl__u32	len;		/* buffer size or number of iovecs */
	union {
		__lkl__kernel_rwf_t	rw_flags;
		__lkl__u32		fsync_flags;
		__lkl__u16		poll_events;	/* compatibility */
		__lkl__u32		poll32_events;	/* word-reversed for BE */
		__lkl__u32		sync_range_flags;
		__lkl__u32		msg_flags;
		__lkl__u32		timeout_flags;
		__lkl__u32		accept_flags;
		__lkl__u32		cancel_flags;
		__lkl__u32		open_flags;
		__lkl__u32		statx_flags;
		__lkl__u32		fadvise_advice;
		__lkl__u32		splice_flags;
		__lkl__u32		rename_flags;
		__lkl__u32		unlink_flags;
		__lkl__u32		hardlink_flags;
		__lkl__u32		xattr_flags;
		__lkl__u32		msg_ring_flags;
		__lkl__u32		uring_cmd_flags;
	};
	__lkl__u64	user_data;	/* data to be passed back at completion time */
	/* pack this to avoid bogus arm OABI complaints */
	union {
		/* index into fixed buffers, if used */
		__lkl__u16	buf_index;
		/* for grouped buffer selection */
		__lkl__u16	buf_group;
	} __attribute__((packed));
	/* personality to use, if used */
	__lkl__u16	personality;
	union {
		__lkl__s32	splice_fd_in;
		__lkl__u32	file_index;
		struct {
			__lkl__u16	addr_len;
			__lkl__u16	__pad3[1];
		};
	};
	union {
		struct {
			__lkl__u64	addr3;
			__lkl__u64	__pad2[1];
		};
		/*
		 * If the ring is initialized with LKL_IORING_SETUP_SQE128, then
		 * this field is used for 80 bytes of arbitrary command data
		 */
		__lkl__u8	cmd[0];
	};
};

/*
 * If sqe->file_index is set to this for opcodes that instantiate a new
 * direct descriptor (like openat/openat2/accept), then io_uring will allocate
 * an available direct descriptor instead of having the application pass one
 * in. The picked direct descriptor will be returned in cqe->res, or -LKL_ENFILE
 * if the space is full.
 */
#define LKL_IORING_FILE_INDEX_ALLOC		(~0U)

enum {
	LKL_IOSQE_FIXED_FILE_BIT,
	LKL_IOSQE_IO_DRAIN_BIT,
	LKL_IOSQE_IO_LINK_BIT,
	LKL_IOSQE_IO_HARDLINK_BIT,
	LKL_IOSQE_ASYNC_BIT,
	LKL_IOSQE_BUFFER_SELECT_BIT,
	LKL_IOSQE_CQE_SKIP_SUCCESS_BIT,
};

/*
 * sqe->flags
 */
/* use fixed fileset */
#define LKL_IOSQE_FIXED_FILE	(1U << LKL_IOSQE_FIXED_FILE_BIT)
/* issue after inflight IO */
#define LKL_IOSQE_IO_DRAIN		(1U << LKL_IOSQE_IO_DRAIN_BIT)
/* links next sqe */
#define LKL_IOSQE_IO_LINK		(1U << LKL_IOSQE_IO_LINK_BIT)
/* like LINK, but stronger */
#define LKL_IOSQE_IO_HARDLINK	(1U << LKL_IOSQE_IO_HARDLINK_BIT)
/* always go async */
#define LKL_IOSQE_ASYNC		(1U << LKL_IOSQE_ASYNC_BIT)
/* select buffer from sqe->buf_group */
#define LKL_IOSQE_BUFFER_SELECT	(1U << LKL_IOSQE_BUFFER_SELECT_BIT)
/* don't post CQE if request succeeded */
#define LKL_IOSQE_CQE_SKIP_SUCCESS	(1U << LKL_IOSQE_CQE_SKIP_SUCCESS_BIT)

/*
 * io_uring_setup() flags
 */
#define LKL_IORING_SETUP_IOPOLL	(1U << 0)	/* io_context is polled */
#define LKL_IORING_SETUP_SQPOLL	(1U << 1)	/* SQ poll thread */
#define LKL_IORING_SETUP_SQ_AFF	(1U << 2)	/* sq_thread_cpu is valid */
#define LKL_IORING_SETUP_CQSIZE	(1U << 3)	/* app defines CQ size */
#define LKL_IORING_SETUP_CLAMP	(1U << 4)	/* clamp SQ/CQ ring sizes */
#define LKL_IORING_SETUP_ATTACH_WQ	(1U << 5)	/* attach to existing wq */
#define LKL_IORING_SETUP_R_DISABLED	(1U << 6)	/* start with ring disabled */
#define LKL_IORING_SETUP_SUBMIT_ALL	(1U << 7)	/* continue submit on error */
/*
 * Cooperative task running. When requests complete, they often require
 * forcing the submitter to transition to the kernel to complete. If this
 * flag is set, work will be done when the task transitions anyway, rather
 * than force an inter-processor interrupt reschedule. This avoids interrupting
 * a task running in userspace, and saves an IPI.
 */
#define LKL_IORING_SETUP_COOP_TASKRUN	(1U << 8)
/*
 * If COOP_TASKRUN is set, get notified if task work is available for
 * running and a kernel transition would be needed to run it. This sets
 * LKL_IORING_SQ_TASKRUN in the sq ring flags. Not valid with COOP_TASKRUN.
 */
#define LKL_IORING_SETUP_TASKRUN_FLAG	(1U << 9)
#define LKL_IORING_SETUP_SQE128		(1U << 10) /* SQEs are 128 byte */
#define LKL_IORING_SETUP_CQE32		(1U << 11) /* CQEs are 32 byte */
/*
 * Only one task is allowed to submit requests
 */
#define LKL_IORING_SETUP_SINGLE_ISSUER	(1U << 12)

/*
 * Defer running task work to get events.
 * Rather than running bits of task work whenever the task transitions
 * try to do it just before it is needed.
 */
#define LKL_IORING_SETUP_DEFER_TASKRUN	(1U << 13)

enum lkl_io_uring_op {
	LKL_IORING_OP_NOP,
	LKL_IORING_OP_READV,
	LKL_IORING_OP_WRITEV,
	LKL_IORING_OP_FSYNC,
	LKL_IORING_OP_READ_FIXED,
	LKL_IORING_OP_WRITE_FIXED,
	LKL_IORING_OP_POLL_ADD,
	LKL_IORING_OP_POLL_REMOVE,
	LKL_IORING_OP_SYNC_FILE_RANGE,
	LKL_IORING_OP_SENDMSG,
	LKL_IORING_OP_RECVMSG,
	LKL_IORING_OP_TIMEOUT,
	LKL_IORING_OP_TIMEOUT_REMOVE,
	LKL_IORING_OP_ACCEPT,
	LKL_IORING_OP_ASYNC_CANCEL,
	LKL_IORING_OP_LINK_TIMEOUT,
	LKL_IORING_OP_CONNECT,
	LKL_IORING_OP_FALLOCATE,
	LKL_IORING_OP_OPENAT,
	LKL_IORING_OP_CLOSE,
	LKL_IORING_OP_FILES_UPDATE,
	LKL_IORING_OP_STATX,
	LKL_IORING_OP_READ,
	LKL_IORING_OP_WRITE,
	LKL_IORING_OP_FADVISE,
	LKL_IORING_OP_MADVISE,
	LKL_IORING_OP_SEND,
	LKL_IORING_OP_RECV,
	LKL_IORING_OP_OPENAT2,
	LKL_IORING_OP_EPOLL_CTL,
	LKL_IORING_OP_SPLICE,
	LKL_IORING_OP_PROVIDE_BUFFERS,
	LKL_IORING_OP_REMOVE_BUFFERS,
	LKL_IORING_OP_TEE,
	LKL_IORING_OP_SHUTDOWN,
	LKL_IORING_OP_RENAMEAT,
	LKL_IORING_OP_UNLINKAT,
	LKL_IORING_OP_MKDIRAT,
	LKL_IORING_OP_SYMLINKAT,
	LKL_IORING_OP_LINKAT,
	LKL_IORING_OP_MSG_RING,
	LKL_IORING_OP_FSETXATTR,
	LKL_IORING_OP_SETXATTR,
	LKL_IORING_OP_FGETXATTR,
	LKL_IORING_OP_GETXATTR,
	LKL_IORING_OP_SOCKET,
	LKL_IORING_OP_URING_CMD,
	LKL_IORING_OP_SEND_ZC,
	LKL_IORING_OP_SENDMSG_ZC,

	/* this goes last, obviously */
	LKL_IORING_OP_LAST,
};

/*
 * sqe->uring_cmd_flags
 * LKL_IORING_URING_CMD_FIXED	use registered buffer; pass this flag
 *				along with setting sqe->buf_index.
 */
#define LKL_IORING_URING_CMD_FIXED	(1U << 0)


/*
 * sqe->fsync_flags
 */
#define LKL_IORING_FSYNC_DATASYNC	(1U << 0)

/*
 * sqe->timeout_flags
 */
#define LKL_IORING_TIMEOUT_ABS		(1U << 0)
#define LKL_IORING_TIMEOUT_UPDATE		(1U << 1)
#define LKL_IORING_TIMEOUT_BOOTTIME		(1U << 2)
#define LKL_IORING_TIMEOUT_REALTIME		(1U << 3)
#define LKL_IORING_LINK_TIMEOUT_UPDATE	(1U << 4)
#define LKL_IORING_TIMEOUT_ETIME_SUCCESS	(1U << 5)
#define LKL_IORING_TIMEOUT_CLOCK_MASK	(LKL_IORING_TIMEOUT_BOOTTIME | LKL_IORING_TIMEOUT_REALTIME)
#define LKL_IORING_TIMEOUT_UPDATE_MASK	(LKL_IORING_TIMEOUT_UPDATE | LKL_IORING_LINK_TIMEOUT_UPDATE)
/*
 * sqe->splice_flags
 * extends splice(2) flags
 */
#define LKL_SPLICE_F_FD_IN_FIXED	(1U << 31) /* the last bit of __lkl__u32 */

/*
 * POLL_ADD flags. Note that since sqe->poll_events is the flag space, the
 * command flags for POLL_ADD are stored in sqe->len.
 *
 * LKL_IORING_POLL_ADD_MULTI	Multishot poll. Sets LKL_IORING_CQE_F_MORE if
 *				the poll handler will continue to report
 *				CQEs on behalf of the same SQE.
 *
 * IORING_POLL_UPDATE		Update existing poll request, matching
 *				sqe->addr as the old user_data field.
 *
 * IORING_POLL_LEVEL		Level triggered poll.
 */
#define LKL_IORING_POLL_ADD_MULTI	(1U << 0)
#define LKL_IORING_POLL_UPDATE_EVENTS	(1U << 1)
#define LKL_IORING_POLL_UPDATE_USER_DATA	(1U << 2)
#define LKL_IORING_POLL_ADD_LEVEL		(1U << 3)

/*
 * ASYNC_CANCEL flags.
 *
 * LKL_IORING_ASYNC_CANCEL_ALL	Cancel all requests that match the given key
 * LKL_IORING_ASYNC_CANCEL_FD	Key off 'fd' for cancelation rather than the
 *				request 'user_data'
 * LKL_IORING_ASYNC_CANCEL_ANY	Match any request
 * LKL_IORING_ASYNC_CANCEL_FD_FIXED	'fd' passed in is a fixed descriptor
 */
#define LKL_IORING_ASYNC_CANCEL_ALL	(1U << 0)
#define LKL_IORING_ASYNC_CANCEL_FD	(1U << 1)
#define LKL_IORING_ASYNC_CANCEL_ANY	(1U << 2)
#define LKL_IORING_ASYNC_CANCEL_FD_FIXED	(1U << 3)

/*
 * send/sendmsg and recv/recvmsg flags (sqe->ioprio)
 *
 * LKL_IORING_RECVSEND_POLL_FIRST	If set, instead of first attempting to send
 *				or receive and arm poll if that yields an
 *				-LKL_EAGAIN result, arm poll upfront and skip
 *				the initial transfer attempt.
 *
 * LKL_IORING_RECV_MULTISHOT	Multishot recv. Sets LKL_IORING_CQE_F_MORE if
 *				the handler will continue to report
 *				CQEs on behalf of the same SQE.
 *
 * LKL_IORING_RECVSEND_FIXED_BUF	Use registered buffers, the index is stored in
 *				the buf_index field.
 */
#define LKL_IORING_RECVSEND_POLL_FIRST	(1U << 0)
#define LKL_IORING_RECV_MULTISHOT		(1U << 1)
#define LKL_IORING_RECVSEND_FIXED_BUF	(1U << 2)

/*
 * accept flags stored in sqe->ioprio
 */
#define LKL_IORING_ACCEPT_MULTISHOT	(1U << 0)

/*
 * LKL_IORING_OP_MSG_RING command types, stored in sqe->addr
 */
enum {
	LKL_IORING_MSG_DATA,	/* pass sqe->len as 'res' and off as user_data */
	LKL_IORING_MSG_SEND_FD,	/* send a registered fd to another ring */
};

/*
 * LKL_IORING_OP_MSG_RING flags (sqe->msg_ring_flags)
 *
 * LKL_IORING_MSG_RING_CQE_SKIP	Don't post a CQE to the target ring. Not
 *				applicable for LKL_IORING_MSG_DATA, obviously.
 */
#define LKL_IORING_MSG_RING_CQE_SKIP	(1U << 0)

/*
 * IO completion data structure (Completion Queue Entry)
 */
struct lkl_io_uring_cqe {
	__lkl__u64	user_data;	/* sqe->data submission passed back */
	__lkl__s32	res;		/* result code for this event */
	__lkl__u32	flags;

	/*
	 * If the ring is initialized with LKL_IORING_SETUP_CQE32, then this field
	 * contains 16-bytes of padding, doubling the size of the CQE.
	 */
	__lkl__u64 big_cqe[];
};

/*
 * cqe->flags
 *
 * LKL_IORING_CQE_F_BUFFER	If set, the upper 16 bits are the buffer ID
 * LKL_IORING_CQE_F_MORE	If set, parent SQE will generate more CQE entries
 * LKL_IORING_CQE_F_SOCK_NONEMPTY	If set, more data to read after socket recv
 * LKL_IORING_CQE_F_NOTIF	Set for notification CQEs. Can be used to distinct
 * 			them from sends.
 */
#define LKL_IORING_CQE_F_BUFFER		(1U << 0)
#define LKL_IORING_CQE_F_MORE		(1U << 1)
#define LKL_IORING_CQE_F_SOCK_NONEMPTY	(1U << 2)
#define LKL_IORING_CQE_F_NOTIF		(1U << 3)

enum {
	LKL_IORING_CQE_BUFFER_SHIFT		= 16,
};

/*
 * Magic offsets for the application to mmap the data it needs
 */
#define LKL_IORING_OFF_SQ_RING		0ULL
#define LKL_IORING_OFF_CQ_RING		0x8000000ULL
#define LKL_IORING_OFF_SQES			0x10000000ULL

/*
 * Filled with the offset for mmap(2)
 */
struct lkl_io_sqring_offsets {
	__lkl__u32 head;
	__lkl__u32 tail;
	__lkl__u32 ring_mask;
	__lkl__u32 ring_entries;
	__lkl__u32 flags;
	__lkl__u32 dropped;
	__lkl__u32 array;
	__lkl__u32 resv1;
	__lkl__u64 resv2;
};

/*
 * sq_ring->flags
 */
#define LKL_IORING_SQ_NEED_WAKEUP	(1U << 0) /* needs io_uring_enter wakeup */
#define LKL_IORING_SQ_CQ_OVERFLOW	(1U << 1) /* CQ ring is overflown */
#define LKL_IORING_SQ_TASKRUN	(1U << 2) /* task should enter the kernel */

struct lkl_io_cqring_offsets {
	__lkl__u32 head;
	__lkl__u32 tail;
	__lkl__u32 ring_mask;
	__lkl__u32 ring_entries;
	__lkl__u32 overflow;
	__lkl__u32 cqes;
	__lkl__u32 flags;
	__lkl__u32 resv1;
	__lkl__u64 resv2;
};

/*
 * cq_ring->flags
 */

/* disable eventfd notifications */
#define LKL_IORING_CQ_EVENTFD_DISABLED	(1U << 0)

/*
 * io_uring_enter(2) flags
 */
#define LKL_IORING_ENTER_GETEVENTS		(1U << 0)
#define LKL_IORING_ENTER_SQ_WAKEUP		(1U << 1)
#define LKL_IORING_ENTER_SQ_WAIT		(1U << 2)
#define LKL_IORING_ENTER_EXT_ARG		(1U << 3)
#define LKL_IORING_ENTER_REGISTERED_RING	(1U << 4)

/*
 * Passed in for io_uring_setup(2). Copied back with updated info on success
 */
struct lkl_io_uring_params {
	__lkl__u32 sq_entries;
	__lkl__u32 cq_entries;
	__lkl__u32 flags;
	__lkl__u32 sq_thread_cpu;
	__lkl__u32 sq_thread_idle;
	__lkl__u32 features;
	__lkl__u32 wq_fd;
	__lkl__u32 resv[3];
	struct lkl_io_sqring_offsets sq_off;
	struct lkl_io_cqring_offsets cq_off;
};

/*
 * io_uring_params->features flags
 */
#define LKL_IORING_FEAT_SINGLE_MMAP		(1U << 0)
#define LKL_IORING_FEAT_NODROP		(1U << 1)
#define LKL_IORING_FEAT_SUBMIT_STABLE	(1U << 2)
#define LKL_IORING_FEAT_RW_CUR_POS		(1U << 3)
#define LKL_IORING_FEAT_CUR_PERSONALITY	(1U << 4)
#define LKL_IORING_FEAT_FAST_POLL		(1U << 5)
#define LKL_IORING_FEAT_POLL_32BITS 	(1U << 6)
#define LKL_IORING_FEAT_SQPOLL_NONFIXED	(1U << 7)
#define LKL_IORING_FEAT_EXT_ARG		(1U << 8)
#define LKL_IORING_FEAT_NATIVE_WORKERS	(1U << 9)
#define LKL_IORING_FEAT_RSRC_TAGS		(1U << 10)
#define LKL_IORING_FEAT_CQE_SKIP		(1U << 11)
#define LKL_IORING_FEAT_LINKED_FILE		(1U << 12)

/*
 * io_uring_register(2) opcodes and arguments
 */
enum {
	LKL_IORING_REGISTER_BUFFERS			= 0,
	LKL_IORING_UNREGISTER_BUFFERS		= 1,
	LKL_IORING_REGISTER_FILES			= 2,
	LKL_IORING_UNREGISTER_FILES			= 3,
	LKL_IORING_REGISTER_EVENTFD			= 4,
	LKL_IORING_UNREGISTER_EVENTFD		= 5,
	LKL_IORING_REGISTER_FILES_UPDATE		= 6,
	LKL_IORING_REGISTER_EVENTFD_ASYNC		= 7,
	LKL_IORING_REGISTER_PROBE			= 8,
	LKL_IORING_REGISTER_PERSONALITY		= 9,
	LKL_IORING_UNREGISTER_PERSONALITY		= 10,
	LKL_IORING_REGISTER_RESTRICTIONS		= 11,
	LKL_IORING_REGISTER_ENABLE_RINGS		= 12,

	/* extended with tagging */
	LKL_IORING_REGISTER_FILES2			= 13,
	LKL_IORING_REGISTER_FILES_UPDATE2		= 14,
	LKL_IORING_REGISTER_BUFFERS2		= 15,
	LKL_IORING_REGISTER_BUFFERS_UPDATE		= 16,

	/* set/clear io-wq thread affinities */
	LKL_IORING_REGISTER_IOWQ_AFF		= 17,
	LKL_IORING_UNREGISTER_IOWQ_AFF		= 18,

	/* set/get max number of io-wq workers */
	LKL_IORING_REGISTER_IOWQ_MAX_WORKERS	= 19,

	/* register/unregister io_uring fd with the ring */
	LKL_IORING_REGISTER_RING_FDS		= 20,
	LKL_IORING_UNREGISTER_RING_FDS		= 21,

	/* register ring based provide buffer group */
	LKL_IORING_REGISTER_PBUF_RING		= 22,
	LKL_IORING_UNREGISTER_PBUF_RING		= 23,

	/* sync cancelation API */
	LKL_IORING_REGISTER_SYNC_CANCEL		= 24,

	/* register a range of fixed file slots for automatic slot allocation */
	LKL_IORING_REGISTER_FILE_ALLOC_RANGE	= 25,

	/* this goes last */
	LKL_IORING_REGISTER_LAST
};

/* io-wq worker categories */
enum {
	LKL_IO_WQ_BOUND,
	LKL_IO_WQ_UNBOUND,
};

/* deprecated, see struct lkl_io_uring_rsrc_update */
struct lkl_io_uring_files_update {
	__lkl__u32 offset;
	__lkl__u32 resv;
	__lkl__aligned_u64 /* __lkl__s32 * */ fds;
};

/*
 * Register a fully sparse file space, rather than pass in an array of all
 * -1 file descriptors.
 */
#define LKL_IORING_RSRC_REGISTER_SPARSE	(1U << 0)

struct lkl_io_uring_rsrc_register {
	__lkl__u32 nr;
	__lkl__u32 flags;
	__lkl__u64 resv2;
	__lkl__aligned_u64 data;
	__lkl__aligned_u64 tags;
};

struct lkl_io_uring_rsrc_update {
	__lkl__u32 offset;
	__lkl__u32 resv;
	__lkl__aligned_u64 data;
};

struct lkl_io_uring_rsrc_update2 {
	__lkl__u32 offset;
	__lkl__u32 resv;
	__lkl__aligned_u64 data;
	__lkl__aligned_u64 tags;
	__lkl__u32 nr;
	__lkl__u32 resv2;
};

struct lkl_io_uring_notification_slot {
	__lkl__u64 tag;
	__lkl__u64 resv[3];
};

struct lkl_io_uring_notification_register {
	__lkl__u32 nr_slots;
	__lkl__u32 resv;
	__lkl__u64 resv2;
	__lkl__u64 data;
	__lkl__u64 resv3;
};

/* Skip updating fd indexes set to this value in the fd table */
#define LKL_IORING_REGISTER_FILES_SKIP	(-2)

#define LKL_IO_URING_OP_SUPPORTED	(1U << 0)

struct lkl_io_uring_probe_op {
	__lkl__u8 op;
	__lkl__u8 resv;
	__lkl__u16 flags;	/* IO_URING_OP_* flags */
	__lkl__u32 resv2;
};

struct lkl_io_uring_probe {
	__lkl__u8 last_op;	/* last opcode supported */
	__lkl__u8 ops_len;	/* length of ops[] array below */
	__lkl__u16 resv;
	__lkl__u32 resv2[3];
	struct lkl_io_uring_probe_op ops[];
};

struct lkl_io_uring_restriction {
	__lkl__u16 opcode;
	union {
		__lkl__u8 register_op; /* LKL_IORING_RESTRICTION_REGISTER_OP */
		__lkl__u8 sqe_op;      /* LKL_IORING_RESTRICTION_SQE_OP */
		__lkl__u8 sqe_flags;   /* IORING_RESTRICTION_SQE_FLAGS_* */
	};
	__lkl__u8 resv;
	__lkl__u32 resv2[3];
};

struct lkl_io_uring_buf {
	__lkl__u64	addr;
	__lkl__u32	len;
	__lkl__u16	bid;
	__lkl__u16	resv;
};

struct lkl_io_uring_buf_ring {
	union {
		/*
		 * To avoid spilling into more pages than we need to, the
		 * ring tail is overlaid with the io_uring_buf->resv field.
		 */
		struct {
			__lkl__u64	resv1;
			__lkl__u32	resv2;
			__lkl__u16	resv3;
			__lkl__u16	tail;
		};
		struct lkl_io_uring_buf	bufs[0];
	};
};

/* argument for IORING_(UN)REGISTER_PBUF_RING */
struct lkl_io_uring_buf_reg {
	__lkl__u64	ring_addr;
	__lkl__u32	ring_entries;
	__lkl__u16	bgid;
	__lkl__u16	pad;
	__lkl__u64	resv[3];
};

/*
 * io_uring_restriction->opcode values
 */
enum {
	/* Allow an io_uring_register(2) opcode */
	LKL_IORING_RESTRICTION_REGISTER_OP		= 0,

	/* Allow an sqe opcode */
	LKL_IORING_RESTRICTION_SQE_OP		= 1,

	/* Allow sqe flags */
	LKL_IORING_RESTRICTION_SQE_FLAGS_ALLOWED	= 2,

	/* Require sqe flags (these flags must be set on each submission) */
	LKL_IORING_RESTRICTION_SQE_FLAGS_REQUIRED	= 3,

	LKL_IORING_RESTRICTION_LAST
};

struct lkl_io_uring_getevents_arg {
	__lkl__u64	sigmask;
	__lkl__u32	sigmask_sz;
	__lkl__u32	pad;
	__lkl__u64	ts;
};

/*
 * Argument for LKL_IORING_REGISTER_SYNC_CANCEL
 */
struct lkl_io_uring_sync_cancel_reg {
	__lkl__u64				addr;
	__lkl__s32				fd;
	__lkl__u32				flags;
	struct __lkl__kernel_timespec	timeout;
	__lkl__u64				pad[4];
};

/*
 * Argument for LKL_IORING_REGISTER_FILE_ALLOC_RANGE
 * The range is specified as [off, off + len)
 */
struct lkl_io_uring_file_index_range {
	__lkl__u32	off;
	__lkl__u32	len;
	__lkl__u64	resv;
};

struct lkl_io_uring_recvmsg_out {
	__lkl__u32 namelen;
	__lkl__u32 controllen;
	__lkl__u32 payloadlen;
	__lkl__u32 flags;
};

#ifdef __cplusplus
}
#endif

#endif
