/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_FS_H
#define _LKL_LINUX_FS_H

/*
 * This file has definitions for some important file table structures
 * and constants and structures used by various generic file system
 * ioctl's.  Please do not make any changes in this file before
 * sending patches for review to linux-fsdevel@vger.kernel.org and
 * linux-api@vger.kernel.org.
 */

#include <lkl/linux/limits.h>
#include <lkl/linux/ioctl.h>
#include <lkl/linux/types.h>
#include <lkl/linux/fscrypt.h>

/* Use of MS_* flags within the kernel is restricted to core mount(2) code. */
#include <lkl/linux/mount.h>

/*
 * It's silly to have LKL_NR_OPEN bigger than LKL_NR_FILE, but you can change
 * the file limit at runtime and only root can increase the per-process
 * nr_file rlimit, so it's safe to set up a ridiculously high absolute
 * upper limit on files-per-process.
 *
 * Some programs (notably those using select()) may have to be 
 * recompiled to take full advantage of the new limits..  
 */

/* Fixed constants first: */
#undef LKL_NR_OPEN
#define LKL_INR_OPEN_CUR 1024	/* Initial setting for nfile rlimits */
#define LKL_INR_OPEN_MAX 4096	/* Hard limit for nfile rlimits */

#define LKL_BLOCK_SIZE_BITS 10
#define LKL_BLOCK_SIZE (1<<LKL_BLOCK_SIZE_BITS)

#define LKL_SEEK_SET	0	/* seek relative to beginning of file */
#define LKL_SEEK_CUR	1	/* seek relative to current file position */
#define LKL_SEEK_END	2	/* seek relative to end of file */
#define LKL_SEEK_DATA	3	/* seek to the next data */
#define LKL_SEEK_HOLE	4	/* seek to the next hole */
#define LKL_SEEK_MAX	LKL_SEEK_HOLE

#define LKL_RENAME_NOREPLACE	(1 << 0)	/* Don't overwrite target */
#define LKL_RENAME_EXCHANGE		(1 << 1)	/* Exchange source and dest */
#define LKL_RENAME_WHITEOUT		(1 << 2)	/* Whiteout source */

struct lkl_file_clone_range {
	__lkl__s64 src_fd;
	__lkl__u64 src_offset;
	__lkl__u64 src_length;
	__lkl__u64 dest_offset;
};

struct lkl_fstrim_range {
	__lkl__u64 start;
	__lkl__u64 len;
	__lkl__u64 minlen;
};

/* extent-same (dedupe) ioctls; these MUST match the btrfs ioctl definitions */
#define LKL_FILE_DEDUPE_RANGE_SAME		0
#define LKL_FILE_DEDUPE_RANGE_DIFFERS	1

/* from struct btrfs_ioctl_file_extent_same_info */
struct lkl_file_dedupe_range_info {
	__lkl__s64 dest_fd;		/* in - destination file */
	__lkl__u64 dest_offset;	/* in - start of extent in destination */
	__lkl__u64 bytes_deduped;	/* out - total # of bytes we were able
				 * to dedupe from this file. */
	/* status of this dedupe operation:
	 * < 0 for error
	 * == LKL_FILE_DEDUPE_RANGE_SAME if dedupe succeeds
	 * == LKL_FILE_DEDUPE_RANGE_DIFFERS if data differs
	 */
	__lkl__s32 status;		/* out - see above description */
	__lkl__u32 reserved;		/* must be zero */
};

/* from struct btrfs_ioctl_file_extent_same_args */
struct lkl_file_dedupe_range {
	__lkl__u64 src_offset;	/* in - start of extent in source */
	__lkl__u64 src_length;	/* in - length of extent */
	__lkl__u16 dest_count;	/* in - total elements in info array */
	__lkl__u16 reserved1;	/* must be zero */
	__lkl__u32 reserved2;	/* must be zero */
	struct lkl_file_dedupe_range_info info[];
};

/* And dynamically-tunable limits and defaults: */
struct lkl_files_stat_struct {
	unsigned long nr_files;		/* read only */
	unsigned long nr_free_files;	/* read only */
	unsigned long max_files;		/* tunable */
};

struct lkl_inodes_stat_t {
	long nr_inodes;
	long nr_unused;
	long dummy[5];		/* padding for sysctl ABI compatibility */
};


#define LKL_NR_FILE  8192	/* this can well be larger on a larger system */

/*
 * Structure for LKL_FS_IOC_FSGETXATTR[A] and LKL_FS_IOC_FSSETXATTR.
 */
