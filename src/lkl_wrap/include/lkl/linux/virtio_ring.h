#ifndef _LKL_LINUX_VIRTIO_RING_H
#define _LKL_LINUX_VIRTIO_RING_H
/* An interface for efficient virtio implementation, currently for use by KVM,
 * but hopefully others soon.  Do NOT change this since it will
 * break existing servers and clients.
 *
 * This header is BSD licensed so anyone can use the definitions to implement
 * compatible drivers/servers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Copyright Rusty Russell IBM Corporation 2007. */
#include <stdint.h>
#include <lkl/linux/types.h>
#include <lkl/linux/virtio_types.h>

/* This marks a buffer as continuing via the next field. */
#define LKL_VRING_DESC_F_NEXT	1
/* This marks a buffer as write-only (otherwise read-only). */
#define LKL_VRING_DESC_F_WRITE	2
/* This means the buffer contains a list of buffer descriptors. */
#define LKL_VRING_DESC_F_INDIRECT	4

/* The Host uses this in used->flags to advise the Guest: don't kick me when
 * you add a buffer.  It's unreliable, so it's simply an optimization.  Guest
 * will still kick if it's out of buffers. */
#define LKL_VRING_USED_F_NO_NOTIFY	1
/* The Guest uses this in avail->flags to advise the Host: don't interrupt me
 * when you consume a buffer.  It's unreliable, so it's simply an
 * optimization.  */
#define LKL_VRING_AVAIL_F_NO_INTERRUPT	1

/* We support indirect buffer descriptors */
#define LKL_VIRTIO_RING_F_INDIRECT_DESC	28

/* The Guest publishes the used index for which it expects an interrupt
 * at the end of the avail ring. Host should ignore the avail->flags field. */
/* The Host publishes the avail index for which it expects a kick
 * at the end of the used ring. Guest should ignore the used->flags field. */
#define LKL_VIRTIO_RING_F_EVENT_IDX		29

/* Virtio ring descriptors: 16 bytes.  These can chain together via "next". */
struct lkl_vring_desc {
	/* Address (guest-physical). */
	__lkl__virtio64 addr;
	/* Length. */
	__lkl__virtio32 len;
	/* The flags as indicated above. */
	__lkl__virtio16 flags;
	/* We chain unused descriptors via this, too */
	__lkl__virtio16 next;
};

struct lkl_vring_avail {
	__lkl__virtio16 flags;
	__lkl__virtio16 idx;
	__lkl__virtio16 ring[];
};

/* lkl_u32 is used here for ids for padding reasons. */
struct lkl_vring_used_elem {
	/* Index of start of used descriptor chain. */
	__lkl__virtio32 id;
	/* Total length of the descriptor chain which was used (written to) */
	__lkl__virtio32 len;
};

struct lkl_vring_used {
	__lkl__virtio16 flags;
	__lkl__virtio16 idx;
	struct lkl_vring_used_elem ring[];
};

struct lkl_vring {
	unsigned int num;

	struct lkl_vring_desc *desc;

	struct lkl_vring_avail *avail;

	struct lkl_vring_used *used;
};

/* Alignment requirements for vring elements.
 * When using pre-virtio 1.0 layout, these fall out naturally.
 */
#define LKL_VRING_AVAIL_ALIGN_SIZE 2
#define LKL_VRING_USED_ALIGN_SIZE 4
#define LKL_VRING_DESC_ALIGN_SIZE 16

/* The standard layout for the ring is a continuous chunk of memory which looks
 * like this.  We assume num is a power of 2.
 *
 * struct lkl_vring
 * {
 *	// The actual descriptors (16 bytes each)
 *	struct lkl_vring_desc desc[num];
 *
 *	// A ring of available descriptor heads with free-running index.
 *	__lkl__virtio16 avail_flags;
 *	__lkl__virtio16 avail_idx;
 *	__lkl__virtio16 available[num];
 *	__lkl__virtio16 used_event_idx;
 *
 *	// Padding to the next align boundary.
 *	char pad[];
 *
 *	// A ring of used descriptor heads with free-running index.
 *	__lkl__virtio16 used_flags;
 *	__lkl__virtio16 used_idx;
 *	struct lkl_vring_used_elem used[num];
 *	__lkl__virtio16 avail_event_idx;
 * };
 */
/* We publish the used event index at the end of the available ring, and vice
 * versa. They are at the end for backwards compatibility. */
#define lkl_vring_used_event(vr) ((vr)->avail->ring[(vr)->num])
#define lkl_vring_avail_event(vr) (*(__lkl__virtio16 *)&(vr)->used->ring[(vr)->num])

static __inline__ void vring_init(struct lkl_vring *vr, unsigned int num, void *p,
			      unsigned long align)
{
	vr->num = num;
	vr->desc = p;
	vr->avail = p + num*sizeof(struct lkl_vring_desc);
	vr->used = (void *)(((lkl_uintptr_t)&vr->avail->ring[num] + sizeof(__lkl__virtio16)
		+ align-1) & ~(align - 1));
}

static __inline__ unsigned lkl_vring_size(unsigned int num, unsigned long align)
{
	return ((sizeof(struct lkl_vring_desc) * num + sizeof(__lkl__virtio16) * (3 + num)
		 + align - 1) & ~(align - 1))
		+ sizeof(__lkl__virtio16) * 3 + sizeof(struct lkl_vring_used_elem) * num;
}

/* The following is used with USED_EVENT_IDX and AVAIL_EVENT_IDX */
/* Assuming a given event_idx value from the other side, if
 * we have just incremented index from old to new_idx,
 * should we trigger an event? */
static __inline__ int lkl_vring_need_event(__lkl__u16 event_idx, __lkl__u16 new_idx, __lkl__u16 old)
{
	/* Note: Xen has similar logic for notification hold-off
	 * in include/xen/interface/io/ring.h with req_event and req_prod
	 * corresponding to event_idx + 1 and new_idx respectively.
	 * Note also that req_event and req_prod in Xen start at 1,
	 * event indexes in virtio start at 0. */
	return (__lkl__u16)(new_idx - event_idx - 1) < (__lkl__u16)(new_idx - old);
}

#endif /* _LKL_LINUX_VIRTIO_RING_H */
