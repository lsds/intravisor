/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This is <linux/capability.h>
 *
 * Andrew G. Morgan <morgan@kernel.org>
 * Alexander Kjeldaas <astor@guardian.no>
 * with help from Aleph1, Roland Buresund and Andrew Main.
 *
 * See here for the libcap library ("POSIX draft" compliance):
 *
 * ftp://www.kernel.org/pub/linux/libs/security/linux-privs/kernel-2.6/
 */

#ifndef _LKL_LINUX_CAPABILITY_H
#define _LKL_LINUX_CAPABILITY_H

#include <lkl/linux/types.h>

/* User-level do most of the mapping between kernel and user
   capabilities based on the version tag given by the kernel. The
   kernel might be somewhat backwards compatible, but don't bet on
   it. */

/* Note, cap_t, is defined by POSIX (draft) to be an "opaque" pointer to
   a set of three capability sets.  The transposition of 3*the
   following structure to such a composite is better handled in a user
   library since the draft standard requires the use of malloc/free
   etc.. */

#define _LKL_LINUX_CAPABILITY_VERSION_1  0x19980330
#define _LKL_LINUX_CAPABILITY_U32S_1     1

#define _LKL_LINUX_CAPABILITY_VERSION_2  0x20071026  /* deprecated - use v3 */
#define _LKL_LINUX_CAPABILITY_U32S_2     2

#define _LKL_LINUX_CAPABILITY_VERSION_3  0x20080522
#define _LKL_LINUX_CAPABILITY_U32S_3     2

typedef struct __lkl__user_cap_header_struct {
	__lkl__u32 version;
	int pid;
} *lkl_cap_user_header_t;

typedef struct __lkl__user_cap_data_struct {
        __lkl__u32 effective;
        __lkl__u32 permitted;
        __lkl__u32 inheritable;
} *lkl_cap_user_data_t;


#define LKL_VFS_CAP_REVISION_MASK	0xFF000000
#define LKL_VFS_CAP_REVISION_SHIFT	24
#define LKL_VFS_CAP_FLAGS_MASK	~LKL_VFS_CAP_REVISION_MASK
#define LKL_VFS_CAP_FLAGS_EFFECTIVE	0x000001

#define LKL_VFS_CAP_REVISION_1	0x01000000
#define LKL_VFS_CAP_U32_1           1
#define LKL_XATTR_CAPS_SZ_1         (sizeof(__lkl__le32)*(1 + 2*LKL_VFS_CAP_U32_1))

#define LKL_VFS_CAP_REVISION_2	0x02000000
#define LKL_VFS_CAP_U32_2           2
#define LKL_XATTR_CAPS_SZ_2         (sizeof(__lkl__le32)*(1 + 2*LKL_VFS_CAP_U32_2))

#define LKL_VFS_CAP_REVISION_3	0x03000000
#define LKL_VFS_CAP_U32_3           2
#define LKL_XATTR_CAPS_SZ_3         (sizeof(__lkl__le32)*(2 + 2*LKL_VFS_CAP_U32_3))

#define LKL_XATTR_CAPS_SZ           LKL_XATTR_CAPS_SZ_3
#define LKL_VFS_CAP_U32             LKL_VFS_CAP_U32_3
#define LKL_VFS_CAP_REVISION	LKL_VFS_CAP_REVISION_3

struct lkl_vfs_cap_data {
	__lkl__le32 magic_etc;            /* Little endian */
	struct {
		__lkl__le32 permitted;    /* Little endian */
		__lkl__le32 inheritable;  /* Little endian */
	} data[LKL_VFS_CAP_U32];
};

/*
 * same as vfs_cap_data but with a rootid at the end
 */
struct lkl_vfs_ns_cap_data {
	__lkl__le32 magic_etc;
	struct {
		__lkl__le32 permitted;    /* Little endian */
		__lkl__le32 inheritable;  /* Little endian */
	} data[LKL_VFS_CAP_U32];
	__lkl__le32 rootid;
};


/*
 * Backwardly compatible definition for source code - trapped in a
 * 32-bit world. If you find you need this, please consider using
 * libcap to untrap yourself...
 */
#define _LKL_LINUX_CAPABILITY_VERSION  _LKL_LINUX_CAPABILITY_VERSION_1
#define _LKL_LINUX_CAPABILITY_U32S     _LKL_LINUX_CAPABILITY_U32S_1



/**
 ** POSIX-draft defined capabilities.
 **/

/* In a system with the [_POSIX_CHOWN_RESTRICTED] option defined, this
   overrides the restriction of changing file ownership and group
   ownership. */

#define LKL_CAP_CHOWN            0