struct lkl_fsxattr {
	__lkl__u32		fsx_xflags;	/* xflags field value (get/set) */
	__lkl__u32		fsx_extsize;	/* extsize field value (get/set)*/
	__lkl__u32		fsx_nextents;	/* nextents field value (get)	*/
	__lkl__u32		fsx_projid;	/* project identifier (get/set) */
	__lkl__u32		fsx_cowextsize;	/* CoW extsize field value (get/set)*/
	unsigned char	fsx_pad[8];
};

/*
 * Flags for the fsx_xflags field
 */
#define LKL_FS_XFLAG_REALTIME	0x00000001	/* data in realtime volume */
#define LKL_FS_XFLAG_PREALLOC	0x00000002	/* preallocated file extents */
#define LKL_FS_XFLAG_IMMUTABLE	0x00000008	/* file cannot be modified */
#define LKL_FS_XFLAG_APPEND		0x00000010	/* all writes append */
#define LKL_FS_XFLAG_SYNC		0x00000020	/* all writes synchronous */
#define LKL_FS_XFLAG_NOATIME	0x00000040	/* do not update access time */
#define LKL_FS_XFLAG_NODUMP		0x00000080	/* do not include in backups */
#define LKL_FS_XFLAG_RTINHERIT	0x00000100	/* create with rt bit set */
#define LKL_FS_XFLAG_PROJINHERIT	0x00000200	/* create with parents projid */
#define LKL_FS_XFLAG_NOSYMLINKS	0x00000400	/* disallow symlink creation */
#define LKL_FS_XFLAG_EXTSIZE	0x00000800	/* extent size allocator hint */
#define LKL_FS_XFLAG_EXTSZINHERIT	0x00001000	/* inherit inode extent size */
#define LKL_FS_XFLAG_NODEFRAG	0x00002000	/* do not defragment */
#define LKL_FS_XFLAG_FILESTREAM	0x00004000	/* use filestream allocator */
#define LKL_FS_XFLAG_DAX		0x00008000	/* use DAX for IO */
#define LKL_FS_XFLAG_COWEXTSIZE	0x00010000	/* CoW extent size allocator hint */
#define LKL_FS_XFLAG_HASATTR	0x80000000	/* no DIFLAG for this	*/

/* the read-only stuff doesn't really belong here, but any other place is
   probably as bad and I don't want to create yet another include file. */

#define LKL_BLKROSET   _LKL_IO(0x12,93)	/* set device read-only (0 = read-write) */
#define LKL_BLKROGET   _LKL_IO(0x12,94)	/* get read-only status (0 = read_write) */
#define LKL_BLKRRPART  _LKL_IO(0x12,95)	/* re-read partition table */
#define LKL_BLKGETSIZE _LKL_IO(0x12,96)	/* return device size /512 (long *arg) */
#define LKL_BLKFLSBUF  _LKL_IO(0x12,97)	/* flush buffer cache */
#define LKL_BLKRASET   _LKL_IO(0x12,98)	/* set read ahead for block device */
#define LKL_BLKRAGET   _LKL_IO(0x12,99)	/* get current read ahead setting */
#define LKL_BLKFRASET  _LKL_IO(0x12,100)/* set filesystem (mm/filemap.c) read-ahead */
#define LKL_BLKFRAGET  _LKL_IO(0x12,101)/* get filesystem (mm/filemap.c) read-ahead */
#define LKL_BLKSECTSET _LKL_IO(0x12,102)/* set max sectors per request (ll_rw_blk.c) */
#define LKL_BLKSECTGET _LKL_IO(0x12,103)/* get max sectors per request (ll_rw_blk.c) */
#define LKL_BLKSSZGET  _LKL_IO(0x12,104)/* get block device sector size */
#if 0
#define LKL_BLKPG      _LKL_IO(0x12,105)/* See blkpg.h */

/* Some people are morons.  Do not use sizeof! */

#define LKL_BLKELVGET  _LKL_IOR(0x12,106,lkl_size_t)/* elevator get */
#define LKL_BLKELVSET  _LKL_IOW(0x12,107,lkl_size_t)/* elevator set */
/* This was here just to show that the number is taken -
   probably all these _LKL_IO(0x12,*) ioctls should be moved to blkpg.h. */
