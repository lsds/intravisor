/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_STAT_H
#define _LKL_LINUX_STAT_H

#include <lkl/linux/types.h>

#if defined(__LKL__KERNEL__) || !defined(__GLIBC__) || (__GLIBC__ < 2)

#define LKL_S_IFMT  00170000
#define LKL_S_IFSOCK 0140000
#define LKL_S_IFLNK	 0120000
#define LKL_S_IFREG  0100000
#define LKL_S_IFBLK  0060000
#define LKL_S_IFDIR  0040000
#define LKL_S_IFCHR  0020000
#define LKL_S_IFIFO  0010000
#define LKL_S_ISUID  0004000
#define LKL_S_ISGID  0002000
#define LKL_S_ISVTX  0001000

#define LKL_S_ISLNK(m)	(((m) & LKL_S_IFMT) == LKL_S_IFLNK)
#define LKL_S_ISREG(m)	(((m) & LKL_S_IFMT) == LKL_S_IFREG)
#define LKL_S_ISDIR(m)	(((m) & LKL_S_IFMT) == LKL_S_IFDIR)
#define LKL_S_ISCHR(m)	(((m) & LKL_S_IFMT) == LKL_S_IFCHR)
#define LKL_S_ISBLK(m)	(((m) & LKL_S_IFMT) == LKL_S_IFBLK)
#define LKL_S_ISFIFO(m)	(((m) & LKL_S_IFMT) == LKL_S_IFIFO)
#define LKL_S_ISSOCK(m)	(((m) & LKL_S_IFMT) == LKL_S_IFSOCK)

#define LKL_S_IRWXU 00700
#define LKL_S_IRUSR 00400
#define LKL_S_IWUSR 00200
#define LKL_S_IXUSR 00100

#define LKL_S_IRWXG 00070
#define LKL_S_IRGRP 00040
#define LKL_S_IWGRP 00020
#define LKL_S_IXGRP 00010

#define LKL_S_IRWXO 00007
#define LKL_S_IROTH 00004
#define LKL_S_IWOTH 00002
#define LKL_S_IXOTH 00001

#endif

/*
 * Timestamp structure for the timestamps in struct lkl_statx.
 *
 * tv_sec holds the number of seconds before (negative) or after (positive)
 * 00:00:00 1st January 1970 UTC.
 *
 * tv_nsec holds a number of nanoseconds (0..999,999,999) after the tv_sec time.
 *
 * __reserved is held in case we need a yet finer resolution.
 */
struct lkl_statx_timestamp {
	__lkl__s64	tv_sec;
	__lkl__u32	tv_nsec;
	__lkl__s32	__reserved;
};

/*
 * Structures for the extended file attribute retrieval system call
 * (statx()).
 *
 * The caller passes a mask of what they're specifically interested in as a
 * parameter to statx().  What statx() actually got will be indicated in
 * st_mask upon return.
 *
 * For each bit in the mask argument:
 *
 * - if the datum is not supported:
 *
 *   - the bit will be cleared, and
 *
 *   - the datum will be set to an appropriate fabricated value if one is
 *     available (eg. CIFS can take a default uid and gid), otherwise
 *
 *   - the field will be cleared;
 *
 * - otherwise, if explicitly requested:
 *
 *   - the datum will be synchronised to the server if LKL_AT_STATX_FORCE_SYNC is
 *     set or if the datum is considered out of date, and
 *
 *   - the field will be filled in and the bit will be set;
 *
 * - otherwise, if not requested, but available in approximate form without any
 *   effort, it will be filled in anyway, and the bit will be set upon return
 *   (it might not be up to date, however, and no attempt will be made to
 *   synchronise the internal state first);
 *
 * - otherwise the field and the bit will be cleared before returning.
 *
 * Items in LKL_STATX_BASIC_STATS may be marked unavailable on return, but they
 * will have values installed for compatibility purposes so that stat() and
 * co. can be emulated in userspace.
 */
