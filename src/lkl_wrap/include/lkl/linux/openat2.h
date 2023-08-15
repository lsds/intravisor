/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_OPENAT2_H
#define _LKL_LINUX_OPENAT2_H

#include <lkl/linux/types.h>

/*
 * Arguments for how openat2(2) should open the target path. If only @flags and
 * @mode are non-zero, then openat2(2) operates very similarly to openat(2).
 *
 * However, unlike openat(2), unknown or invalid bits in @flags result in
 * -LKL_EINVAL rather than being silently ignored. @mode must be zero unless one of
 * {LKL_O_CREAT, LKL_O_TMPFILE} are set.
 *
 * @flags: O_* flags.
 * @mode: LKL_O_CREAT/LKL_O_TMPFILE file mode.
 * @resolve: RESOLVE_* flags.
 */
struct lkl_open_how {
	__lkl__u64 flags;
	__lkl__u64 mode;
	__lkl__u64 resolve;
};

/* how->resolve flags for openat2(2). */
#define LKL_RESOLVE_NO_XDEV		0x01 /* Block mount-point crossings
					(includes bind-mounts). */
#define LKL_RESOLVE_NO_MAGICLINKS	0x02 /* Block traversal through procfs-style
					"magic-links". */
#define LKL_RESOLVE_NO_SYMLINKS	0x04 /* Block traversal through all symlinks
					(implies OEXT_NO_MAGICLINKS) */
#define LKL_RESOLVE_BENEATH		0x08 /* Block "lexical" trickery like
					"..", symlinks, and absolute
					paths which escape the dirfd. */
#define LKL_RESOLVE_IN_ROOT		0x10 /* Make all jumps to "/" and ".."
					be scoped inside the dirfd
					(similar to chroot(2)). */
#define LKL_RESOLVE_CACHED		0x20 /* Only complete if resolution can be
					completed through cached lookup. May
					return -LKL_EAGAIN if that's not
					possible. */

#endif /* _LKL_LINUX_OPENAT2_H */
