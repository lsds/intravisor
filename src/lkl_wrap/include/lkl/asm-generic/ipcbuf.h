/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_IPCBUF_H
#define __LKL__ASM_GENERIC_IPCBUF_H

/*
 * The generic ipc64_perm structure:
 * Note extra padding because this structure is passed back and forth
 * between kernel and user space.
 *
 * ipc64_perm was originally meant to be architecture specific, but
 * everyone just ended up making identical copies without specific
 * optimizations, so we may just as well all use the same one.
 *
 * Pad space is left for:
 * - 32-bit lkl_mode_t on architectures that only had 16 bit
 * - 32-bit seq
 * - 2 miscellaneous 32-bit values
 */

struct lkl_ipc64_perm {
	__lkl__kernel_key_t		key;
	__lkl__kernel_uid32_t	uid;
	__lkl__kernel_gid32_t	gid;
	__lkl__kernel_uid32_t	cuid;
	__lkl__kernel_gid32_t	cgid;
	__lkl__kernel_mode_t		mode;
				/* pad if lkl_mode_t is u16: */
	unsigned char		__pad1[4 - sizeof(__lkl__kernel_mode_t)];
	unsigned short		seq;
	unsigned short		__pad2;
	__lkl__kernel_ulong_t	__unused1;
	__lkl__kernel_ulong_t	__unused2;
};

#endif /* __LKL__ASM_GENERIC_IPCBUF_H */
