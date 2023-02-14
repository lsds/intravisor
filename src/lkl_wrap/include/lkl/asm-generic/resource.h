/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_RESOURCE_H
#define _LKL_ASM_GENERIC_RESOURCE_H

/*
 * Resource limit IDs
 *
 * ( Compatibility detail: there are architectures that have
 *   a different rlimit ID order in the 5-9 range and want
 *   to keep that order for binary compatibility. The reasons
 *   are historic and all new rlimits are identical across all
 *   arches. If an arch has such special order for some rlimits
 *   then it defines them prior including asm-generic/resource.h. )
 */

#define LKL_RLIMIT_CPU		0	/* CPU time in sec */
#define LKL_RLIMIT_FSIZE		1	/* Maximum filesize */
#define LKL_RLIMIT_DATA		2	/* max data size */
#define LKL_RLIMIT_STACK		3	/* max stack size */
#define LKL_RLIMIT_CORE		4	/* max core file size */

#ifndef LKL_RLIMIT_RSS
# define LKL_RLIMIT_RSS		5	/* max resident set size */
#endif

#ifndef LKL_RLIMIT_NPROC
# define LKL_RLIMIT_NPROC		6	/* max number of processes */
#endif

#ifndef LKL_RLIMIT_NOFILE
# define LKL_RLIMIT_NOFILE		7	/* max number of open files */
#endif

#ifndef LKL_RLIMIT_MEMLOCK
# define LKL_RLIMIT_MEMLOCK		8	/* max locked-in-memory address space */
#endif

#ifndef LKL_RLIMIT_AS
# define LKL_RLIMIT_AS		9	/* address space limit */
#endif

#define LKL_RLIMIT_LOCKS		10	/* maximum file locks held */
#define LKL_RLIMIT_SIGPENDING	11	/* max number of pending signals */
#define LKL_RLIMIT_MSGQUEUE		12	/* maximum bytes in POSIX mqueues */
#define LKL_RLIMIT_NICE		13	/* max nice prio allowed to raise to
					   0-39 for nice level 19 .. -20 */
#define LKL_RLIMIT_RTPRIO		14	/* maximum realtime priority */
#define LKL_RLIMIT_RTTIME		15	/* timeout for RT tasks in us */
#define LKL_RLIM_NLIMITS		16

/*
 * SuS says limits have to be unsigned.
 * Which makes a ton more sense anyway.
 *
 * Some architectures override this (for compatibility reasons):
 */
#ifndef LKL_RLIM_INFINITY
# define LKL_RLIM_INFINITY		(~0UL)
#endif


#endif /* _LKL_ASM_GENERIC_RESOURCE_H */
