#ifndef _LKL_LINUX_MOUNT_H
#define _LKL_LINUX_MOUNT_H

#include <lkl/linux/types.h>

/*
 * These are the fs-independent mount-flags: up to 32 flags are supported
 *
 * Usage of these is restricted within the kernel to core mount(2) code and
 * callers of sys_mount() only.  Filesystems should be using the SB_*
 * equivalent instead.
 */
#define LKL_MS_RDONLY	 1	/* Mount read-only */
#define LKL_MS_NOSUID	 2	/* Ignore suid and sgid bits */
#define LKL_MS_NODEV	 4	/* Disallow access to device special files */
#define LKL_MS_NOEXEC	 8	/* Disallow program execution */
#define LKL_MS_SYNCHRONOUS	16	/* Writes are synced at once */
#define LKL_MS_REMOUNT	32	/* Alter flags of a mounted FS */
#define LKL_MS_MANDLOCK	64	/* Allow mandatory locks on an FS */
#define LKL_MS_DIRSYNC	128	/* Directory modifications are synchronous */
#define LKL_MS_NOSYMFOLLOW	256	/* Do not follow symlinks */
#define LKL_MS_NOATIME	1024	/* Do not update access times. */
#define LKL_MS_NODIRATIME	2048	/* Do not update directory access times */
#define LKL_MS_BIND		4096
#define LKL_MS_MOVE		8192
#define LKL_MS_REC		16384
#define LKL_MS_VERBOSE	32768	/* War is peace. Verbosity is silence.
				   LKL_MS_VERBOSE is deprecated. */
#define LKL_MS_SILENT	32768
#define LKL_MS_POSIXACL	(1<<16)	/* VFS does not apply the umask */
#define LKL_MS_UNBINDABLE	(1<<17)	/* change to unbindable */
#define LKL_MS_PRIVATE	(1<<18)	/* change to private */
#define LKL_MS_SLAVE	(1<<19)	/* change to slave */
#define LKL_MS_SHARED	(1<<20)	/* change to shared */
#define LKL_MS_RELATIME	(1<<21)	/* Update atime relative to mtime/ctime. */
#define LKL_MS_KERNMOUNT	(1<<22) /* this is a kern_mount call */
#define LKL_MS_I_VERSION	(1<<23) /* Update inode I_version field */
#define LKL_MS_STRICTATIME	(1<<24) /* Always perform atime updates */
#define LKL_MS_LAZYTIME	(1<<25) /* Update the on-disk [acm]times lazily */

/* These sb flags are internal to the kernel */
#define LKL_MS_SUBMOUNT     (1<<26)
#define LKL_MS_NOREMOTELOCK	(1<<27)
#define LKL_MS_NOSEC	(1<<28)
#define LKL_MS_BORN		(1<<29)
#define LKL_MS_ACTIVE	(1<<30)
#define LKL_MS_NOUSER	(1<<31)

/*
 * Superblock flags that can be altered by LKL_MS_REMOUNT
 */
#define LKL_MS_RMT_MASK	(LKL_MS_RDONLY|LKL_MS_SYNCHRONOUS|LKL_MS_MANDLOCK|LKL_MS_I_VERSION|\
			 LKL_MS_LAZYTIME)

/*
 * Old magic mount flag and mask
 */
#define LKL_MS_MGC_VAL 0xC0ED0000
#define LKL_MS_MGC_MSK 0xffff0000

/*
 * open_tree() flags.
 */
#define LKL_OPEN_TREE_CLONE		1		/* Clone the target tree and attach the clone */
#define LKL_OPEN_TREE_CLOEXEC	LKL_O_CLOEXEC	/* Close the file on execve() */

/*
 * move_mount() flags.
 */
