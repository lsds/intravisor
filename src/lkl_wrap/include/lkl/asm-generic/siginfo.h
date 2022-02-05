/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_ASM_GENERIC_SIGINFO_H
#define _LKL_ASM_GENERIC_SIGINFO_H


#include <lkl/linux/types.h>

typedef union lkl_sigval {
	int sival_int;
	void *sival_ptr;
} lkl_sigval_t;

/*
 * This is the size (including padding) of the part of the
 * struct lkl_siginfo that is before the union.
 */
#ifndef __LKL__ARCH_SI_PREAMBLE_SIZE
#define __LKL__ARCH_SI_PREAMBLE_SIZE	(3 * sizeof(int))
#endif

#define LKL_SI_MAX_SIZE	128
#ifndef LKL_SI_PAD_SIZE
#define LKL_SI_PAD_SIZE	((LKL_SI_MAX_SIZE - __LKL__ARCH_SI_PREAMBLE_SIZE) / sizeof(int))
#endif

/*
 * The default "lkl_si_band" type is "long", as specified by POSIX.
 * However, some architectures want to override this to "int"
 * for historical compatibility reasons, so we allow that.
 */
#ifndef __LKL__ARCH_SI_BAND_T
#define __LKL__ARCH_SI_BAND_T long
#endif

#ifndef __LKL__ARCH_SI_CLOCK_T
#define __LKL__ARCH_SI_CLOCK_T __lkl__kernel_clock_t
#endif

#ifndef __LKL__ARCH_SI_ATTRIBUTES
#define __LKL__ARCH_SI_ATTRIBUTES
#endif

typedef struct lkl_siginfo {
	int si_signo;
#ifndef __ARCH_HAS_SWAPPED_SIGINFO
	int si_errno;
	int si_code;
#else
	int si_code;
	int si_errno;
#endif

	union {
		int _pad[LKL_SI_PAD_SIZE];

		/* kill() */
		struct {
			__lkl__kernel_pid_t _pid;	/* sender's pid */
			__lkl__kernel_uid32_t _uid;	/* sender's uid */
		} _kill;

		/* POSIX.1b timers */
		struct {
			__lkl__kernel_timer_t _tid;	/* timer id */
			int _overrun;		/* overrun count */
			lkl_sigval_t _sigval;	/* same as below */
			int _sys_private;       /* not to be passed to user */
		} _timer;

		/* POSIX.1b signals */
		struct {
			__lkl__kernel_pid_t _pid;	/* sender's pid */
			__lkl__kernel_uid32_t _uid;	/* sender's uid */
			lkl_sigval_t _sigval;
		} _rt;

		/* LKL_SIGCHLD */
		struct {
			__lkl__kernel_pid_t _pid;	/* which child */
			__lkl__kernel_uid32_t _uid;	/* sender's uid */
			int _status;		/* exit code */
			__LKL__ARCH_SI_CLOCK_T _utime;
			__LKL__ARCH_SI_CLOCK_T _stime;
		} _sigchld;

		/* LKL_SIGILL, LKL_SIGFPE, LKL_SIGSEGV, LKL_SIGBUS, LKL_SIGTRAP, SIGEMT */
		struct {
			void *_addr; /* faulting insn/memory ref. */
#ifdef __ARCH_SI_TRAPNO
			int _trapno;	/* TRAP # which caused the signal */
#endif
#ifdef __ia64__
			int _imm;		/* immediate value for "break" */
			unsigned int _flags;	/* see ia64 si_flags */
			unsigned long _isr;	/* isr */
#endif

#define __LKL__ADDR_BND_PKEY_PAD  (__alignof__(void *) < sizeof(short) ? \
			      sizeof(short) : __alignof__(void *))
			union {
				/*
				 * used when si_code=LKL_BUS_MCEERR_AR or
				 * used when si_code=LKL_BUS_MCEERR_AO
				 */
				short _addr_lsb; /* LSB of the reported address */
				/* used when si_code=LKL_SEGV_BNDERR */
				struct {
					char _dummy_bnd[__LKL__ADDR_BND_PKEY_PAD];
					void *_lower;
					void *_upper;
				} _addr_bnd;
				/* used when si_code=LKL_SEGV_PKUERR */
				struct {
					char _dummy_pkey[__LKL__ADDR_BND_PKEY_PAD];
					__lkl__u32 _pkey;
				} _addr_pkey;
			};
		} _sigfault;

		/* LKL_SIGPOLL */
		struct {
			__LKL__ARCH_SI_BAND_T _band;	/* LKL_POLL_IN, LKL_POLL_OUT, LKL_POLL_MSG */
			int _fd;
		} _sigpoll;

		/* LKL_SIGSYS */
		struct {
			void *_call_addr; /* calling user insn */
			int _syscall;	/* triggering system call number */
			unsigned int _arch;	/* AUDIT_ARCH_* of syscall */
		} _sigsys;
	} _sifields;
} __LKL__ARCH_SI_ATTRIBUTES lkl_siginfo_t;

