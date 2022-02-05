/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_FCNTL_H
#define _LKL_ASM_GENERIC_FCNTL_H

#include <lkl/linux/types.h>

/*
 * FMODE_EXEC is 0x20
 * FMODE_NONOTIFY is 0x4000000
 * These cannot be used by userspace O_* until internal and external open
 * flags are split.
 * -Eric Paris
 */

/*
 * When introducing new O_* bits, please check its uniqueness in fcntl_init().
 */

#define LKL_O_ACCMODE	00000003
#define LKL_O_RDONLY	00000000
#define LKL_O_WRONLY	00000001
#define LKL_O_RDWR		00000002
#ifndef LKL_O_CREAT
#define LKL_O_CREAT		00000100	/* not fcntl */
#endif
#ifndef LKL_O_EXCL
#define LKL_O_EXCL		00000200	/* not fcntl */
#endif
#ifndef LKL_O_NOCTTY
#define LKL_O_NOCTTY	00000400	/* not fcntl */
#endif
#ifndef LKL_O_TRUNC
#define LKL_O_TRUNC		00001000	/* not fcntl */
#endif
#ifndef LKL_O_APPEND
#define LKL_O_APPEND	00002000
#endif
#ifndef LKL_O_NONBLOCK
#define LKL_O_NONBLOCK	00004000
#endif
#ifndef LKL_O_DSYNC
#define LKL_O_DSYNC		00010000	/* used to be LKL_O_SYNC, see below */
#endif
#ifndef LKL_FASYNC
#define LKL_FASYNC		00020000	/* fcntl, for BSD compatibility */
#endif
#ifndef LKL_O_DIRECT
#define LKL_O_DIRECT	00040000	/* direct disk access hint */
#endif
#ifndef LKL_O_LARGEFILE
#define LKL_O_LARGEFILE	00100000
#endif
#ifndef LKL_O_DIRECTORY
#define LKL_O_DIRECTORY	00200000	/* must be a directory */
#endif
#ifndef LKL_O_NOFOLLOW
#define LKL_O_NOFOLLOW	00400000	/* don't follow links */
#endif
#ifndef LKL_O_NOATIME
#define LKL_O_NOATIME	01000000
#endif
#ifndef LKL_O_CLOEXEC
#define LKL_O_CLOEXEC	02000000	/* set close_on_exec */
#endif

/*
 * Before Linux 2.6.33 only LKL_O_DSYNC semantics were implemented, but using
 * the LKL_O_SYNC flag.  We continue to use the existing numerical value
 * for LKL_O_DSYNC semantics now, but using the correct symbolic name for it.
 * This new value is used to request true Posix LKL_O_SYNC semantics.  It is
 * defined in this strange way to make sure applications compiled against
 * new headers get at least LKL_O_DSYNC semantics on older kernels.
 *
 * This has the nice side-effect that we can simply test for LKL_O_DSYNC
 * wherever we do not care if LKL_O_DSYNC or LKL_O_SYNC is used.
 *
 * Note: __LKL__O_SYNC must never be used directly.
 */
#ifndef LKL_O_SYNC
#define __LKL__O_SYNC	04000000
#define LKL_O_SYNC		(__LKL__O_SYNC|LKL_O_DSYNC)
#endif

#ifndef LKL_O_PATH
#define LKL_O_PATH		010000000
#endif

#ifndef __LKL__O_TMPFILE
#define __LKL__O_TMPFILE	020000000
#endif

/* a horrid kludge trying to make sure that this will fail on old kernels */
#define LKL_O_TMPFILE (__LKL__O_TMPFILE | LKL_O_DIRECTORY)
#define LKL_O_TMPFILE_MASK (__LKL__O_TMPFILE | LKL_O_DIRECTORY | LKL_O_CREAT)      

#ifndef LKL_O_NDELAY
#define LKL_O_NDELAY	LKL_O_NONBLOCK
#endif

