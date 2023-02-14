/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_ERRNO_H
#define _LKL_ASM_GENERIC_ERRNO_H

#include <lkl/asm-generic/errno-base.h>

#define	LKL_EDEADLK		35	/* Resource deadlock would occur */
#define	LKL_ENAMETOOLONG	36	/* File name too long */
#define	LKL_ENOLCK		37	/* No record locks available */

/*
 * This error code is special: arch syscall entry code will return
 * -LKL_ENOSYS if users try to call a syscall that doesn't exist.  To keep
 * failures of syscalls that really do exist distinguishable from
 * failures due to attempts to use a nonexistent syscall, syscall
 * implementations should refrain from returning -LKL_ENOSYS.
 */
#define	LKL_ENOSYS		38	/* Invalid system call number */

#define	LKL_ENOTEMPTY	39	/* Directory not empty */
#define	LKL_ELOOP		40	/* Too many symbolic links encountered */
#define	LKL_EWOULDBLOCK	LKL_EAGAIN	/* Operation would block */
#define	LKL_ENOMSG		42	/* No message of desired type */
#define	LKL_EIDRM		43	/* Identifier removed */
#define	LKL_ECHRNG		44	/* Channel number out of range */
#define	LKL_EL2NSYNC	45	/* Level 2 not synchronized */
#define	LKL_EL3HLT		46	/* Level 3 halted */
#define	LKL_EL3RST		47	/* Level 3 reset */
#define	LKL_ELNRNG		48	/* Link number out of range */
#define	LKL_EUNATCH		49	/* Protocol driver not attached */
#define	LKL_ENOCSI		50	/* No CSI structure available */
#define	LKL_EL2HLT		51	/* Level 2 halted */
#define	LKL_EBADE		52	/* Invalid exchange */
#define	LKL_EBADR		53	/* Invalid request descriptor */
#define	LKL_EXFULL		54	/* Exchange full */
#define	LKL_ENOANO		55	/* No anode */
#define	LKL_EBADRQC		56	/* Invalid request code */
#define	LKL_EBADSLT		57	/* Invalid slot */

#define	LKL_EDEADLOCK	LKL_EDEADLK

#define	LKL_EBFONT		59	/* Bad font file format */
#define	LKL_ENOSTR		60	/* Device not a stream */
#define	LKL_ENODATA		61	/* No data available */
#define	LKL_ETIME		62	/* Timer expired */
#define	LKL_ENOSR		63	/* Out of streams resources */
#define	LKL_ENONET		64	/* Machine is not on the network */
#define	LKL_ENOPKG		65	/* Package not installed */
#define	LKL_EREMOTE		66	/* Object is remote */
#define	LKL_ENOLINK		67	/* Link has been severed */
#define	LKL_EADV		68	/* Advertise error */
#define	LKL_ESRMNT		69	/* Srmount error */
#define	LKL_ECOMM		70	/* Communication error on send */
#define	LKL_EPROTO		71	/* Protocol error */
#define	LKL_EMULTIHOP	72	/* Multihop attempted */
#define	LKL_EDOTDOT		73	/* RFS specific error */
#define	LKL_EBADMSG		74	/* Not a data message */
#define	LKL_EOVERFLOW	75	/* Value too large for defined data type */
#define	LKL_ENOTUNIQ	76	/* Name not unique on network */
#define	LKL_EBADFD		77	/* File descriptor in bad state */
#define	LKL_EREMCHG		78	/* Remote address changed */
#define	LKL_ELIBACC		79	/* Can not access a needed shared library */
#define	LKL_ELIBBAD		80	/* Accessing a corrupted shared library */
#define	LKL_ELIBSCN		81	/* .lib section in a.out corrupted */
#define	LKL_ELIBMAX		82	/* Attempting to link in too many shared libraries */
#define	LKL_ELIBEXEC	83	/* Cannot exec a shared library directly */
#define	LKL_EILSEQ		84	/* Illegal byte sequence */
#define	LKL_ERESTART	85	/* Interrupted system call should be restarted */
#define	LKL_ESTRPIPE	86	/* Streams pipe error */
#define	LKL_EUSERS		87	/* Too many users */
#define	LKL_ENOTSOCK	88	/* Socket operation on non-socket */
#define	LKL_EDESTADDRREQ	89	/* Destination address required */
#define	LKL_EMSGSIZE	90	/* Message too long */
#define	LKL_EPROTOTYPE	91	/* Protocol wrong type for socket */
#define	LKL_ENOPROTOOPT	92	/* Protocol not available */
#define	LKL_EPROTONOSUPPORT	93	/* Protocol not supported */
#define	LKL_ESOCKTNOSUPPORT	94	/* Socket type not supported */
#define	LKL_EOPNOTSUPP	95	/* Operation not supported on transport endpoint */
#define	LKL_EPFNOSUPPORT	96	/* Protocol family not supported */
#define	LKL_EAFNOSUPPORT	97	/* Address family not supported by protocol */
#define	LKL_EADDRINUSE	98	/* Address already in use */
#define	LKL_EADDRNOTAVAIL	99	/* Cannot assign requested address */
#define	LKL_ENETDOWN	100	/* Network is down */
#define	LKL_ENETUNREACH	101	/* Network is unreachable */
#define	LKL_ENETRESET	102	/* Network dropped connection because of reset */
#define	LKL_ECONNABORTED	103	/* Software caused connection abort */
#define	LKL_ECONNRESET	104	/* Connection reset by peer */
#define	LKL_ENOBUFS		105	/* No buffer space available */
#define	LKL_EISCONN		106	/* Transport endpoint is already connected */
#define	LKL_ENOTCONN	107	/* Transport endpoint is not connected */
#define	LKL_ESHUTDOWN	108	/* Cannot send after transport endpoint shutdown */
#define	LKL_ETOOMANYREFS	109	/* Too many references: cannot splice */
#define	LKL_ETIMEDOUT	110	/* Connection timed out */
#define	LKL_ECONNREFUSED	111	/* Connection refused */
#define	LKL_EHOSTDOWN	112	/* Host is down */
#define	LKL_EHOSTUNREACH	113	/* No route to host */
#define	LKL_EALREADY	114	/* Operation already in progress */
#define	LKL_EINPROGRESS	115	/* Operation now in progress */
#define	LKL_ESTALE		116	/* Stale file handle */
#define	LKL_EUCLEAN		117	/* Structure needs cleaning */
#define	LKL_ENOTNAM		118	/* Not a XENIX named type file */
#define	LKL_ENAVAIL		119	/* No XENIX semaphores available */
#define	LKL_EISNAM		120	/* Is a named type file */
#define	LKL_EREMOTEIO	121	/* Remote I/O error */
#define	LKL_EDQUOT		122	/* Quota exceeded */

#define	LKL_ENOMEDIUM	123	/* No medium found */
#define	LKL_EMEDIUMTYPE	124	/* Wrong medium type */
#define	LKL_ECANCELED	125	/* Operation Canceled */
#define	LKL_ENOKEY		126	/* Required key not available */
#define	LKL_EKEYEXPIRED	127	/* Key has expired */
#define	LKL_EKEYREVOKED	128	/* Key has been revoked */
#define	LKL_EKEYREJECTED	129	/* Key was rejected by service */

/* for robust mutexes */
#define	LKL_EOWNERDEAD	130	/* Owner died */
#define	LKL_ENOTRECOVERABLE	131	/* State not recoverable */

#define LKL_ERFKILL		132	/* Operation not possible due to RF-kill */

#define LKL_EHWPOISON	133	/* Memory page has hardware error */

#endif