/*
 * How these fields are to be accessed.
 */
#define lkl_si_pid		_sifields._kill._pid
#define lkl_si_uid		_sifields._kill._uid
#define lkl_si_tid		_sifields._timer._tid
#define lkl_si_overrun	_sifields._timer._overrun
#define lkl_si_sys_private  _sifields._timer._sys_private
#define lkl_si_status	_sifields._sigchld._status
#define lkl_si_utime	_sifields._sigchld._utime
#define lkl_si_stime	_sifields._sigchld._stime
#define lkl_si_value	_sifields._rt._sigval
#define lkl_si_int		_sifields._rt._sigval.sival_int
#define lkl_si_ptr		_sifields._rt._sigval.sival_ptr
#define lkl_si_addr		_sifields._sigfault._addr
#ifdef __ARCH_SI_TRAPNO
#define lkl_si_trapno	_sifields._sigfault._trapno
#endif
#define lkl_si_addr_lsb	_sifields._sigfault._addr_lsb
#define lkl_si_lower	_sifields._sigfault._addr_bnd._lower
#define lkl_si_upper	_sifields._sigfault._addr_bnd._upper
#define lkl_si_pkey		_sifields._sigfault._addr_pkey._pkey
#define lkl_si_band		_sifields._sigpoll._band
#define lkl_si_fd		_sifields._sigpoll._fd
#define lkl_si_call_addr	_sifields._sigsys._call_addr
#define lkl_si_syscall	_sifields._sigsys._syscall
#define lkl_si_arch		_sifields._sigsys._arch

/*
 * si_code values
 * Digital reserves positive values for kernel-generated signals.
 */
#define LKL_SI_USER		0		/* sent by kill, sigsend, raise */
#define LKL_SI_KERNEL	0x80		/* sent by the kernel from somewhere */
#define LKL_SI_QUEUE	-1		/* sent by sigqueue */
#define LKL_SI_TIMER	-2		/* sent by timer expiration */
#define LKL_SI_MESGQ	-3		/* sent by real time mesq state change */
#define LKL_SI_ASYNCIO	-4		/* sent by AIO completion */
#define LKL_SI_SIGIO	-5		/* sent by queued LKL_SIGIO */
#define LKL_SI_TKILL	-6		/* sent by tkill system call */
#define LKL_SI_DETHREAD	-7		/* sent by execve() killing subsidiary threads */
#define LKL_SI_ASYNCNL	-60		/* sent by glibc async name lookup completion */

#define LKL_SI_FROMUSER(siptr)	((siptr)->si_code <= 0)
#define LKL_SI_FROMKERNEL(siptr)	((siptr)->si_code > 0)

/*
 * LKL_SIGILL si_codes
 */
#define LKL_ILL_ILLOPC	1	/* illegal opcode */
#define LKL_ILL_ILLOPN	2	/* illegal operand */
#define LKL_ILL_ILLADR	3	/* illegal addressing mode */
#define LKL_ILL_ILLTRP	4	/* illegal trap */
#define LKL_ILL_PRVOPC	5	/* privileged opcode */
#define LKL_ILL_PRVREG	6	/* privileged register */
#define LKL_ILL_COPROC	7	/* coprocessor error */
#define LKL_ILL_BADSTK	8	/* internal stack error */
#define LKL_ILL_BADIADDR	9	/* unimplemented instruction address */
#define __LKL__ILL_BREAK	10	/* illegal break */
#define __LKL__ILL_BNDMOD	11	/* bundle-update (modification) in progress */
#define LKL_NSIGILL		11

/*
 * LKL_SIGFPE si_codes
 */
#define LKL_FPE_INTDIV	1	/* integer divide by zero */
#define LKL_FPE_INTOVF	2	/* integer overflow */
#define LKL_FPE_FLTDIV	3	/* floating point divide by zero */
#define LKL_FPE_FLTOVF	4	/* floating point overflow */
#define LKL_FPE_FLTUND	5	/* floating point underflow */
#define LKL_FPE_FLTRES	6	/* floating point inexact result */
#define LKL_FPE_FLTINV	7	/* floating point invalid operation */
#define LKL_FPE_FLTSUB	8	/* subscript out of range */
#define __LKL__FPE_DECOVF	9	/* decimal overflow */
#define __LKL__FPE_DECDIV	10	/* decimal division by zero */
#define __LKL__FPE_DECERR	11	/* packed decimal error */
#define __LKL__FPE_INVASC	12	/* invalid ASCII digit */
#define __LKL__FPE_INVDEC	13	/* invalid decimal digit */
#define LKL_FPE_FLTUNK	14	/* undiagnosed floating-point exception */
#define LKL_FPE_CONDTRAP	15	/* trap on condition */
#define LKL_NSIGFPE		15

/*
 * LKL_SIGSEGV si_codes
 */