#define LKL_F_DUPFD		0	/* dup */
#define LKL_F_GETFD		1	/* get close_on_exec */
#define LKL_F_SETFD		2	/* set/clear close_on_exec */
#define LKL_F_GETFL		3	/* get file->f_flags */
#define LKL_F_SETFL		4	/* set file->f_flags */
#ifndef LKL_F_GETLK
#define LKL_F_GETLK		5
#define LKL_F_SETLK		6
#define LKL_F_SETLKW	7
#endif
#ifndef LKL_F_SETOWN
#define LKL_F_SETOWN	8	/* for sockets. */
#define LKL_F_GETOWN	9	/* for sockets. */
#endif
#ifndef LKL_F_SETSIG
#define LKL_F_SETSIG	10	/* for sockets. */
#define LKL_F_GETSIG	11	/* for sockets. */
#endif

#ifndef LKL_CONFIG_64BIT
#ifndef LKL_F_GETLK64
#define LKL_F_GETLK64	12	/*  using 'struct lkl_flock64' */
#define LKL_F_SETLK64	13
#define LKL_F_SETLKW64	14
#endif
#endif

#ifndef LKL_F_SETOWN_EX
#define LKL_F_SETOWN_EX	15
#define LKL_F_GETOWN_EX	16
#endif

#ifndef LKL_F_GETOWNER_UIDS
#define LKL_F_GETOWNER_UIDS	17
#endif

/*
 * Open File Description Locks
 *
 * Usually record locks held by a process are released on *any* close and are
 * not inherited across a fork().
 *
 * These cmd values will set locks that conflict with process-associated
 * record  locks, but are "owned" by the open file description, not the
 * process. This means that they are inherited across fork() like BSD (flock)
 * locks, and they are only released automatically when the last reference to
 * the the open file against which they were acquired is put.
 */
#define LKL_F_OFD_GETLK	36
#define LKL_F_OFD_SETLK	37
#define LKL_F_OFD_SETLKW	38

#define LKL_F_OWNER_TID	0
#define LKL_F_OWNER_PID	1
#define LKL_F_OWNER_PGRP	2

struct lkl_f_owner_ex {
	int	type;
	__lkl__kernel_pid_t	pid;
};

/* for F_[GET|SET]FL */
#define LKL_FD_CLOEXEC	1	/* actually anything with low bit set goes */

/* for posix fcntl() and lockf() */
#ifndef LKL_F_RDLCK
#define LKL_F_RDLCK		0
#define LKL_F_WRLCK		1
#define LKL_F_UNLCK		2
#endif

/* for old implementation of bsd flock () */
#ifndef LKL_F_EXLCK
#define LKL_F_EXLCK		4	/* or 3 */
#define LKL_F_SHLCK		8	/* or 4 */
#endif

/* operations for bsd flock(), also used by the kernel implementation */
#define LKL_LOCK_SH		1	/* shared lock */
#define LKL_LOCK_EX		2	/* exclusive lock */
#define LKL_LOCK_NB		4	/* or'd with one of the above to prevent
				   blocking */
#define LKL_LOCK_UN		8	/* remove lock */

#define LKL_LOCK_MAND	32	/* This is a mandatory flock ... */
#define LKL_LOCK_READ	64	/* which allows concurrent read operations */
#define LKL_LOCK_WRITE	128	/* which allows concurrent write operations */
#define LKL_LOCK_RW		192	/* which allows concurrent read & write ops */

#define LKL_F_LINUX_SPECIFIC_BASE	1024

#ifndef HAVE_ARCH_STRUCT_FLOCK
#ifndef __LKL__ARCH_FLOCK_PAD
#define __LKL__ARCH_FLOCK_PAD
#endif

struct lkl_flock {
	short	l_type;
	short	l_whence;
	__lkl__kernel_off_t	l_start;
	__lkl__kernel_off_t	l_len;
	__lkl__kernel_pid_t	l_pid;
	__LKL__ARCH_FLOCK_PAD
};
#endif

#ifndef HAVE_ARCH_STRUCT_FLOCK64
#ifndef __LKL__ARCH_FLOCK64_PAD
#define __LKL__ARCH_FLOCK64_PAD
#endif

struct lkl_flock64 {
	short  l_type;
	short  l_whence;
	__lkl__kernel_loff_t l_start;
	__lkl__kernel_loff_t l_len;
	__lkl__kernel_pid_t  l_pid;
	__LKL__ARCH_FLOCK64_PAD
};
#endif

#endif /* _LKL_ASM_GENERIC_FCNTL_H */
