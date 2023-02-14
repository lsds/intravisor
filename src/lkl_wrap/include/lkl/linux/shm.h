/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_SHM_H_
#define _LKL_LINUX_SHM_H_

#include <lkl/linux/ipc.h>
#include <lkl/linux/errno.h>
#include <lkl/asm-generic/hugetlb_encode.h>
#include <unistd.h>

/*
 * LKL_SHMMNI, LKL_SHMMAX and LKL_SHMALL are default upper limits which can be
 * modified by sysctl. The LKL_SHMMAX and LKL_SHMALL values have been chosen to
 * be as large possible without facilitating scenarios where userspace
 * causes overflows when adjusting the limits via operations of the form
 * "retrieve current limit; add X; update limit". It is therefore not
 * advised to make LKL_SHMMAX and LKL_SHMALL any larger. These limits are
 * suitable for both 32 and 64-bit systems.
 */
#define LKL_SHMMIN 1			 /* min shared seg size (bytes) */
#define LKL_SHMMNI 4096			 /* max num of segs system wide */
#define LKL_SHMMAX (ULONG_MAX - (1UL << 24)) /* max shared seg size (bytes) */
#define LKL_SHMALL (ULONG_MAX - (1UL << 24)) /* max shm system wide (pages) */
#define LKL_SHMSEG LKL_SHMMNI			 /* max shared segs per process */

/* Obsolete, used only for backwards compatibility and libc5 compiles */
struct lkl_shmid_ds {
	struct ipc_perm		shm_perm;	/* operation perms */
	int			shm_segsz;	/* size of segment (bytes) */
	__lkl__kernel_time_t		shm_atime;	/* last attach time */
	__lkl__kernel_time_t		shm_dtime;	/* last detach time */
	__lkl__kernel_time_t		shm_ctime;	/* last change time */
	__lkl__kernel_ipc_pid_t	shm_cpid;	/* pid of creator */
	__lkl__kernel_ipc_pid_t	shm_lpid;	/* pid of last operator */
	unsigned short		shm_nattch;	/* no. of current attaches */
	unsigned short 		shm_unused;	/* compatibility */
	void 			*shm_unused2;	/* ditto - used by LKL_DIPC */
	void			*shm_unused3;	/* unused */
};

/* Include the definition of shmid64_ds and shminfo64 */
#include <lkl/asm/shmbuf.h>

/*
 * shmget() shmflg values.
 */
/* The bottom nine bits are the same as open(2) mode flags */
#define LKL_SHM_R		0400	/* or S_IRUGO from <linux/stat.h> */
#define LKL_SHM_W		0200	/* or S_IWUGO from <linux/stat.h> */
/* Bits 9 & 10 are LKL_IPC_CREAT and LKL_IPC_EXCL */
#define LKL_SHM_HUGETLB	04000	/* segment will use huge TLB pages */
#define LKL_SHM_NORESERVE	010000	/* don't check for reservations */

/*
 * Huge page size encoding when LKL_SHM_HUGETLB is specified, and a huge page
 * size other than the default is desired.  See hugetlb_encode.h
 */
#define LKL_SHM_HUGE_SHIFT	LKL_HUGETLB_FLAG_ENCODE_SHIFT
#define LKL_SHM_HUGE_MASK	LKL_HUGETLB_FLAG_ENCODE_MASK

#define LKL_SHM_HUGE_64KB	LKL_HUGETLB_FLAG_ENCODE_64KB
#define LKL_SHM_HUGE_512KB	LKL_HUGETLB_FLAG_ENCODE_512KB
#define LKL_SHM_HUGE_1MB	LKL_HUGETLB_FLAG_ENCODE_1MB
#define LKL_SHM_HUGE_2MB	LKL_HUGETLB_FLAG_ENCODE_2MB
#define LKL_SHM_HUGE_8MB	LKL_HUGETLB_FLAG_ENCODE_8MB
#define LKL_SHM_HUGE_16MB	LKL_HUGETLB_FLAG_ENCODE_16MB
#define LKL_SHM_HUGE_256MB	LKL_HUGETLB_FLAG_ENCODE_256MB
#define LKL_SHM_HUGE_1GB	LKL_HUGETLB_FLAG_ENCODE_1GB
#define LKL_SHM_HUGE_2GB	LKL_HUGETLB_FLAG_ENCODE_2GB
#define LKL_SHM_HUGE_16GB	LKL_HUGETLB_FLAG_ENCODE_16GB

/*
 * shmat() shmflg values
 */
#define	LKL_SHM_RDONLY	010000	/* read-only access */
#define	LKL_SHM_RND		020000	/* round attach address to SHMLBA boundary */
#define	LKL_SHM_REMAP	040000	/* take-over region on attach */
#define	LKL_SHM_EXEC	0100000	/* execution access */

/* super user shmctl commands */
#define LKL_SHM_LOCK 	11
#define LKL_SHM_UNLOCK 	12

/* ipcs ctl commands */
#define LKL_SHM_STAT	13
#define LKL_SHM_INFO	14
#define LKL_SHM_STAT_ANY    15

/* Obsolete, used only for backwards compatibility */
struct	lkl_shminfo {
	int shmmax;
	int shmmin;
	int shmmni;
	int shmseg;
	int shmall;
};

struct lkl_shm_info {
	int used_ids;
	__lkl__kernel_ulong_t shm_tot;	/* total allocated shm */
	__lkl__kernel_ulong_t shm_rss;	/* total resident shm */
	__lkl__kernel_ulong_t shm_swp;	/* total swapped shm */
	__lkl__kernel_ulong_t swap_attempts;
	__lkl__kernel_ulong_t swap_successes;
};


#endif /* _LKL_LINUX_SHM_H_ */