struct lkl_statx {
	/* 0x00 */
	__lkl__u32	stx_mask;	/* What results were written [uncond] */
	__lkl__u32	stx_blksize;	/* Preferred general I/O size [uncond] */
	__lkl__u64	stx_attributes;	/* Flags conveying information about the file [uncond] */
	/* 0x10 */
	__lkl__u32	stx_nlink;	/* Number of hard links */
	__lkl__u32	stx_uid;	/* User ID of owner */
	__lkl__u32	stx_gid;	/* Group ID of owner */
	__lkl__u16	stx_mode;	/* File mode */
	__lkl__u16	__spare0[1];
	/* 0x20 */
	__lkl__u64	stx_ino;	/* Inode number */
	__lkl__u64	stx_size;	/* File size */
	__lkl__u64	stx_blocks;	/* Number of 512-byte blocks allocated */
	__lkl__u64	stx_attributes_mask; /* Mask to show what's supported in stx_attributes */
	/* 0x40 */
	struct lkl_statx_timestamp	stx_atime;	/* Last access time */
	struct lkl_statx_timestamp	stx_btime;	/* File creation time */
	struct lkl_statx_timestamp	stx_ctime;	/* Last attribute change time */
	struct lkl_statx_timestamp	stx_mtime;	/* Last data modification time */
	/* 0x80 */
	__lkl__u32	stx_rdev_major;	/* Device ID of special file [if bdev/cdev] */
	__lkl__u32	stx_rdev_minor;
	__lkl__u32	stx_dev_major;	/* ID of device containing file [uncond] */
	__lkl__u32	stx_dev_minor;
	/* 0x90 */
	__lkl__u64	__spare2[14];	/* Spare space for future expansion */
	/* 0x100 */
};

/*
 * Flags to be stx_mask
 *
 * Query request/result mask for statx() and struct lkl_statx::stx_mask.
 *
 * These bits should be set in the mask argument of statx() to request
 * particular items when calling statx().
 */
#define LKL_STATX_TYPE		0x00000001U	/* Want/got stx_mode & LKL_S_IFMT */
#define LKL_STATX_MODE		0x00000002U	/* Want/got stx_mode & ~LKL_S_IFMT */
#define LKL_STATX_NLINK		0x00000004U	/* Want/got stx_nlink */
#define LKL_STATX_UID		0x00000008U	/* Want/got stx_uid */
#define LKL_STATX_GID		0x00000010U	/* Want/got stx_gid */
#define LKL_STATX_ATIME		0x00000020U	/* Want/got stx_atime */
#define LKL_STATX_MTIME		0x00000040U	/* Want/got stx_mtime */
#define LKL_STATX_CTIME		0x00000080U	/* Want/got stx_ctime */
#define LKL_STATX_INO		0x00000100U	/* Want/got stx_ino */
#define LKL_STATX_SIZE		0x00000200U	/* Want/got stx_size */
#define LKL_STATX_BLOCKS		0x00000400U	/* Want/got stx_blocks */
#define LKL_STATX_BASIC_STATS	0x000007ffU	/* The stuff in the normal stat struct */
#define LKL_STATX_BTIME		0x00000800U	/* Want/got stx_btime */
#define LKL_STATX_ALL		0x00000fffU	/* All currently supported flags */
#define LKL_STATX__RESERVED		0x80000000U	/* Reserved for future struct lkl_statx expansion */

/*
 * Attributes to be found in stx_attributes and masked in stx_attributes_mask.
 *
 * These give information about the features or the state of a file that might
 * be of use to ordinary userspace programs such as GUIs or ls rather than
 * specialised tools.
 *
 * Note that the flags marked [I] correspond to generic FS_IOC_FLAGS
 * semantically.  Where possible, the numerical value is picked to correspond
 * also.
 */
#define LKL_STATX_ATTR_COMPRESSED		0x00000004 /* [I] File is compressed by the fs */
#define LKL_STATX_ATTR_IMMUTABLE		0x00000010 /* [I] File is marked immutable */
#define LKL_STATX_ATTR_APPEND		0x00000020 /* [I] File is append-only */
#define LKL_STATX_ATTR_NODUMP		0x00000040 /* [I] File is not to be dumped */
#define LKL_STATX_ATTR_ENCRYPTED		0x00000800 /* [I] File requires key to decrypt in fs */

#define LKL_STATX_ATTR_AUTOMOUNT		0x00001000 /* Dir: Automount trigger */


#endif /* _LKL_LINUX_STAT_H */