#define LKL_MOVE_MOUNT_F_SYMLINKS		0x00000001 /* Follow symlinks on from path */
#define LKL_MOVE_MOUNT_F_AUTOMOUNTS		0x00000002 /* Follow automounts on from path */
#define LKL_MOVE_MOUNT_F_EMPTY_PATH		0x00000004 /* Empty from path permitted */
#define LKL_MOVE_MOUNT_T_SYMLINKS		0x00000010 /* Follow symlinks on to path */
#define LKL_MOVE_MOUNT_T_AUTOMOUNTS		0x00000020 /* Follow automounts on to path */
#define LKL_MOVE_MOUNT_T_EMPTY_PATH		0x00000040 /* Empty to path permitted */
#define LKL_MOVE_MOUNT_SET_GROUP		0x00000100 /* Set sharing group instead */
#define LKL_MOVE_MOUNT__MASK		0x00000177

/*
 * fsopen() flags.
 */
#define LKL_FSOPEN_CLOEXEC		0x00000001

/*
 * fspick() flags.
 */
#define LKL_FSPICK_CLOEXEC		0x00000001
#define LKL_FSPICK_SYMLINK_NOFOLLOW	0x00000002
#define LKL_FSPICK_NO_AUTOMOUNT	0x00000004
#define LKL_FSPICK_EMPTY_PATH	0x00000008

/*
 * The type of fsconfig() call made.
 */
enum lkl_fsconfig_command {
	LKL_FSCONFIG_SET_FLAG	= 0,	/* Set parameter, supplying no value */
	LKL_FSCONFIG_SET_STRING	= 1,	/* Set parameter, supplying a string value */
	LKL_FSCONFIG_SET_BINARY	= 2,	/* Set parameter, supplying a binary blob value */
	LKL_FSCONFIG_SET_PATH	= 3,	/* Set parameter, supplying an object by path */
	LKL_FSCONFIG_SET_PATH_EMPTY	= 4,	/* Set parameter, supplying an object by (empty) path */
	LKL_FSCONFIG_SET_FD		= 5,	/* Set parameter, supplying an object by fd */
	LKL_FSCONFIG_CMD_CREATE	= 6,	/* Invoke superblock creation */
	LKL_FSCONFIG_CMD_RECONFIGURE = 7,	/* Invoke superblock reconfiguration */
};

/*
 * fsmount() flags.
 */
#define LKL_FSMOUNT_CLOEXEC		0x00000001

/*
 * Mount attributes.
 */
#define LKL_MOUNT_ATTR_RDONLY	0x00000001 /* Mount read-only */
#define LKL_MOUNT_ATTR_NOSUID	0x00000002 /* Ignore suid and sgid bits */
#define LKL_MOUNT_ATTR_NODEV	0x00000004 /* Disallow access to device special files */
#define LKL_MOUNT_ATTR_NOEXEC	0x00000008 /* Disallow program execution */
#define LKL_MOUNT_ATTR__ATIME	0x00000070 /* Setting on how atime should be updated */
#define LKL_MOUNT_ATTR_RELATIME	0x00000000 /* - Update atime relative to mtime/ctime. */
#define LKL_MOUNT_ATTR_NOATIME	0x00000010 /* - Do not update access times. */
#define LKL_MOUNT_ATTR_STRICTATIME	0x00000020 /* - Always perform atime updates */
#define LKL_MOUNT_ATTR_NODIRATIME	0x00000080 /* Do not update directory access times */
#define LKL_MOUNT_ATTR_IDMAP	0x00100000 /* Idmap mount to @userns_fd in struct lkl_mount_attr. */
#define LKL_MOUNT_ATTR_NOSYMFOLLOW	0x00200000 /* Do not follow symlinks */

/*
 * mount_setattr()
 */
struct lkl_mount_attr {
	__lkl__u64 attr_set;
	__lkl__u64 attr_clr;
	__lkl__u64 propagation;
	__lkl__u64 userns_fd;
};

/* List of all mount_attr versions. */
#define LKL_MOUNT_ATTR_SIZE_VER0	32 /* sizeof first published struct */

#endif /* _LKL_LINUX_MOUNT_H */
