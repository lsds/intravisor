/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_SIGNAL_H
#define __LKL__ASM_GENERIC_SIGNAL_H

#include <lkl/linux/types.h>

#define _LKL_NSIG		64
#define _LKL_NSIG_BPW	__LKL__BITS_PER_LONG
#define _LKL_NSIG_WORDS	(_LKL_NSIG / _LKL_NSIG_BPW)

#define LKL_SIGHUP		 1
#define LKL_SIGINT		 2
#define LKL_SIGQUIT		 3
#define LKL_SIGILL		 4
#define LKL_SIGTRAP		 5
#define LKL_SIGABRT		 6
#define LKL_SIGIOT		 6
#define LKL_SIGBUS		 7
#define LKL_SIGFPE		 8
#define LKL_SIGKILL		 9
#define LKL_SIGUSR1		10
#define LKL_SIGSEGV		11
#define LKL_SIGUSR2		12
#define LKL_SIGPIPE		13
#define LKL_SIGALRM		14
#define LKL_SIGTERM		15
#define LKL_SIGSTKFLT	16
#define LKL_SIGCHLD		17
#define LKL_SIGCONT		18
#define LKL_SIGSTOP		19
#define LKL_SIGTSTP		20
#define LKL_SIGTTIN		21
#define LKL_SIGTTOU		22
#define LKL_SIGURG		23
#define LKL_SIGXCPU		24
#define LKL_SIGXFSZ		25
#define LKL_SIGVTALRM	26
#define LKL_SIGPROF		27
#define LKL_SIGWINCH	28
#define LKL_SIGIO		29
#define LKL_SIGPOLL		LKL_SIGIO
/*
#define LKL_SIGLOST		29
*/
#define LKL_SIGPWR		30
#define LKL_SIGSYS		31
#define	LKL_SIGUNUSED	31

/* These should not be considered constants from userland.  */
#define LKL_SIGRTMIN	32
#ifndef LKL_SIGRTMAX
#define LKL_SIGRTMAX	_LKL_NSIG
#endif

/*
 * SA_FLAGS values:
 *
 * LKL_SA_ONSTACK indicates that a registered lkl_stack_t will be used.
 * LKL_SA_RESTART flag to get restarting signals (which were the default long ago)
 * LKL_SA_NOCLDSTOP flag to turn off LKL_SIGCHLD when children stop.
 * LKL_SA_RESETHAND clears the handler when the signal is delivered.
 * LKL_SA_NOCLDWAIT flag on LKL_SIGCHLD to inhibit zombies.
 * LKL_SA_NODEFER prevents the current signal from being masked in the handler.
 *
 * LKL_SA_ONESHOT and LKL_SA_NOMASK are the historical Linux names for the Single
 * Unix names RESETHAND and NODEFER respectively.
 */
#define LKL_SA_NOCLDSTOP	0x00000001
#define LKL_SA_NOCLDWAIT	0x00000002
#define LKL_SA_SIGINFO	0x00000004
#define LKL_SA_ONSTACK	0x08000000
#define LKL_SA_RESTART	0x10000000
#define LKL_SA_NODEFER	0x40000000
#define LKL_SA_RESETHAND	0x80000000

#define LKL_SA_NOMASK	LKL_SA_NODEFER
#define LKL_SA_ONESHOT	LKL_SA_RESETHAND

/*
 * New architectures should not define the obsolete
 *	SA_RESTORER	0x04000000
 */

#if !defined LKL_MINSIGSTKSZ || !defined LKL_SIGSTKSZ
#define LKL_MINSIGSTKSZ	2048
#define LKL_SIGSTKSZ	8192
#endif

#ifndef __ASSEMBLY__
typedef struct {
	unsigned long sig[_LKL_NSIG_WORDS];
} lkl_sigset_t;

/* not actually used, but required for linux/syscalls.h */
typedef unsigned long lkl_old_sigset_t;

#include <lkl/asm-generic/signal-defs.h>

#ifdef SA_RESTORER
#define __LKL__ARCH_HAS_SA_RESTORER
#endif

struct lkl_sigaction {
	__lkl__sighandler_t lkl_sa_handler;
	unsigned long sa_flags;
#ifdef SA_RESTORER
	__lkl__sigrestore_t sa_restorer;
#endif
	lkl_sigset_t sa_mask;		/* mask last for extensibility */
};

typedef struct lkl_sigaltstack {
	void *ss_sp;
	int ss_flags;
	lkl_size_t ss_size;
} lkl_stack_t;

#endif /* __ASSEMBLY__ */

#endif /* __LKL__ASM_GENERIC_SIGNAL_H */
