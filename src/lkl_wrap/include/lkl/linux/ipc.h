/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_IPC_H
#define _LKL_LINUX_IPC_H

#include <lkl/linux/types.h>

#define LKL_IPC_PRIVATE ((__lkl__kernel_key_t) 0)  

/* Obsolete, used only for backwards compatibility and libc5 compiles */
struct ipc_perm
{
	__lkl__kernel_key_t	key;
	__lkl__kernel_uid_t	uid;
	__lkl__kernel_gid_t	gid;
	__lkl__kernel_uid_t	cuid;
	__lkl__kernel_gid_t	cgid;
	__lkl__kernel_mode_t	mode; 
	unsigned short	seq;
};

/* Include the definition of ipc64_perm */
#include <lkl/asm/ipcbuf.h>

/* resource get request flags */
#define LKL_IPC_CREAT  00001000   /* create if key is nonexistent */
#define LKL_IPC_EXCL   00002000   /* fail if key exists */
#define LKL_IPC_NOWAIT 00004000   /* return error on wait */

/* these fields are used by the LKL_DIPC package so the kernel as standard
   should avoid using them if possible */
   
#define LKL_IPC_DIPC 00010000  /* make it distributed */
#define LKL_IPC_OWN  00020000  /* this machine is the LKL_DIPC owner */

/* 
 * Control commands used with semctl, msgctl and shmctl 
 * see also specific commands in sem.h, msg.h and shm.h
 */
#define LKL_IPC_RMID 0     /* remove resource */
#define LKL_IPC_SET  1     /* set ipc_perm options */
#define LKL_IPC_STAT 2     /* get ipc_perm options */
#define LKL_IPC_INFO 3     /* see ipcs */

/*
 * Version flags for semctl, msgctl, and shmctl commands
 * These are passed as bitflags or-ed with the actual command
 */
#define LKL_IPC_OLD 0	/* Old version (no 32-bit UID support on many
			   architectures) */
#define LKL_IPC_64  0x0100  /* New version (support 32-bit UIDs, bigger
			   message sizes, etc. */

/*
 * These are used to wrap system calls.
 *
 * See architecture code for ugly details..
 */
struct lkl_ipc_kludge {
	struct lkl_msgbuf *msgp;
	long msgtyp;
};

#define LKL_SEMOP		 1
#define LKL_SEMGET		 2
#define LKL_SEMCTL		 3
#define LKL_SEMTIMEDOP	 4
#define LKL_MSGSND		11
#define LKL_MSGRCV		12
#define LKL_MSGGET		13
#define LKL_MSGCTL		14
#define LKL_SHMAT		21
#define LKL_SHMDT		22
#define LKL_SHMGET		23
#define LKL_SHMCTL		24

/* Used by the LKL_DIPC package, try and avoid reusing it */
#define LKL_DIPC            25

#define LKL_IPCCALL(version,op)	((version)<<16 | (op))


#endif /* _LKL_LINUX_IPC_H */
