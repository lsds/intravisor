/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_LIMITS_H
#define _LKL_LINUX_LIMITS_H

#define LKL_NR_OPEN	        1024

#define LKL_NGROUPS_MAX    65536	/* supplemental group IDs are available */
#define LKL_ARG_MAX       131072	/* # bytes of args + environ for exec() */
#define LKL_LINK_MAX         127	/* # links a file may have */
#define LKL_MAX_CANON        255	/* size of the canonical input queue */
#define LKL_MAX_INPUT        255	/* size of the type-ahead buffer */
#define LKL_NAME_MAX         255	/* # chars in a file name */
#define LKL_PATH_MAX        4096	/* # chars in a path name including nul */
#define LKL_PIPE_BUF        4096	/* # bytes in atomic write to a pipe */
#define LKL_XATTR_NAME_MAX   255	/* # chars in an extended attribute name */
#define LKL_XATTR_SIZE_MAX 65536	/* size of an extended attribute value (64k) */
#define LKL_XATTR_LIST_MAX 65536	/* size of extended attribute namelist (64k) */

#define LKL_RTSIG_MAX	  32

#endif