#define LKL_SEGV_MAPERR	1	/* address not mapped to object */
#define LKL_SEGV_ACCERR	2	/* invalid permissions for mapped object */
#define LKL_SEGV_BNDERR	3	/* failed address bound checks */
#ifdef __ia64__
# define __LKL__SEGV_PSTKOVF	4	/* paragraph stack overflow */
#else
# define LKL_SEGV_PKUERR	4	/* failed protection key checks */
#endif
#define LKL_SEGV_ACCADI	5	/* ADI not enabled for mapped object */
#define LKL_SEGV_ADIDERR	6	/* Disrupting MCD error */
#define LKL_SEGV_ADIPERR	7	/* Precise MCD exception */
#define LKL_NSIGSEGV	7

/*
 * LKL_SIGBUS si_codes
 */
#define LKL_BUS_ADRALN	1	/* invalid address alignment */
#define LKL_BUS_ADRERR	2	/* non-existent physical address */
#define LKL_BUS_OBJERR	3	/* object specific hardware error */
/* hardware memory error consumed on a machine check: action required */
#define LKL_BUS_MCEERR_AR	4
/* hardware memory error detected in process but not consumed: action optional*/
#define LKL_BUS_MCEERR_AO	5
#define LKL_NSIGBUS		5

/*
 * LKL_SIGTRAP si_codes
 */
#define LKL_TRAP_BRKPT	1	/* process breakpoint */
#define LKL_TRAP_TRACE	2	/* process trace trap */
#define LKL_TRAP_BRANCH     3	/* process taken branch trap */
#define LKL_TRAP_HWBKPT     4	/* hardware breakpoint/watchpoint */
#define LKL_NSIGTRAP	4

/*
 * There is an additional set of LKL_SIGTRAP si_codes used by ptrace
 * that are of the form: ((PTRACE_EVENT_XXX << 8) | LKL_SIGTRAP)
 */

/*
 * LKL_SIGCHLD si_codes
 */
#define LKL_CLD_EXITED	1	/* child has exited */
#define LKL_CLD_KILLED	2	/* child was killed */
#define LKL_CLD_DUMPED	3	/* child terminated abnormally */
#define LKL_CLD_TRAPPED	4	/* traced child has trapped */
#define LKL_CLD_STOPPED	5	/* child has stopped */
#define LKL_CLD_CONTINUED	6	/* stopped child has continued */
#define LKL_NSIGCHLD	6

/*
 * LKL_SIGPOLL (or any other signal without signal specific si_codes) si_codes
 */
#define LKL_POLL_IN		1	/* data input available */
#define LKL_POLL_OUT	2	/* output buffers available */
#define LKL_POLL_MSG	3	/* input message available */
#define LKL_POLL_ERR	4	/* i/o error */
#define LKL_POLL_PRI	5	/* high priority input available */
#define LKL_POLL_HUP	6	/* device disconnected */
#define LKL_NSIGPOLL	6

/*
 * LKL_SIGSYS si_codes
 */
#define LKL_SYS_SECCOMP	1	/* seccomp triggered */
#define LKL_NSIGSYS		1

/*
 * sigevent definitions
 * 
 * It seems likely that LKL_SIGEV_THREAD will have to be handled from 
 * userspace, libpthread transmuting it to LKL_SIGEV_SIGNAL, which the
 * thread manager then catches and does the appropriate nonsense.
 * However, everything is written out here so as to not get lost.
 */
#define LKL_SIGEV_SIGNAL	0	/* notify via signal */
#define LKL_SIGEV_NONE	1	/* other notification: meaningless */
#define LKL_SIGEV_THREAD	2	/* deliver via thread creation */
#define LKL_SIGEV_THREAD_ID 4	/* deliver to thread */

/*
 * This works because the alignment is ok on all current architectures
 * but we leave open this being overridden in the future
 */
#ifndef __LKL__ARCH_SIGEV_PREAMBLE_SIZE
#define __LKL__ARCH_SIGEV_PREAMBLE_SIZE	(sizeof(int) * 2 + sizeof(lkl_sigval_t))
#endif

#define LKL_SIGEV_MAX_SIZE	64
#define LKL_SIGEV_PAD_SIZE	((LKL_SIGEV_MAX_SIZE - __LKL__ARCH_SIGEV_PREAMBLE_SIZE) \
		/ sizeof(int))

typedef struct lkl_sigevent {
	lkl_sigval_t sigev_value;
	int sigev_signo;
	int sigev_notify;
	union {
		int _pad[LKL_SIGEV_PAD_SIZE];
		 int _tid;

		struct {
			void (*_function)(lkl_sigval_t);
			void *_attribute;	/* really pthread_attr_t */
		} _sigev_thread;
	} _sigev_un;
} lkl_sigevent_t;

#define lkl_sigev_notify_function	_sigev_un._sigev_thread._function
#define lkl_sigev_notify_attributes	_sigev_un._sigev_thread._attribute
#define lkl_sigev_notify_thread_id	 _sigev_un._tid


#endif /* _LKL_ASM_GENERIC_SIGINFO_H */
