/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef __LKL__ASM_GENERIC_SIGNAL_DEFS_H
#define __LKL__ASM_GENERIC_SIGNAL_DEFS_H



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