#endif
/* A jump here: 108-111 have been used for various private purposes. */
#define LKL_BLKBSZGET  _LKL_IOR(0x12,112,lkl_size_t)
#define LKL_BLKBSZSET  _LKL_IOW(0x12,113,lkl_size_t)
#define LKL_BLKGETSIZE64 _LKL_IOR(0x12,114,lkl_size_t)	/* return device size in bytes (lkl_u64 *arg) */
#define LKL_BLKTRACESETUP _LKL_IOWR(0x12,115,struct blk_user_trace_setup)
#define LKL_BLKTRACESTART _LKL_IO(0x12,116)
#define LKL_BLKTRACESTOP _LKL_IO(0x12,117)
#define LKL_BLKTRACETEARDOWN _LKL_IO(0x12,118)
#define LKL_BLKDISCARD _LKL_IO(0x12,119)
#define LKL_BLKIOMIN _LKL_IO(0x12,120)
#define LKL_BLKIOOPT _LKL_IO(0x12,121)
#define LKL_BLKALIGNOFF _LKL_IO(0x12,122)
#define LKL_BLKPBSZGET _LKL_IO(0x12,123)
#define LKL_BLKDISCARDZEROES _LKL_IO(0x12,124)
#define LKL_BLKSECDISCARD _LKL_IO(0x12,125)
#define LKL_BLKROTATIONAL _LKL_IO(0x12,126)
#define LKL_BLKZEROOUT _LKL_IO(0x12,127)
#define LKL_BLKGETDISKSEQ _LKL_IOR(0x12,128,__lkl__u64)
/*
 * A jump here: 130-136 are reserved for zoned block devices
 * (see uapi/linux/blkzoned.h)
 */

#define LKL_BMAP_IOCTL 1		/* obsolete - kept for compatibility */
#define LKL_FIBMAP	   _LKL_IO(0x00,1)	/* bmap access */
#define LKL_FIGETBSZ   _LKL_IO(0x00,2)	/* get the block size used for bmap */
#define LKL_FIFREEZE	_LKL_IOWR('X', 119, int)	/* Freeze */
#define LKL_FITHAW		_LKL_IOWR('X', 120, int)	/* Thaw */
#define LKL_FITRIM		_LKL_IOWR('X', 121, struct lkl_fstrim_range)	/* Trim */
#define LKL_FICLONE		_LKL_IOW(0x94, 9, int)
#define LKL_FICLONERANGE	_LKL_IOW(0x94, 13, struct lkl_file_clone_range)
#define LKL_FIDEDUPERANGE	_LKL_IOWR(0x94, 54, struct lkl_file_dedupe_range)

#define LKL_FSLABEL_MAX 256	/* Max chars for the interface; each fs may differ */

#define	LKL_FS_IOC_GETFLAGS			_LKL_IOR('f', 1, long)
#define	LKL_FS_IOC_SETFLAGS			_LKL_IOW('f', 2, long)
#define	LKL_FS_IOC_GETVERSION		_LKL_IOR('v', 1, long)
#define	LKL_FS_IOC_SETVERSION		_LKL_IOW('v', 2, long)
#define LKL_FS_IOC_FIEMAP			_LKL_IOWR('f', 11, struct fiemap)
#define LKL_FS_IOC32_GETFLAGS		_LKL_IOR('f', 1, int)
#define LKL_FS_IOC32_SETFLAGS		_LKL_IOW('f', 2, int)
#define LKL_FS_IOC32_GETVERSION		_LKL_IOR('v', 1, int)
#define LKL_FS_IOC32_SETVERSION		_LKL_IOW('v', 2, int)
#define LKL_FS_IOC_FSGETXATTR		_LKL_IOR('X', 31, struct lkl_fsxattr)
#define LKL_FS_IOC_FSSETXATTR		_LKL_IOW('X', 32, struct lkl_fsxattr)
#define LKL_FS_IOC_GETFSLABEL		_LKL_IOR(0x94, 49, char[LKL_FSLABEL_MAX])
#define LKL_FS_IOC_SETFSLABEL		_LKL_IOW(0x94, 50, char[LKL_FSLABEL_MAX])

/*
 * Inode flags (LKL_FS_IOC_GETFLAGS / LKL_FS_IOC_SETFLAGS)
 *
 * Note: for historical reasons, these flags were originally used and
 * defined for use by ext2/ext3, and then other file systems started
 * using these flags so they wouldn't need to write their own version
 * of chattr/lsattr (which was shipped as part of e2fsprogs).  You
 * should think twice before trying to use these flags in new
 * contexts, or trying to assign these flags, since they are used both
 * as the UAPI and the on-disk encoding for ext2/3/4.  Also, we are
 * almost out of 32-bit flags.  :-)
 *
 * We have recently hoisted LKL_FS_IOC_FSGETXATTR / LKL_FS_IOC_FSSETXATTR from
 * XFS to the generic FS level interface.  This uses a structure that
 * has padding and hence has more room to grow, so it may be more
 * appropriate for many new use cases.
 *
 * Please do not change these flags or interfaces before checking with
 * linux-fsdevel@vger.kernel.org and linux-api@vger.kernel.org.
 */
