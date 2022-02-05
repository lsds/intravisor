/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_MSG_H
#define _LKL_LINUX_MSG_H

#include <lkl/linux/ipc.h>

/* ipcs ctl commands */
#define LKL_MSG_STAT 11
#define LKL_MSG_INFO 12
#define LKL_MSG_STAT_ANY 13

/* msgrcv options */
#define LKL_MSG_NOERROR     010000  /* no error if message is too big */
#define LKL_MSG_EXCEPT      020000  /* recv any msg except of specified type.*/
#define LKL_MSG_COPY        040000  /* copy (not remove) all queue messages */

/* Obsolete, used only for backwards compatibility and libc5 compiles */
struct lkl_msqid_ds {
	struct ipc_perm msg_perm;
	struct msg *msg_first;		/* first message on queue,unused  */
	struct msg *msg_last;		/* last message in queue,unused */
	__lkl__kernel_time_t msg_stime;	/* last msgsnd time */
	__lkl__kernel_time_t msg_rtime;	/* last msgrcv time */
	__lkl__kernel_time_t msg_ctime;	/* last change time */
	unsigned long  msg_lcbytes;	/* Reuse junk fields for 32 bit */
	unsigned long  msg_lqbytes;	/* ditto */
	unsigned short msg_cbytes;	/* current number of bytes on queue */
	unsigned short msg_qnum;	/* number of messages in queue */
	unsigned short msg_qbytes;	/* max number of bytes on queue */
	__lkl__kernel_ipc_pid_t msg_lspid;	/* pid of last msgsnd */
	__lkl__kernel_ipc_pid_t msg_lrpid;	/* last receive pid */
};

/* Include the definition of msqid64_ds */
#include <lkl/asm/msgbuf.h>

/* message buffer for msgsnd and msgrcv calls */
struct lkl_msgbuf {
	__lkl__kernel_long_t mtype;          /* type of message */
	char mtext[1];                  /* message text */
};

/* buffer for msgctl calls LKL_IPC_INFO, LKL_MSG_INFO */
struct lkl_msginfo {
	int msgpool;
	int msgmap; 
	int msgmax; 
	int msgmnb; 
	int msgmni; 
	int msgssz; 
	int msgtql; 
	unsigned short  msgseg; 
};

/*
 * LKL_MSGMNI, LKL_MSGMAX and LKL_MSGMNB are default values which can be
 * modified by sysctl.
 *
 * LKL_MSGMNI is the upper limit for the number of messages queues per
 * namespace.
 * It has been chosen to be as large possible without facilitating
 * scenarios where userspace causes overflows when adjusting the limits via
 * operations of the form retrieve current limit; add X; update limit".
 *
 * LKL_MSGMNB is the default size of a new message queue. Non-root tasks can
 * decrease the size with msgctl(LKL_IPC_SET), root tasks
 * (actually: LKL_CAP_SYS_RESOURCE) can both increase and decrease the queue
 * size. The optimal value is application dependent.
 * 16384 is used because it was always used (since 0.99.10)
 *
 * MAXMAX is the maximum size of an individual message, it's a global
 * (per-namespace) limit that applies for all message queues.
 * It's set to 1/2 of LKL_MSGMNB, to ensure that at least two messages fit into
 * the queue. This is also an arbitrary choice (since 2.6.0).
 */

#define LKL_MSGMNI 32000   /* <= IPCMNI */     /* max # of msg queue identifiers */
#define LKL_MSGMAX  8192   /* <= INT_MAX */   /* max size of message (bytes) */
#define LKL_MSGMNB 16384   /* <= INT_MAX */   /* default max size of a message queue */

/* unused */
#define LKL_MSGPOOL (LKL_MSGMNI * LKL_MSGMNB / 1024) /* size in kbytes of message pool */
#define LKL_MSGTQL  LKL_MSGMNB            /* number of system message headers */
#define LKL_MSGMAP  LKL_MSGMNB            /* number of entries in message map */
#define LKL_MSGSSZ  16                /* message segment size */
#define __LKL__MSGSEG ((LKL_MSGPOOL * 1024) / LKL_MSGSSZ) /* max no. of segments */
#define LKL_MSGSEG (__LKL__MSGSEG <= 0xffff ? __LKL__MSGSEG : 0xffff)


#endif /* _LKL_LINUX_MSG_H */
