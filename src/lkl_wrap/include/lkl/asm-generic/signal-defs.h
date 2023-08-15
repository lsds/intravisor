/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_SIGNAL_DEFS_H
#define __LKL__ASM_GENERIC_SIGNAL_DEFS_H



/*
 * SA_FLAGS values:
 *
 * LKL_SA_NOCLDSTOP flag to turn off LKL_SIGCHLD when children stop.
 * LKL_SA_NOCLDWAIT flag on LKL_SIGCHLD to inhibit zombies.
 * LKL_SA_SIGINFO delivers the signal with SIGINFO structs.
 * LKL_SA_ONSTACK indicates that a registered lkl_stack_t will be used.
 * LKL_SA_RESTART flag to get restarting signals (which were the default long ago)
 * LKL_SA_NODEFER prevents the current signal from being masked in the handler.
 * LKL_SA_RESETHAND clears the handler when the signal is delivered.
 * LKL_SA_UNSUPPORTED is a flag bit that will never be supported. Kernels from
 * before the introduction of LKL_SA_UNSUPPORTED did not clear unknown bits from
 * sa_flags when read using the oldact argument to sigaction and rt_sigaction,
 * so this bit allows flag bit support to be detected from userspace while
 * allowing an old kernel to be distinguished from a kernel that supports every
 * flag bit.
 * LKL_SA_EXPOSE_TAGBITS exposes an architecture-defined set of tag bits in
 * siginfo.lkl_si_addr.
 *
 * LKL_SA_ONESHOT and LKL_SA_NOMASK are the historical Linux names for the Single
 * Unix names RESETHAND and NODEFER respectively.
 */
#ifndef LKL_SA_NOCLDSTOP
#define LKL_SA_NOCLDSTOP	0x00000001
#endif
#ifndef LKL_SA_NOCLDWAIT
#define LKL_SA_NOCLDWAIT	0x00000002
#endif
#ifndef LKL_SA_SIGINFO
#define LKL_SA_SIGINFO	0x00000004
#endif
/* 0x00000008 used on alpha, mips, parisc */
/* 0x00000010 used on alpha, parisc */
/* 0x00000020 used on alpha, parisc, sparc */
/* 0x00000040 used on alpha, parisc */
/* 0x00000080 used on parisc */
/* 0x00000100 used on sparc */
/* 0x00000200 used on sparc */
#define LKL_SA_UNSUPPORTED	0x00000400
#define LKL_SA_EXPOSE_TAGBITS	0x00000800
/* 0x00010000 used on mips */
/* 0x00800000 used for internal SA_IMMUTABLE */
/* 0x01000000 used on x86 */
/* 0x02000000 used on x86 */
/*
 * New architectures should not define the obsolete
 *	SA_RESTORER	0x04000000
 */
#ifndef LKL_SA_ONSTACK
#define LKL_SA_ONSTACK	0x08000000
#endif
#ifndef LKL_SA_RESTART
#define LKL_SA_RESTART	0x10000000
#endif
#ifndef LKL_SA_NODEFER
#define LKL_SA_NODEFER	0x40000000
#endif
#ifndef LKL_SA_RESETHAND
#define LKL_SA_RESETHAND	0x80000000
#endif

#define LKL_SA_NOMASK	LKL_SA_NODEFER
#define LKL_SA_ONESHOT	LKL_SA_RESETHAND

#ifndef LKL_SIG_BLOCK
#define LKL_SIG_BLOCK          0	/* for blocking signals */
#endif
#ifndef LKL_SIG_UNBLOCK
#define LKL_SIG_UNBLOCK        1	/* for unblocking signals */
#endif
#ifndef LKL_SIG_SETMASK
#define LKL_SIG_SETMASK        2	/* for setting the signal mask */
#endif

#ifndef __ASSEMBLY__
typedef void __lkl__signalfn_t(int);
typedef __lkl__signalfn_t *__lkl__sighandler_t;

typedef void __lkl__restorefn_t(void);
typedef __lkl__restorefn_t *__lkl__sigrestore_t;

#define LKL_SIG_DFL	((__lkl__sighandler_t)0)	/* default signal handling */
#define LKL_SIG_IGN	((__lkl__sighandler_t)1)	/* ignore signal */
#define LKL_SIG_ERR	((__lkl__sighandler_t)-1)	/* error return from signal */
#endif

#endif /* __LKL__ASM_GENERIC_SIGNAL_DEFS_H */
