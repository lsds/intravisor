/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_ERRNO_BASE_H
#define _LKL_ASM_GENERIC_ERRNO_BASE_H

#define	LKL_EPERM		 1	/* Operation not permitted */
#define	LKL_ENOENT		 2	/* No such file or directory */
#define	LKL_ESRCH		 3	/* No such process */
#define	LKL_EINTR		 4	/* Interrupted system call */
#define	LKL_EIO		 5	/* I/O error */
#define	LKL_ENXIO		 6	/* No such device or address */
#define	LKL_E2BIG		 7	/* Argument list too long */
#define	LKL_ENOEXEC		 8	/* Exec format error */
#define	LKL_EBADF		 9	/* Bad file number */
#define	LKL_ECHILD		10	/* No child processes */
#define	LKL_EAGAIN		11	/* Try again */
#define	LKL_ENOMEM		12	/* Out of memory */
#define	LKL_EACCES		13	/* Permission denied */
#define	LKL_EFAULT		14	/* Bad address */
#define	LKL_ENOTBLK		15	/* Block device required */
#define	LKL_EBUSY		16	/* Device or resource busy */
#define	LKL_EEXIST		17	/* File exists */
#define	LKL_EXDEV		18	/* Cross-device link */
#define	LKL_ENODEV		19	/* No such device */
#define	LKL_ENOTDIR		20	/* Not a directory */
#define	LKL_EISDIR		21	/* Is a directory */
#define	LKL_EINVAL		22	/* Invalid argument */
#define	LKL_ENFILE		23	/* File table overflow */
#define	LKL_EMFILE		24	/* Too many open files */
#define	LKL_ENOTTY		25	/* Not a typewriter */
#define	LKL_ETXTBSY		26	/* Text file busy */
#define	LKL_EFBIG		27	/* File too large */
#define	LKL_ENOSPC		28	/* No space left on device */
#define	LKL_ESPIPE		29	/* Illegal seek */
#define	LKL_EROFS		30	/* Read-only file system */
#define	LKL_EMLINK		31	/* Too many links */
#define	LKL_EPIPE		32	/* Broken pipe */
#define	LKL_EDOM		33	/* Math argument out of domain of func */
#define	LKL_ERANGE		34	/* Math result not representable */

#endif
