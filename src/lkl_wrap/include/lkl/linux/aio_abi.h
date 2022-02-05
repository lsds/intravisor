/* include/linux/aio_abi.h
 *
 * Copyright 2000,2001,2002 Red Hat.
 *
 * Written by Benjamin LaHaise <bcrl@kvack.org>
 *
 * Distribute under the terms of the GPLv2 (see ../../COPYING) or under 
 * the following terms.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, provided that the above copyright
 * notice appears in all copies.  This software is provided without any
 * warranty, express or implied.  Red Hat makes no representations about
 * the suitability of this software for any purpose.
 *
 * IN NO EVENT SHALL RED HAT BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
 * SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF
 * THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF RED HAT HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * RED HAT DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND
 * RED HAT HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.
 */
#ifndef __LKL__LINUX__AIO_ABI_H
#define __LKL__LINUX__AIO_ABI_H

#include <lkl/linux/types.h>
#include <lkl/linux/fs.h>
#include <lkl/asm/byteorder.h>

typedef __lkl__kernel_ulong_t lkl_aio_context_t;

enum {
	LKL_IOCB_CMD_PREAD = 0,
	LKL_IOCB_CMD_PWRITE = 1,
	LKL_IOCB_CMD_FSYNC = 2,
	LKL_IOCB_CMD_FDSYNC = 3,
	/* These two are experimental.
	 * IOCB_CMD_PREADX = 4,
	 * IOCB_CMD_POLL = 5,
	 */
	LKL_IOCB_CMD_NOOP = 6,
	LKL_IOCB_CMD_PREADV = 7,
	LKL_IOCB_CMD_PWRITEV = 8,
};

/*
 * Valid flags for the "aio_flags" member of the "struct lkl_iocb".
 *
 * LKL_IOCB_FLAG_RESFD - Set if the "aio_resfd" member of the "struct lkl_iocb"
 *                   is valid.
 */
#define LKL_IOCB_FLAG_RESFD		(1 << 0)

/* read() from /dev/aio returns these structures. */
struct lkl_io_event {
	__lkl__u64		data;		/* the data field from the iocb */
	__lkl__u64		obj;		/* what iocb this event came from */
	__lkl__s64		res;		/* result code for this event */
	__lkl__s64		res2;		/* secondary result */
};

/*
 * we always use a 64bit lkl_off_t when communicating
 * with userland.  its up to libraries to do the
 * proper padding and aio_error abstraction
 */

struct lkl_iocb {
	/* these are internal to the kernel/libc. */
	__lkl__u64	aio_data;	/* data to be returned in event's data */

#if defined(__BYTE_ORDER) ? __BYTE_ORDER == __LKL__LITTLE_ENDIAN : defined(__LKL__LITTLE_ENDIAN)
	__lkl__u32	aio_key;	/* the kernel sets aio_key to the req # */
	__lkl__kernel_rwf_t aio_rw_flags;	/* RWF_* flags */
#elif defined(__BYTE_ORDER) ? __BYTE_ORDER == __LKL__BIG_ENDIAN : defined(__LKL__BIG_ENDIAN)
	__lkl__kernel_rwf_t aio_rw_flags;	/* RWF_* flags */
	__lkl__u32	aio_key;	/* the kernel sets aio_key to the req # */
#else
#error edit for your odd byteorder.
#endif

	/* common fields */
	__lkl__u16	aio_lio_opcode;	/* see IOCB_CMD_ above */
	__lkl__s16	aio_reqprio;
	__lkl__u32	aio_fildes;

	__lkl__u64	aio_buf;
	__lkl__u64	aio_nbytes;
	__lkl__s64	aio_offset;

	/* extra parameters */
	__lkl__u64	aio_reserved2;	/* TODO: use this for a (struct lkl_sigevent *) */

	/* flags for the "struct lkl_iocb" */
	__lkl__u32	aio_flags;

	/*
	 * if the LKL_IOCB_FLAG_RESFD flag of "aio_flags" is set, this is an
	 * eventfd to signal AIO readiness to
	 */
	__lkl__u32	aio_resfd;
}; /* 64 bytes */

#undef IFBIG
#undef IFLITTLE

#endif /* __LKL__LINUX__AIO_ABI_H */