#define	LKL_FS_SECRM_FL			0x00000001 /* Secure deletion */
#define	LKL_FS_UNRM_FL			0x00000002 /* Undelete */
#define	LKL_FS_COMPR_FL			0x00000004 /* Compress file */
#define LKL_FS_SYNC_FL			0x00000008 /* Synchronous updates */
#define LKL_FS_IMMUTABLE_FL			0x00000010 /* Immutable file */
#define LKL_FS_APPEND_FL			0x00000020 /* writes to file may only append */
#define LKL_FS_NODUMP_FL			0x00000040 /* do not dump file */
#define LKL_FS_NOATIME_FL			0x00000080 /* do not update atime */
/* Reserved for compression usage... */
#define LKL_FS_DIRTY_FL			0x00000100
#define LKL_FS_COMPRBLK_FL			0x00000200 /* One or more compressed clusters */
#define LKL_FS_NOCOMP_FL			0x00000400 /* Don't compress */
/* End compression flags --- maybe not all used */
#define LKL_FS_ENCRYPT_FL			0x00000800 /* Encrypted file */
#define LKL_FS_BTREE_FL			0x00001000 /* btree format dir */
#define LKL_FS_INDEX_FL			0x00001000 /* hash-indexed directory */
#define LKL_FS_IMAGIC_FL			0x00002000 /* AFS directory */
#define LKL_FS_JOURNAL_DATA_FL		0x00004000 /* Reserved for ext3 */
#define LKL_FS_NOTAIL_FL			0x00008000 /* file tail should not be merged */
#define LKL_FS_DIRSYNC_FL			0x00010000 /* dirsync behaviour (directories only) */
#define LKL_FS_TOPDIR_FL			0x00020000 /* Top of directory hierarchies*/
#define LKL_FS_HUGE_FILE_FL			0x00040000 /* Reserved for ext4 */
#define LKL_FS_EXTENT_FL			0x00080000 /* Extents */
#define LKL_FS_VERITY_FL			0x00100000 /* Verity protected inode */
#define LKL_FS_EA_INODE_FL			0x00200000 /* Inode used for large EA */
#define LKL_FS_EOFBLOCKS_FL			0x00400000 /* Reserved for ext4 */
#define LKL_FS_NOCOW_FL			0x00800000 /* Do not cow file */
#define LKL_FS_DAX_FL			0x02000000 /* Inode is DAX */
#define LKL_FS_INLINE_DATA_FL		0x10000000 /* Reserved for ext4 */
#define LKL_FS_PROJINHERIT_FL		0x20000000 /* Create with parents projid */
#define LKL_FS_CASEFOLD_FL			0x40000000 /* Folder is case insensitive */
#define LKL_FS_RESERVED_FL			0x80000000 /* reserved for ext2 lib */

#define LKL_FS_FL_USER_VISIBLE		0x0003DFFF /* User visible flags */
#define LKL_FS_FL_USER_MODIFIABLE		0x000380FF /* User modifiable flags */


#define LKL_SYNC_FILE_RANGE_WAIT_BEFORE	1
#define LKL_SYNC_FILE_RANGE_WRITE		2
#define LKL_SYNC_FILE_RANGE_WAIT_AFTER	4
#define LKL_SYNC_FILE_RANGE_WRITE_AND_WAIT	(LKL_SYNC_FILE_RANGE_WRITE | \
					 LKL_SYNC_FILE_RANGE_WAIT_BEFORE | \
					 LKL_SYNC_FILE_RANGE_WAIT_AFTER)

/*
 * Flags for preadv2/pwritev2:
 */

typedef int __lkl__bitwise __lkl__kernel_rwf_t;

/* high priority request, poll if possible */
#define LKL_RWF_HIPRI	((__lkl__kernel_rwf_t)0x00000001)

/* per-IO LKL_O_DSYNC */
#define LKL_RWF_DSYNC	((__lkl__kernel_rwf_t)0x00000002)

/* per-IO LKL_O_SYNC */
#define LKL_RWF_SYNC	((__lkl__kernel_rwf_t)0x00000004)

/* per-IO, return -LKL_EAGAIN if operation would block */
#define LKL_RWF_NOWAIT	((__lkl__kernel_rwf_t)0x00000008)

/* per-IO LKL_O_APPEND */
#define LKL_RWF_APPEND	((__lkl__kernel_rwf_t)0x00000010)

/* mask of flags supported by the kernel */
#define LKL_RWF_SUPPORTED	(LKL_RWF_HIPRI | LKL_RWF_DSYNC | LKL_RWF_SYNC | LKL_RWF_NOWAIT |\
			 LKL_RWF_APPEND)

#endif /* _LKL_LINUX_FS_H */
