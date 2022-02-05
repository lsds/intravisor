/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_SEM_H
#define _LKL_LINUX_SEM_H

#include <lkl/linux/ipc.h>

/* semop flags */
#define LKL_SEM_UNDO        0x1000  /* undo the operation on exit */

/* semctl Command Definitions. */
#define LKL_GETPID  11       /* get sempid */
#define LKL_GETVAL  12       /* get semval */
#define LKL_GETALL  13       /* get all semval's */
#define LKL_GETNCNT 14       /* get semncnt */
#define LKL_GETZCNT 15       /* get semzcnt */
#define LKL_SETVAL  16       /* set semval */
#define LKL_SETALL  17       /* set all semval's */

/* ipcs ctl cmds */
#define LKL_SEM_STAT 18
#define LKL_SEM_INFO 19
#define LKL_SEM_STAT_ANY 20

/* Obsolete, used only for backwards compatibility and libc5 compiles */
struct lkl_semid_ds {
	struct ipc_perm	sem_perm;		/* permissions .. see ipc.h */
	__lkl__kernel_time_t	sem_otime;		/* last semop time */
	__lkl__kernel_time_t	sem_ctime;		/* create/last semctl() time */
	struct sem	*sem_base;		/* ptr to first semaphore in array */
	struct sem_queue *sem_pending;		/* pending operations to be processed */
	struct sem_queue **sem_pending_last;	/* last pending operation */
	struct sem_undo	*undo;			/* undo requests on this array */
	unsigned short	sem_nsems;		/* no. of semaphores in array */
};

/* Include the definition of semid64_ds */
#include <lkl/asm/sembuf.h>

/* semop system calls takes an array of these. */
struct lkl_sembuf {
	unsigned short  sem_num;	/* semaphore index in array */
	short		sem_op;		/* semaphore operation */
	short		sem_flg;	/* operation flags */
};

/* arg for semctl system calls. */
union lkl_semun {
	int val;			/* value for LKL_SETVAL */
	struct lkl_semid_ds *buf;	/* buffer for LKL_IPC_STAT & LKL_IPC_SET */
	unsigned short *array;	/* array for LKL_GETALL & LKL_SETALL */
	struct lkl_seminfo *__buf;	/* buffer for LKL_IPC_INFO */
	void *__pad;
};

struct  lkl_seminfo {
	int semmap;
	int semmni;
	int semmns;
	int semmnu;
	int semmsl;
	int semopm;
	int semume;
	int semusz;
	int semvmx;
	int semaem;
};

/*
 * LKL_SEMMNI, LKL_SEMMSL and LKL_SEMMNS are default values which can be
 * modified by sysctl.
 * The values has been chosen to be larger than necessary for any
 * known configuration.
 *
 * LKL_SEMOPM should not be increased beyond 1000, otherwise there is the
 * risk that semop()/semtimedop() fails due to kernel memory fragmentation when
 * allocating the sop array.
 */


#define LKL_SEMMNI  32000           /* <= IPCMNI  max # of semaphore identifiers */
#define LKL_SEMMSL  32000           /* <= INT_MAX max num of semaphores per id */
#define LKL_SEMMNS  (LKL_SEMMNI*LKL_SEMMSL) /* <= INT_MAX max # of semaphores in system */
#define LKL_SEMOPM  500	        /* <= 1 000 max num of ops per semop call */
#define LKL_SEMVMX  32767           /* <= 32767 semaphore maximum value */
#define LKL_SEMAEM  LKL_SEMVMX          /* adjust on exit max value */

/* unused */
#define LKL_SEMUME  LKL_SEMOPM          /* max num of undo entries per process */
#define LKL_SEMMNU  LKL_SEMMNS          /* num of undo structures system wide */
#define LKL_SEMMAP  LKL_SEMMNS          /* # of entries in semaphore map */
#define LKL_SEMUSZ  20		/* sizeof struct sem_undo */


#endif /* _LKL_LINUX_SEM_H */