/* Override all DAC access, including ACL execute access if
   [_POSIX_ACL] is defined. Excluding DAC access covered by
   LKL_CAP_LINUX_IMMUTABLE. */

#define LKL_CAP_DAC_OVERRIDE     1

/* Overrides all DAC restrictions regarding read and search on files
   and directories, including ACL restrictions if [_POSIX_ACL] is
   defined. Excluding DAC access covered by LKL_CAP_LINUX_IMMUTABLE. */

#define LKL_CAP_DAC_READ_SEARCH  2

/* Overrides all restrictions about allowed operations on files, where
   file owner ID must be equal to the user ID, except where LKL_CAP_FSETID
   is applicable. It doesn't override MAC and DAC restrictions. */

#define LKL_CAP_FOWNER           3

/* Overrides the following restrictions that the effective user ID
   shall match the file owner ID when setting the LKL_S_ISUID and LKL_S_ISGID
   bits on that file; that the effective group ID (or one of the
   supplementary group IDs) shall match the file owner ID when setting
   the LKL_S_ISGID bit on that file; that the LKL_S_ISUID and LKL_S_ISGID bits are
   cleared on successful return from chown(2) (not implemented). */

#define LKL_CAP_FSETID           4

/* Overrides the restriction that the real or effective user ID of a
   process sending a signal must match the real or effective user ID
   of the process receiving the signal. */

#define LKL_CAP_KILL             5

/* Allows setgid(2) manipulation */
/* Allows setgroups(2) */
/* Allows forged gids on socket credentials passing. */

#define LKL_CAP_SETGID           6

/* Allows set*uid(2) manipulation (including fsuid). */
/* Allows forged pids on socket credentials passing. */

#define LKL_CAP_SETUID           7


/**
 ** Linux-specific capabilities
 **/

/* Without VFS support for capabilities:
 *   Transfer any capability in your permitted set to any pid,
 *   remove any capability in your permitted set from any pid
 * With VFS support for capabilities (neither of above, but)
 *   Add any capability from current's capability bounding set
 *       to the current process' inheritable set
 *   Allow taking bits out of capability bounding set
 *   Allow modification of the securebits for a process
 */

#define LKL_CAP_SETPCAP          8

/* Allow modification of S_IMMUTABLE and S_APPEND file attributes */

#define LKL_CAP_LINUX_IMMUTABLE  9

/* Allows binding to TCP/UDP sockets below 1024 */
/* Allows binding to ATM VCIs below 32 */

#define LKL_CAP_NET_BIND_SERVICE 10

/* Allow broadcasting, listen to multicast */

#define LKL_CAP_NET_BROADCAST    11

/* Allow interface configuration */
/* Allow administration of IP firewall, masquerading and accounting */
/* Allow setting debug option on sockets */
/* Allow modification of routing tables */
/* Allow setting arbitrary process / process group ownership on
   sockets */
/* Allow binding to any address for transparent proxying (also via NET_RAW) */
/* Allow setting TOS (type of service) */
/* Allow setting promiscuous mode */
/* Allow clearing driver statistics */
/* Allow multicasting */
/* Allow read/write of device-specific registers */
/* Allow activation of ATM control sockets */

#define LKL_CAP_NET_ADMIN        12

/* Allow use of RAW sockets */
/* Allow use of PACKET sockets */
/* Allow binding to any address for transparent proxying (also via NET_ADMIN) */

#define LKL_CAP_NET_RAW          13

/* Allow locking of shared memory segments */
/* Allow mlock and mlockall (which doesn't really have anything to do
   with IPC) */

#define LKL_CAP_IPC_LOCK         14

/* Override IPC ownership checks */

#define LKL_CAP_IPC_OWNER        15

/* Insert and remove kernel modules - modify kernel without limit */
#define LKL_CAP_SYS_MODULE       16

/* Allow ioperm/iopl access */
/* Allow sending USB messages to any device via /dev/bus/usb */

#define LKL_CAP_SYS_RAWIO        17

/* Allow use of chroot() */

#define LKL_CAP_SYS_CHROOT       18

/* Allow ptrace() of any process */

#define LKL_CAP_SYS_PTRACE       19

/* Allow configuration of process accounting */

#define LKL_CAP_SYS_PACCT        20

/* Allow configuration of the secure attention key */
/* Allow administration of the random device */
/* Allow examination and configuration of disk quotas */
/* Allow setting the domainname */
/* Allow setting the hostname */
/* Allow calling bdflush() */
/* Allow mount() and umount(), setting up new smb connection */
/* Allow some autofs root ioctls */
/* Allow nfsservctl */
/* Allow VM86_REQUEST_IRQ */
/* Allow to read/write pci config on alpha */
/* Allow irix_prctl on mips (setstacksize) */
/* Allow flushing all cache on m68k (sys_cacheflush) */
/* Allow removing semaphores */
/* Used instead of LKL_CAP_CHOWN to "chown" IPC message queues, semaphores
   and shared memory */
