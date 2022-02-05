/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_SYSINFO_H
#define _LKL_LINUX_SYSINFO_H

#include <lkl/linux/types.h>

#define LKL_SI_LOAD_SHIFT	16
struct lkl_sysinfo {
	__lkl__kernel_long_t uptime;		/* Seconds since boot */
	__lkl__kernel_ulong_t loads[3];	/* 1, 5, and 15 minute load averages */
	__lkl__kernel_ulong_t totalram;	/* Total usable main memory size */
	__lkl__kernel_ulong_t freeram;	/* Available memory size */
	__lkl__kernel_ulong_t sharedram;	/* Amount of shared memory */
	__lkl__kernel_ulong_t bufferram;	/* Memory used by buffers */
	__lkl__kernel_ulong_t totalswap;	/* Total swap space size */
	__lkl__kernel_ulong_t freeswap;	/* swap space still available */
	__lkl__u16 procs;		   	/* Number of current processes */
	__lkl__u16 pad;		   	/* Explicit padding for m68k */
	__lkl__kernel_ulong_t totalhigh;	/* Total high memory size */
	__lkl__kernel_ulong_t freehigh;	/* Available high memory size */
	__lkl__u32 mem_unit;			/* Memory unit size in bytes */
	char _f[20-2*sizeof(__lkl__kernel_ulong_t)-sizeof(__lkl__u32)];	/* Padding: libc5 uses this.. */
};

#endif /* _LKL_LINUX_SYSINFO_H */