/* Allow locking/unlocking of shared memory segment */
/* Allow turning swap on/off */
/* Allow forged pids on socket credentials passing */
/* Allow setting readahead and flushing buffers on block devices */
/* Allow setting geometry in floppy driver */
/* Allow turning DMA on/off in xd driver */
/* Allow administration of md devices (mostly the above, but some
   extra ioctls) */
/* Allow tuning the ide driver */
/* Allow access to the nvram device */
/* Allow administration of apm_bios, serial and bttv (TV) device */
/* Allow manufacturer commands in isdn CAPI support driver */
/* Allow reading non-standardized portions of pci configuration space */
/* Allow DDI debug ioctl on sbpcd driver */
/* Allow setting up serial ports */
/* Allow sending raw qic-117 commands */
/* Allow enabling/disabling tagged queuing on SCSI controllers and sending
   arbitrary SCSI commands */
/* Allow setting encryption key on loopback filesystem */
/* Allow setting zone reclaim policy */

#define LKL_CAP_SYS_ADMIN        21

/* Allow use of reboot() */

#define LKL_CAP_SYS_BOOT         22

/* Allow raising priority and setting priority on other (different
   UID) processes */
/* Allow use of FIFO and round-robin (realtime) scheduling on own
   processes and setting the scheduling algorithm used by another
   process. */
/* Allow setting cpu affinity on other processes */

#define LKL_CAP_SYS_NICE         23

/* Override resource limits. Set resource limits. */
/* Override quota limits. */
/* Override reserved space on ext2 filesystem */
/* Modify data journaling mode on ext3 filesystem (uses journaling
   resources) */
/* NOTE: ext2 honors fsuid when checking for resource overrides, so
   you can override using fsuid too */
/* Override size restrictions on IPC message queues */
/* Allow more than 64hz interrupts from the real-time clock */
/* Override max number of consoles on console allocation */
/* Override max number of keymaps */

#define LKL_CAP_SYS_RESOURCE     24

/* Allow manipulation of system clock */
/* Allow irix_stime on mips */
/* Allow setting the real-time clock */

#define LKL_CAP_SYS_TIME         25

/* Allow configuration of tty devices */
/* Allow vhangup() of tty */

#define LKL_CAP_SYS_TTY_CONFIG   26

/* Allow the privileged aspects of mknod() */

#define LKL_CAP_MKNOD            27

/* Allow taking of leases on files */

#define LKL_CAP_LEASE            28

/* Allow writing the audit log via unicast netlink socket */

#define LKL_CAP_AUDIT_WRITE      29

/* Allow configuration of audit via unicast netlink socket */

#define LKL_CAP_AUDIT_CONTROL    30

#define LKL_CAP_SETFCAP	     31

/* Override MAC access.
   The base kernel enforces no MAC policy.
   An LSM may enforce a MAC policy, and if it does and it chooses
   to implement capability based overrides of that policy, this is
   the capability it should use to do so. */

#define LKL_CAP_MAC_OVERRIDE     32

/* Allow MAC configuration or state changes.
   The base kernel requires no MAC configuration.
   An LSM may enforce a MAC policy, and if it does and it chooses
   to implement capability based checks on modifications to that
   policy or the data required to maintain it, this is the
   capability it should use to do so. */

#define LKL_CAP_MAC_ADMIN        33

/* Allow configuring the kernel's syslog (printk behaviour) */

#define LKL_CAP_SYSLOG           34

/* Allow triggering something that will wake the system */

#define LKL_CAP_WAKE_ALARM            35

/* Allow preventing system suspends */

#define LKL_CAP_BLOCK_SUSPEND    36

/* Allow reading the audit log via multicast netlink socket */

#define LKL_CAP_AUDIT_READ		37


#define LKL_CAP_LAST_CAP         LKL_CAP_AUDIT_READ

#define lkl_cap_valid(x) ((x) >= 0 && (x) <= LKL_CAP_LAST_CAP)

/*
 * Bit location of each capability (used by user-space library and kernel)
 */

#define LKL_CAP_TO_INDEX(x)     ((x) >> 5)        /* 1 << 5 == bits in __lkl__u32 */
#define LKL_CAP_TO_MASK(x)      (1 << ((x) & 31)) /* mask for indexed __lkl__u32 */


#endif /* _LKL_LINUX_CAPABILITY_H */
