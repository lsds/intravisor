/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#include <lkl/asm/bitsperlong.h>

/*
 * This file contains the system call numbers, based on the
 * layout of the x86-64 architecture, which embeds the
 * pointer to the syscall in the table.
 *
 * As a basic principle, no duplication of functionality
 * should be added, e.g. we don't use lseek when llseek
 * is present. New architectures should use this file
 * and implement the less feature-full calls in user space.
 */

#ifndef __LKL__SYSCALL
#define __LKL__SYSCALL(x, y)
#endif

#if __LKL__BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)
#define __LKL__SC_3264(_nr, _32, _64) __LKL__SYSCALL(_nr, _32)
#else
#define __LKL__SC_3264(_nr, _32, _64) __LKL__SYSCALL(_nr, _64)
#endif

#ifdef __SYSCALL_COMPAT
#define __LKL__SC_COMP(_nr, _sys, _comp) __LKL__SYSCALL(_nr, _comp)
#define __LKL__SC_COMP_3264(_nr, _32, _64, _comp) __LKL__SYSCALL(_nr, _comp)
#else
#define __LKL__SC_COMP(_nr, _sys, _comp) __LKL__SYSCALL(_nr, _sys)
#define __LKL__SC_COMP_3264(_nr, _32, _64, _comp) __LKL__SC_3264(_nr, _32, _64)
#endif

#define __lkl__NR_io_setup 0
__LKL__SC_COMP(__lkl__NR_io_setup, sys_io_setup, compat_sys_io_setup)
#define __lkl__NR_io_destroy 1
__LKL__SYSCALL(__lkl__NR_io_destroy, sys_io_destroy)
#define __lkl__NR_io_submit 2
__LKL__SC_COMP(__lkl__NR_io_submit, sys_io_submit, compat_sys_io_submit)
#define __lkl__NR_io_cancel 3
__LKL__SYSCALL(__lkl__NR_io_cancel, sys_io_cancel)
#define __lkl__NR_io_getevents 4
__LKL__SC_COMP(__lkl__NR_io_getevents, sys_io_getevents, compat_sys_io_getevents)

/* fs/xattr.c */
#define __lkl__NR_setxattr 5
__LKL__SYSCALL(__lkl__NR_setxattr, sys_setxattr)
#define __lkl__NR_lsetxattr 6
__LKL__SYSCALL(__lkl__NR_lsetxattr, sys_lsetxattr)
#define __lkl__NR_fsetxattr 7
__LKL__SYSCALL(__lkl__NR_fsetxattr, sys_fsetxattr)
#define __lkl__NR_getxattr 8
__LKL__SYSCALL(__lkl__NR_getxattr, sys_getxattr)
#define __lkl__NR_lgetxattr 9
__LKL__SYSCALL(__lkl__NR_lgetxattr, sys_lgetxattr)
#define __lkl__NR_fgetxattr 10
__LKL__SYSCALL(__lkl__NR_fgetxattr, sys_fgetxattr)
#define __lkl__NR_listxattr 11
__LKL__SYSCALL(__lkl__NR_listxattr, sys_listxattr)
#define __lkl__NR_llistxattr 12
__LKL__SYSCALL(__lkl__NR_llistxattr, sys_llistxattr)
#define __lkl__NR_flistxattr 13
__LKL__SYSCALL(__lkl__NR_flistxattr, sys_flistxattr)
#define __lkl__NR_removexattr 14
__LKL__SYSCALL(__lkl__NR_removexattr, sys_removexattr)
#define __lkl__NR_lremovexattr 15
__LKL__SYSCALL(__lkl__NR_lremovexattr, sys_lremovexattr)
#define __lkl__NR_fremovexattr 16
__LKL__SYSCALL(__lkl__NR_fremovexattr, sys_fremovexattr)

/* fs/dcache.c */
#define __lkl__NR_getcwd 17
__LKL__SYSCALL(__lkl__NR_getcwd, sys_getcwd)

/* fs/cookies.c */
#define __lkl__NR_lookup_dcookie 18
__LKL__SC_COMP(__lkl__NR_lookup_dcookie, sys_lookup_dcookie, compat_sys_lookup_dcookie)

/* fs/eventfd.c */
#define __lkl__NR_eventfd2 19
__LKL__SYSCALL(__lkl__NR_eventfd2, sys_eventfd2)

/* fs/eventpoll.c */
#define __lkl__NR_epoll_create1 20
__LKL__SYSCALL(__lkl__NR_epoll_create1, sys_epoll_create1)
#define __lkl__NR_epoll_ctl 21
__LKL__SYSCALL(__lkl__NR_epoll_ctl, sys_epoll_ctl)
#define __lkl__NR_epoll_pwait 22
__LKL__SC_COMP(__lkl__NR_epoll_pwait, sys_epoll_pwait, compat_sys_epoll_pwait)

/* fs/fcntl.c */
#define __lkl__NR_dup 23
__LKL__SYSCALL(__lkl__NR_dup, sys_dup)
#define __lkl__NR_dup3 24
__LKL__SYSCALL(__lkl__NR_dup3, sys_dup3)
#define __lkl__NR3264_fcntl 25
__LKL__SC_COMP_3264(__lkl__NR3264_fcntl, sys_fcntl64, sys_fcntl, compat_sys_fcntl64)

/* fs/inotify_user.c */
#define __lkl__NR_inotify_init1 26
__LKL__SYSCALL(__lkl__NR_inotify_init1, sys_inotify_init1)
#define __lkl__NR_inotify_add_watch 27
__LKL__SYSCALL(__lkl__NR_inotify_add_watch, sys_inotify_add_watch)
#define __lkl__NR_inotify_rm_watch 28
__LKL__SYSCALL(__lkl__NR_inotify_rm_watch, sys_inotify_rm_watch)

/* fs/ioctl.c */
#define __lkl__NR_ioctl 29
__LKL__SC_COMP(__lkl__NR_ioctl, sys_ioctl, compat_sys_ioctl)

/* fs/ioprio.c */
#define __lkl__NR_ioprio_set 30
__LKL__SYSCALL(__lkl__NR_ioprio_set, sys_ioprio_set)
#define __lkl__NR_ioprio_get 31
__LKL__SYSCALL(__lkl__NR_ioprio_get, sys_ioprio_get)

/* fs/locks.c */
#define __lkl__NR_flock 32
__LKL__SYSCALL(__lkl__NR_flock, sys_flock)

/* fs/namei.c */
#define __lkl__NR_mknodat 33
__LKL__SYSCALL(__lkl__NR_mknodat, sys_mknodat)
#define __lkl__NR_mkdirat 34
__LKL__SYSCALL(__lkl__NR_mkdirat, sys_mkdirat)
#define __lkl__NR_unlinkat 35
__LKL__SYSCALL(__lkl__NR_unlinkat, sys_unlinkat)
#define __lkl__NR_symlinkat 36
__LKL__SYSCALL(__lkl__NR_symlinkat, sys_symlinkat)
#define __lkl__NR_linkat 37
__LKL__SYSCALL(__lkl__NR_linkat, sys_linkat)
#ifdef __LKL__ARCH_WANT_RENAMEAT
/* renameat is superseded with flags by renameat2 */
#define __lkl__NR_renameat 38
__LKL__SYSCALL(__lkl__NR_renameat, sys_renameat)
#endif /* __LKL__ARCH_WANT_RENAMEAT */

/* fs/namespace.c */
#define __lkl__NR_umount2 39
__LKL__SYSCALL(__lkl__NR_umount2, sys_umount)
#define __lkl__NR_mount 40
__LKL__SC_COMP(__lkl__NR_mount, sys_mount, compat_sys_mount)
#define __lkl__NR_pivot_root 41
__LKL__SYSCALL(__lkl__NR_pivot_root, sys_pivot_root)

/* fs/nfsctl.c */
#define __lkl__NR_nfsservctl 42
__LKL__SYSCALL(__lkl__NR_nfsservctl, sys_ni_syscall)

/* fs/open.c */
#define __lkl__NR3264_statfs 43
__LKL__SC_COMP_3264(__lkl__NR3264_statfs, sys_statfs64, sys_statfs, \
	       compat_sys_statfs64)
#define __lkl__NR3264_fstatfs 44
__LKL__SC_COMP_3264(__lkl__NR3264_fstatfs, sys_fstatfs64, sys_fstatfs, \
	       compat_sys_fstatfs64)
#define __lkl__NR3264_truncate 45
__LKL__SC_COMP_3264(__lkl__NR3264_truncate, sys_truncate64, sys_truncate, \
	       compat_sys_truncate64)
#define __lkl__NR3264_ftruncate 46
__LKL__SC_COMP_3264(__lkl__NR3264_ftruncate, sys_ftruncate64, sys_ftruncate, \
	       compat_sys_ftruncate64)

#define __lkl__NR_fallocate 47
__LKL__SC_COMP(__lkl__NR_fallocate, sys_fallocate, compat_sys_fallocate)
#define __lkl__NR_faccessat 48
__LKL__SYSCALL(__lkl__NR_faccessat, sys_faccessat)
#define __lkl__NR_chdir 49
__LKL__SYSCALL(__lkl__NR_chdir, sys_chdir)
#define __lkl__NR_fchdir 50
__LKL__SYSCALL(__lkl__NR_fchdir, sys_fchdir)
#define __lkl__NR_chroot 51
__LKL__SYSCALL(__lkl__NR_chroot, sys_chroot)
#define __lkl__NR_fchmod 52
__LKL__SYSCALL(__lkl__NR_fchmod, sys_fchmod)
#define __lkl__NR_fchmodat 53
__LKL__SYSCALL(__lkl__NR_fchmodat, sys_fchmodat)
#define __lkl__NR_fchownat 54
__LKL__SYSCALL(__lkl__NR_fchownat, sys_fchownat)
#define __lkl__NR_fchown 55
__LKL__SYSCALL(__lkl__NR_fchown, sys_fchown)
#define __lkl__NR_openat 56
__LKL__SC_COMP(__lkl__NR_openat, sys_openat, compat_sys_openat)
#define __lkl__NR_close 57
__LKL__SYSCALL(__lkl__NR_close, sys_close)
#define __lkl__NR_vhangup 58
__LKL__SYSCALL(__lkl__NR_vhangup, sys_vhangup)

/* fs/pipe.c */
#define __lkl__NR_pipe2 59
__LKL__SYSCALL(__lkl__NR_pipe2, sys_pipe2)

/* fs/quota.c */
#define __lkl__NR_quotactl 60
__LKL__SYSCALL(__lkl__NR_quotactl, sys_quotactl)

/* fs/readdir.c */
#define __lkl__NR_getdents64 61
__LKL__SYSCALL(__lkl__NR_getdents64, sys_getdents64)

/* fs/read_write.c */
#define __lkl__NR3264_lseek 62
__LKL__SC_3264(__lkl__NR3264_lseek, sys_llseek, sys_lseek)
#define __lkl__NR_read 63
__LKL__SYSCALL(__lkl__NR_read, sys_read)
#define __lkl__NR_write 64
__LKL__SYSCALL(__lkl__NR_write, sys_write)
#define __lkl__NR_readv 65
__LKL__SC_COMP(__lkl__NR_readv, sys_readv, compat_sys_readv)
#define __lkl__NR_writev 66
__LKL__SC_COMP(__lkl__NR_writev, sys_writev, compat_sys_writev)
#define __lkl__NR_pread64 67
__LKL__SC_COMP(__lkl__NR_pread64, sys_pread64, compat_sys_pread64)
#define __lkl__NR_pwrite64 68
__LKL__SC_COMP(__lkl__NR_pwrite64, sys_pwrite64, compat_sys_pwrite64)
#define __lkl__NR_preadv 69
__LKL__SC_COMP(__lkl__NR_preadv, sys_preadv, compat_sys_preadv)
#define __lkl__NR_pwritev 70
__LKL__SC_COMP(__lkl__NR_pwritev, sys_pwritev, compat_sys_pwritev)

/* fs/sendfile.c */
#define __lkl__NR3264_sendfile 71
__LKL__SYSCALL(__lkl__NR3264_sendfile, sys_sendfile64)

/* fs/select.c */
#define __lkl__NR_pselect6 72
__LKL__SC_COMP(__lkl__NR_pselect6, sys_pselect6, compat_sys_pselect6)
#define __lkl__NR_ppoll 73
__LKL__SC_COMP(__lkl__NR_ppoll, sys_ppoll, compat_sys_ppoll)

/* fs/signalfd.c */
#define __lkl__NR_signalfd4 74
__LKL__SC_COMP(__lkl__NR_signalfd4, sys_signalfd4, compat_sys_signalfd4)

/* fs/splice.c */
#define __lkl__NR_vmsplice 75
__LKL__SC_COMP(__lkl__NR_vmsplice, sys_vmsplice, compat_sys_vmsplice)
#define __lkl__NR_splice 76
__LKL__SYSCALL(__lkl__NR_splice, sys_splice)
#define __lkl__NR_tee 77
__LKL__SYSCALL(__lkl__NR_tee, sys_tee)

/* fs/stat.c */
#define __lkl__NR_readlinkat 78
__LKL__SYSCALL(__lkl__NR_readlinkat, sys_readlinkat)
#define __lkl__NR3264_fstatat 79
__LKL__SC_3264(__lkl__NR3264_fstatat, sys_fstatat64, sys_newfstatat)
#define __lkl__NR3264_fstat 80
__LKL__SC_3264(__lkl__NR3264_fstat, sys_fstat64, sys_newfstat)

/* fs/sync.c */
#define __lkl__NR_sync 81
__LKL__SYSCALL(__lkl__NR_sync, sys_sync)
#define __lkl__NR_fsync 82
__LKL__SYSCALL(__lkl__NR_fsync, sys_fsync)
#define __lkl__NR_fdatasync 83
__LKL__SYSCALL(__lkl__NR_fdatasync, sys_fdatasync)
#ifdef __ARCH_WANT_SYNC_FILE_RANGE2
#define __lkl__NR_sync_file_range2 84
__LKL__SC_COMP(__lkl__NR_sync_file_range2, sys_sync_file_range2, \
	  compat_sys_sync_file_range2)
#else
#define __lkl__NR_sync_file_range 84
__LKL__SC_COMP(__lkl__NR_sync_file_range, sys_sync_file_range, \
	  compat_sys_sync_file_range)
#endif

/* fs/timerfd.c */
#define __lkl__NR_timerfd_create 85
__LKL__SYSCALL(__lkl__NR_timerfd_create, sys_timerfd_create)
#define __lkl__NR_timerfd_settime 86
__LKL__SC_COMP(__lkl__NR_timerfd_settime, sys_timerfd_settime, \
	  compat_sys_timerfd_settime)
#define __lkl__NR_timerfd_gettime 87
__LKL__SC_COMP(__lkl__NR_timerfd_gettime, sys_timerfd_gettime, \
	  compat_sys_timerfd_gettime)

/* fs/utimes.c */
#define __lkl__NR_utimensat 88
__LKL__SC_COMP(__lkl__NR_utimensat, sys_utimensat, compat_sys_utimensat)

/* kernel/acct.c */
#define __lkl__NR_acct 89
__LKL__SYSCALL(__lkl__NR_acct, sys_acct)

/* kernel/capability.c */
#define __lkl__NR_capget 90
__LKL__SYSCALL(__lkl__NR_capget, sys_capget)
#define __lkl__NR_capset 91
__LKL__SYSCALL(__lkl__NR_capset, sys_capset)

/* kernel/exec_domain.c */
#define __lkl__NR_personality 92
__LKL__SYSCALL(__lkl__NR_personality, sys_personality)

/* kernel/exit.c */
#define __lkl__NR_exit 93
__LKL__SYSCALL(__lkl__NR_exit, sys_exit)
#define __lkl__NR_exit_group 94
__LKL__SYSCALL(__lkl__NR_exit_group, sys_exit_group)
#define __lkl__NR_waitid 95
__LKL__SC_COMP(__lkl__NR_waitid, sys_waitid, compat_sys_waitid)

/* kernel/fork.c */
#define __lkl__NR_set_tid_address 96
__LKL__SYSCALL(__lkl__NR_set_tid_address, sys_set_tid_address)
#define __lkl__NR_unshare 97
__LKL__SYSCALL(__lkl__NR_unshare, sys_unshare)

/* kernel/futex.c */
#define __lkl__NR_futex 98
__LKL__SC_COMP(__lkl__NR_futex, sys_futex, compat_sys_futex)
#define __lkl__NR_set_robust_list 99
__LKL__SC_COMP(__lkl__NR_set_robust_list, sys_set_robust_list, \
	  compat_sys_set_robust_list)
#define __lkl__NR_get_robust_list 100
__LKL__SC_COMP(__lkl__NR_get_robust_list, sys_get_robust_list, \
	  compat_sys_get_robust_list)

/* kernel/hrtimer.c */
#define __lkl__NR_nanosleep 101
__LKL__SC_COMP(__lkl__NR_nanosleep, sys_nanosleep, compat_sys_nanosleep)

/* kernel/itimer.c */
#define __lkl__NR_getitimer 102
__LKL__SC_COMP(__lkl__NR_getitimer, sys_getitimer, compat_sys_getitimer)
#define __lkl__NR_setitimer 103
__LKL__SC_COMP(__lkl__NR_setitimer, sys_setitimer, compat_sys_setitimer)

/* kernel/kexec.c */
#define __lkl__NR_kexec_load 104
__LKL__SC_COMP(__lkl__NR_kexec_load, sys_kexec_load, compat_sys_kexec_load)

/* kernel/module.c */
#define __lkl__NR_init_module 105
__LKL__SYSCALL(__lkl__NR_init_module, sys_init_module)
#define __lkl__NR_delete_module 106
__LKL__SYSCALL(__lkl__NR_delete_module, sys_delete_module)

/* kernel/posix-timers.c */
#define __lkl__NR_timer_create 107
__LKL__SC_COMP(__lkl__NR_timer_create, sys_timer_create, compat_sys_timer_create)
#define __lkl__NR_timer_gettime 108
__LKL__SC_COMP(__lkl__NR_timer_gettime, sys_timer_gettime, compat_sys_timer_gettime)
#define __lkl__NR_timer_getoverrun 109
__LKL__SYSCALL(__lkl__NR_timer_getoverrun, sys_timer_getoverrun)
#define __lkl__NR_timer_settime 110
__LKL__SC_COMP(__lkl__NR_timer_settime, sys_timer_settime, compat_sys_timer_settime)
#define __lkl__NR_timer_delete 111
__LKL__SYSCALL(__lkl__NR_timer_delete, sys_timer_delete)
#define __lkl__NR_clock_settime 112
__LKL__SC_COMP(__lkl__NR_clock_settime, sys_clock_settime, compat_sys_clock_settime)
#define __lkl__NR_clock_gettime 113
__LKL__SC_COMP(__lkl__NR_clock_gettime, sys_clock_gettime, compat_sys_clock_gettime)
#define __lkl__NR_clock_getres 114
__LKL__SC_COMP(__lkl__NR_clock_getres, sys_clock_getres, compat_sys_clock_getres)
#define __lkl__NR_clock_nanosleep 115
__LKL__SC_COMP(__lkl__NR_clock_nanosleep, sys_clock_nanosleep, \
	  compat_sys_clock_nanosleep)

/* kernel/printk.c */
#define __lkl__NR_syslog 116
__LKL__SYSCALL(__lkl__NR_syslog, sys_syslog)

/* kernel/ptrace.c */
#define __lkl__NR_ptrace 117
__LKL__SYSCALL(__lkl__NR_ptrace, sys_ptrace)

/* kernel/sched/core.c */
#define __lkl__NR_sched_setparam 118
__LKL__SYSCALL(__lkl__NR_sched_setparam, sys_sched_setparam)
#define __lkl__NR_sched_setscheduler 119
__LKL__SYSCALL(__lkl__NR_sched_setscheduler, sys_sched_setscheduler)
#define __lkl__NR_sched_getscheduler 120
__LKL__SYSCALL(__lkl__NR_sched_getscheduler, sys_sched_getscheduler)
#define __lkl__NR_sched_getparam 121
__LKL__SYSCALL(__lkl__NR_sched_getparam, sys_sched_getparam)
#define __lkl__NR_sched_setaffinity 122
__LKL__SC_COMP(__lkl__NR_sched_setaffinity, sys_sched_setaffinity, \
	  compat_sys_sched_setaffinity)
#define __lkl__NR_sched_getaffinity 123
__LKL__SC_COMP(__lkl__NR_sched_getaffinity, sys_sched_getaffinity, \
	  compat_sys_sched_getaffinity)
#define __lkl__NR_sched_yield 124
__LKL__SYSCALL(__lkl__NR_sched_yield, sys_sched_yield)
#define __lkl__NR_sched_get_priority_max 125
__LKL__SYSCALL(__lkl__NR_sched_get_priority_max, sys_sched_get_priority_max)
#define __lkl__NR_sched_get_priority_min 126
__LKL__SYSCALL(__lkl__NR_sched_get_priority_min, sys_sched_get_priority_min)
#define __lkl__NR_sched_rr_get_interval 127
__LKL__SC_COMP(__lkl__NR_sched_rr_get_interval, sys_sched_rr_get_interval, \
	  compat_sys_sched_rr_get_interval)

/* kernel/signal.c */
#define __lkl__NR_restart_syscall 128
__LKL__SYSCALL(__lkl__NR_restart_syscall, sys_restart_syscall)
#define __lkl__NR_kill 129
__LKL__SYSCALL(__lkl__NR_kill, sys_kill)
#define __lkl__NR_tkill 130
__LKL__SYSCALL(__lkl__NR_tkill, sys_tkill)
#define __lkl__NR_tgkill 131
__LKL__SYSCALL(__lkl__NR_tgkill, sys_tgkill)
#define __lkl__NR_sigaltstack 132
__LKL__SC_COMP(__lkl__NR_sigaltstack, sys_sigaltstack, compat_sys_sigaltstack)
#define __lkl__NR_rt_sigsuspend 133
__LKL__SC_COMP(__lkl__NR_rt_sigsuspend, sys_rt_sigsuspend, compat_sys_rt_sigsuspend)
#define __lkl__NR_rt_sigaction 134
__LKL__SC_COMP(__lkl__NR_rt_sigaction, sys_rt_sigaction, compat_sys_rt_sigaction)
#define __lkl__NR_rt_sigprocmask 135
__LKL__SC_COMP(__lkl__NR_rt_sigprocmask, sys_rt_sigprocmask, compat_sys_rt_sigprocmask)
#define __lkl__NR_rt_sigpending 136
__LKL__SC_COMP(__lkl__NR_rt_sigpending, sys_rt_sigpending, compat_sys_rt_sigpending)
#define __lkl__NR_rt_sigtimedwait 137
__LKL__SC_COMP(__lkl__NR_rt_sigtimedwait, sys_rt_sigtimedwait, \
	  compat_sys_rt_sigtimedwait)
#define __lkl__NR_rt_sigqueueinfo 138
__LKL__SC_COMP(__lkl__NR_rt_sigqueueinfo, sys_rt_sigqueueinfo, \
	  compat_sys_rt_sigqueueinfo)
#define __lkl__NR_rt_sigreturn 139
__LKL__SC_COMP(__lkl__NR_rt_sigreturn, sys_rt_sigreturn, compat_sys_rt_sigreturn)

/* kernel/sys.c */
#define __lkl__NR_setpriority 140
__LKL__SYSCALL(__lkl__NR_setpriority, sys_setpriority)
#define __lkl__NR_getpriority 141
__LKL__SYSCALL(__lkl__NR_getpriority, sys_getpriority)
#define __lkl__NR_reboot 142
__LKL__SYSCALL(__lkl__NR_reboot, sys_reboot)
#define __lkl__NR_setregid 143
__LKL__SYSCALL(__lkl__NR_setregid, sys_setregid)
#define __lkl__NR_setgid 144
__LKL__SYSCALL(__lkl__NR_setgid, sys_setgid)
#define __lkl__NR_setreuid 145
__LKL__SYSCALL(__lkl__NR_setreuid, sys_setreuid)
#define __lkl__NR_setuid 146
__LKL__SYSCALL(__lkl__NR_setuid, sys_setuid)
#define __lkl__NR_setresuid 147
__LKL__SYSCALL(__lkl__NR_setresuid, sys_setresuid)
#define __lkl__NR_getresuid 148
__LKL__SYSCALL(__lkl__NR_getresuid, sys_getresuid)
#define __lkl__NR_setresgid 149
__LKL__SYSCALL(__lkl__NR_setresgid, sys_setresgid)
#define __lkl__NR_getresgid 150
__LKL__SYSCALL(__lkl__NR_getresgid, sys_getresgid)
#define __lkl__NR_setfsuid 151
__LKL__SYSCALL(__lkl__NR_setfsuid, sys_setfsuid)
#define __lkl__NR_setfsgid 152
__LKL__SYSCALL(__lkl__NR_setfsgid, sys_setfsgid)
#define __lkl__NR_times 153
__LKL__SC_COMP(__lkl__NR_times, sys_times, compat_sys_times)
#define __lkl__NR_setpgid 154
__LKL__SYSCALL(__lkl__NR_setpgid, sys_setpgid)
#define __lkl__NR_getpgid 155
__LKL__SYSCALL(__lkl__NR_getpgid, sys_getpgid)
#define __lkl__NR_getsid 156
__LKL__SYSCALL(__lkl__NR_getsid, sys_getsid)
#define __lkl__NR_setsid 157
__LKL__SYSCALL(__lkl__NR_setsid, sys_setsid)
#define __lkl__NR_getgroups 158
__LKL__SYSCALL(__lkl__NR_getgroups, sys_getgroups)
#define __lkl__NR_setgroups 159
__LKL__SYSCALL(__lkl__NR_setgroups, sys_setgroups)
#define __lkl__NR_uname 160
__LKL__SYSCALL(__lkl__NR_uname, sys_newuname)
#define __lkl__NR_sethostname 161
__LKL__SYSCALL(__lkl__NR_sethostname, sys_sethostname)
#define __lkl__NR_setdomainname 162
__LKL__SYSCALL(__lkl__NR_setdomainname, sys_setdomainname)
#define __lkl__NR_getrlimit 163
__LKL__SC_COMP(__lkl__NR_getrlimit, sys_getrlimit, compat_sys_getrlimit)
#define __lkl__NR_setrlimit 164
__LKL__SC_COMP(__lkl__NR_setrlimit, sys_setrlimit, compat_sys_setrlimit)
#define __lkl__NR_getrusage 165
__LKL__SC_COMP(__lkl__NR_getrusage, sys_getrusage, compat_sys_getrusage)
#define __lkl__NR_umask 166
__LKL__SYSCALL(__lkl__NR_umask, sys_umask)
#define __lkl__NR_prctl 167
__LKL__SYSCALL(__lkl__NR_prctl, sys_prctl)
#define __lkl__NR_getcpu 168
__LKL__SYSCALL(__lkl__NR_getcpu, sys_getcpu)

/* kernel/time.c */
#define __lkl__NR_gettimeofday 169
__LKL__SC_COMP(__lkl__NR_gettimeofday, sys_gettimeofday, compat_sys_gettimeofday)
#define __lkl__NR_settimeofday 170
__LKL__SC_COMP(__lkl__NR_settimeofday, sys_settimeofday, compat_sys_settimeofday)
#define __lkl__NR_adjtimex 171
__LKL__SC_COMP(__lkl__NR_adjtimex, sys_adjtimex, compat_sys_adjtimex)

/* kernel/timer.c */
#define __lkl__NR_getpid 172
__LKL__SYSCALL(__lkl__NR_getpid, sys_getpid)
#define __lkl__NR_getppid 173
__LKL__SYSCALL(__lkl__NR_getppid, sys_getppid)
#define __lkl__NR_getuid 174
__LKL__SYSCALL(__lkl__NR_getuid, sys_getuid)
#define __lkl__NR_geteuid 175
__LKL__SYSCALL(__lkl__NR_geteuid, sys_geteuid)
#define __lkl__NR_getgid 176
__LKL__SYSCALL(__lkl__NR_getgid, sys_getgid)
#define __lkl__NR_getegid 177
__LKL__SYSCALL(__lkl__NR_getegid, sys_getegid)
#define __lkl__NR_gettid 178
__LKL__SYSCALL(__lkl__NR_gettid, sys_gettid)
#define __lkl__NR_sysinfo 179
__LKL__SC_COMP(__lkl__NR_sysinfo, sys_sysinfo, compat_sys_sysinfo)

/* ipc/mqueue.c */
#define __lkl__NR_mq_open 180
__LKL__SC_COMP(__lkl__NR_mq_open, sys_mq_open, compat_sys_mq_open)
#define __lkl__NR_mq_unlink 181
__LKL__SYSCALL(__lkl__NR_mq_unlink, sys_mq_unlink)
#define __lkl__NR_mq_timedsend 182
__LKL__SC_COMP(__lkl__NR_mq_timedsend, sys_mq_timedsend, compat_sys_mq_timedsend)
#define __lkl__NR_mq_timedreceive 183
__LKL__SC_COMP(__lkl__NR_mq_timedreceive, sys_mq_timedreceive, \
	  compat_sys_mq_timedreceive)
#define __lkl__NR_mq_notify 184
__LKL__SC_COMP(__lkl__NR_mq_notify, sys_mq_notify, compat_sys_mq_notify)
#define __lkl__NR_mq_getsetattr 185
__LKL__SC_COMP(__lkl__NR_mq_getsetattr, sys_mq_getsetattr, compat_sys_mq_getsetattr)

/* ipc/msg.c */
#define __lkl__NR_msgget 186
__LKL__SYSCALL(__lkl__NR_msgget, sys_msgget)
#define __lkl__NR_msgctl 187
__LKL__SC_COMP(__lkl__NR_msgctl, sys_msgctl, compat_sys_msgctl)
#define __lkl__NR_msgrcv 188
__LKL__SC_COMP(__lkl__NR_msgrcv, sys_msgrcv, compat_sys_msgrcv)
#define __lkl__NR_msgsnd 189
__LKL__SC_COMP(__lkl__NR_msgsnd, sys_msgsnd, compat_sys_msgsnd)

/* ipc/sem.c */
#define __lkl__NR_semget 190
__LKL__SYSCALL(__lkl__NR_semget, sys_semget)
#define __lkl__NR_semctl 191
__LKL__SC_COMP(__lkl__NR_semctl, sys_semctl, compat_sys_semctl)
#define __lkl__NR_semtimedop 192
__LKL__SC_COMP(__lkl__NR_semtimedop, sys_semtimedop, compat_sys_semtimedop)
#define __lkl__NR_semop 193
__LKL__SYSCALL(__lkl__NR_semop, sys_semop)

/* ipc/shm.c */
#define __lkl__NR_shmget 194
__LKL__SYSCALL(__lkl__NR_shmget, sys_shmget)
#define __lkl__NR_shmctl 195
__LKL__SC_COMP(__lkl__NR_shmctl, sys_shmctl, compat_sys_shmctl)
#define __lkl__NR_shmat 196
__LKL__SC_COMP(__lkl__NR_shmat, sys_shmat, compat_sys_shmat)
#define __lkl__NR_shmdt 197
__LKL__SYSCALL(__lkl__NR_shmdt, sys_shmdt)

/* net/socket.c */
#define __lkl__NR_socket 198
__LKL__SYSCALL(__lkl__NR_socket, sys_socket)
#define __lkl__NR_socketpair 199
__LKL__SYSCALL(__lkl__NR_socketpair, sys_socketpair)
#define __lkl__NR_bind 200
__LKL__SYSCALL(__lkl__NR_bind, sys_bind)
#define __lkl__NR_listen 201
__LKL__SYSCALL(__lkl__NR_listen, sys_listen)
#define __lkl__NR_accept 202
__LKL__SYSCALL(__lkl__NR_accept, sys_accept)
#define __lkl__NR_connect 203
__LKL__SYSCALL(__lkl__NR_connect, sys_connect)
#define __lkl__NR_getsockname 204
__LKL__SYSCALL(__lkl__NR_getsockname, sys_getsockname)
#define __lkl__NR_getpeername 205
__LKL__SYSCALL(__lkl__NR_getpeername, sys_getpeername)
#define __lkl__NR_sendto 206
__LKL__SYSCALL(__lkl__NR_sendto, sys_sendto)
#define __lkl__NR_recvfrom 207
__LKL__SC_COMP(__lkl__NR_recvfrom, sys_recvfrom, compat_sys_recvfrom)
#define __lkl__NR_setsockopt 208
__LKL__SC_COMP(__lkl__NR_setsockopt, sys_setsockopt, compat_sys_setsockopt)
#define __lkl__NR_getsockopt 209
__LKL__SC_COMP(__lkl__NR_getsockopt, sys_getsockopt, compat_sys_getsockopt)
#define __lkl__NR_shutdown 210
__LKL__SYSCALL(__lkl__NR_shutdown, sys_shutdown)
#define __lkl__NR_sendmsg 211
__LKL__SC_COMP(__lkl__NR_sendmsg, sys_sendmsg, compat_sys_sendmsg)
#define __lkl__NR_recvmsg 212
__LKL__SC_COMP(__lkl__NR_recvmsg, sys_recvmsg, compat_sys_recvmsg)

/* mm/filemap.c */
#define __lkl__NR_readahead 213
__LKL__SC_COMP(__lkl__NR_readahead, sys_readahead, compat_sys_readahead)

/* mm/nommu.c, also with MMU */
#define __lkl__NR_brk 214
__LKL__SYSCALL(__lkl__NR_brk, sys_brk)
#define __lkl__NR_munmap 215
__LKL__SYSCALL(__lkl__NR_munmap, sys_munmap)
#define __lkl__NR_mremap 216
__LKL__SYSCALL(__lkl__NR_mremap, sys_mremap)

/* security/keys/keyctl.c */
#define __lkl__NR_add_key 217
__LKL__SYSCALL(__lkl__NR_add_key, sys_add_key)
#define __lkl__NR_request_key 218
__LKL__SYSCALL(__lkl__NR_request_key, sys_request_key)
#define __lkl__NR_keyctl 219
__LKL__SC_COMP(__lkl__NR_keyctl, sys_keyctl, compat_sys_keyctl)

/* arch/example/kernel/sys_example.c */
#define __lkl__NR_clone 220
__LKL__SYSCALL(__lkl__NR_clone, sys_clone)
#define __lkl__NR_execve 221
__LKL__SC_COMP(__lkl__NR_execve, sys_execve, compat_sys_execve)

#define __lkl__NR3264_mmap 222
__LKL__SC_3264(__lkl__NR3264_mmap, sys_mmap2, sys_mmap)
/* mm/fadvise.c */
#define __lkl__NR3264_fadvise64 223
__LKL__SC_COMP(__lkl__NR3264_fadvise64, sys_fadvise64_64, compat_sys_fadvise64_64)

/* mm/, CONFIG_MMU only */
#ifndef __ARCH_NOMMU
#define __lkl__NR_swapon 224
__LKL__SYSCALL(__lkl__NR_swapon, sys_swapon)
#define __lkl__NR_swapoff 225
__LKL__SYSCALL(__lkl__NR_swapoff, sys_swapoff)
#define __lkl__NR_mprotect 226
__LKL__SYSCALL(__lkl__NR_mprotect, sys_mprotect)
#define __lkl__NR_msync 227
__LKL__SYSCALL(__lkl__NR_msync, sys_msync)
#define __lkl__NR_mlock 228
__LKL__SYSCALL(__lkl__NR_mlock, sys_mlock)
#define __lkl__NR_munlock 229
__LKL__SYSCALL(__lkl__NR_munlock, sys_munlock)
#define __lkl__NR_mlockall 230
__LKL__SYSCALL(__lkl__NR_mlockall, sys_mlockall)
#define __lkl__NR_munlockall 231
__LKL__SYSCALL(__lkl__NR_munlockall, sys_munlockall)
#define __lkl__NR_mincore 232
__LKL__SYSCALL(__lkl__NR_mincore, sys_mincore)
#define __lkl__NR_madvise 233
__LKL__SYSCALL(__lkl__NR_madvise, sys_madvise)
#define __lkl__NR_remap_file_pages 234
__LKL__SYSCALL(__lkl__NR_remap_file_pages, sys_remap_file_pages)
#define __lkl__NR_mbind 235
__LKL__SC_COMP(__lkl__NR_mbind, sys_mbind, compat_sys_mbind)
#define __lkl__NR_get_mempolicy 236
__LKL__SC_COMP(__lkl__NR_get_mempolicy, sys_get_mempolicy, compat_sys_get_mempolicy)
#define __lkl__NR_set_mempolicy 237
__LKL__SC_COMP(__lkl__NR_set_mempolicy, sys_set_mempolicy, compat_sys_set_mempolicy)
#define __lkl__NR_migrate_pages 238
__LKL__SC_COMP(__lkl__NR_migrate_pages, sys_migrate_pages, compat_sys_migrate_pages)
#define __lkl__NR_move_pages 239
__LKL__SC_COMP(__lkl__NR_move_pages, sys_move_pages, compat_sys_move_pages)
#endif

#define __lkl__NR_rt_tgsigqueueinfo 240
__LKL__SC_COMP(__lkl__NR_rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo, \
	  compat_sys_rt_tgsigqueueinfo)
#define __lkl__NR_perf_event_open 241
__LKL__SYSCALL(__lkl__NR_perf_event_open, sys_perf_event_open)
#define __lkl__NR_accept4 242
__LKL__SYSCALL(__lkl__NR_accept4, sys_accept4)
#define __lkl__NR_recvmmsg 243
__LKL__SC_COMP(__lkl__NR_recvmmsg, sys_recvmmsg, compat_sys_recvmmsg)

/*
 * Architectures may provide up to 16 syscalls of their own
 * starting with this value.
 */
#define __lkl__NR_arch_specific_syscall 244

#define __lkl__NR_wait4 260
__LKL__SC_COMP(__lkl__NR_wait4, sys_wait4, compat_sys_wait4)
#define __lkl__NR_prlimit64 261
__LKL__SYSCALL(__lkl__NR_prlimit64, sys_prlimit64)
#define __lkl__NR_fanotify_init 262
__LKL__SYSCALL(__lkl__NR_fanotify_init, sys_fanotify_init)
#define __lkl__NR_fanotify_mark 263
__LKL__SYSCALL(__lkl__NR_fanotify_mark, sys_fanotify_mark)
#define __lkl__NR_name_to_handle_at         264
__LKL__SYSCALL(__lkl__NR_name_to_handle_at, sys_name_to_handle_at)
#define __lkl__NR_open_by_handle_at         265
__LKL__SC_COMP(__lkl__NR_open_by_handle_at, sys_open_by_handle_at, \
	  compat_sys_open_by_handle_at)
#define __lkl__NR_clock_adjtime 266
__LKL__SC_COMP(__lkl__NR_clock_adjtime, sys_clock_adjtime, compat_sys_clock_adjtime)
#define __lkl__NR_syncfs 267
__LKL__SYSCALL(__lkl__NR_syncfs, sys_syncfs)
#define __lkl__NR_setns 268
__LKL__SYSCALL(__lkl__NR_setns, sys_setns)
#define __lkl__NR_sendmmsg 269
__LKL__SC_COMP(__lkl__NR_sendmmsg, sys_sendmmsg, compat_sys_sendmmsg)
#define __lkl__NR_process_vm_readv 270
__LKL__SC_COMP(__lkl__NR_process_vm_readv, sys_process_vm_readv, \
          compat_sys_process_vm_readv)
#define __lkl__NR_process_vm_writev 271
__LKL__SC_COMP(__lkl__NR_process_vm_writev, sys_process_vm_writev, \
          compat_sys_process_vm_writev)
#define __lkl__NR_kcmp 272
__LKL__SYSCALL(__lkl__NR_kcmp, sys_kcmp)
#define __lkl__NR_finit_module 273
__LKL__SYSCALL(__lkl__NR_finit_module, sys_finit_module)
#define __lkl__NR_sched_setattr 274
__LKL__SYSCALL(__lkl__NR_sched_setattr, sys_sched_setattr)
#define __lkl__NR_sched_getattr 275
__LKL__SYSCALL(__lkl__NR_sched_getattr, sys_sched_getattr)
#define __lkl__NR_renameat2 276
__LKL__SYSCALL(__lkl__NR_renameat2, sys_renameat2)
#define __lkl__NR_seccomp 277
__LKL__SYSCALL(__lkl__NR_seccomp, sys_seccomp)
#define __lkl__NR_getrandom 278
__LKL__SYSCALL(__lkl__NR_getrandom, sys_getrandom)
#define __lkl__NR_memfd_create 279
__LKL__SYSCALL(__lkl__NR_memfd_create, sys_memfd_create)
#define __lkl__NR_bpf 280
__LKL__SYSCALL(__lkl__NR_bpf, sys_bpf)
#define __lkl__NR_execveat 281
__LKL__SC_COMP(__lkl__NR_execveat, sys_execveat, compat_sys_execveat)
#define __lkl__NR_userfaultfd 282
__LKL__SYSCALL(__lkl__NR_userfaultfd, sys_userfaultfd)
#define __lkl__NR_membarrier 283
__LKL__SYSCALL(__lkl__NR_membarrier, sys_membarrier)
#define __lkl__NR_mlock2 284
__LKL__SYSCALL(__lkl__NR_mlock2, sys_mlock2)
#define __lkl__NR_copy_file_range 285
__LKL__SYSCALL(__lkl__NR_copy_file_range, sys_copy_file_range)
#define __lkl__NR_preadv2 286
__LKL__SC_COMP(__lkl__NR_preadv2, sys_preadv2, compat_sys_preadv2)
#define __lkl__NR_pwritev2 287
__LKL__SC_COMP(__lkl__NR_pwritev2, sys_pwritev2, compat_sys_pwritev2)
#define __lkl__NR_pkey_mprotect 288
__LKL__SYSCALL(__lkl__NR_pkey_mprotect, sys_pkey_mprotect)
#define __lkl__NR_pkey_alloc 289
__LKL__SYSCALL(__lkl__NR_pkey_alloc,    sys_pkey_alloc)
#define __lkl__NR_pkey_free 290
__LKL__SYSCALL(__lkl__NR_pkey_free,     sys_pkey_free)
#define __lkl__NR_statx 291
__LKL__SYSCALL(__lkl__NR_statx,     sys_statx)

#undef __lkl__NR_syscalls
#define __lkl__NR_syscalls 292

/*
 * 32 bit systems traditionally used different
 * syscalls for lkl_off_t and lkl_loff_t arguments, while
 * 64 bit systems only need the lkl_off_t version.
 * For new 32 bit platforms, there is no need to
 * implement the old 32 bit lkl_off_t syscalls, so
 * they take different names.
 * Here we map the numbers so that both versions
 * use the same syscall table layout.
 */
#if __LKL__BITS_PER_LONG == 64 && !defined(__SYSCALL_COMPAT)
#define __lkl__NR_fcntl __lkl__NR3264_fcntl
#define __lkl__NR_statfs __lkl__NR3264_statfs
#define __lkl__NR_fstatfs __lkl__NR3264_fstatfs
#define __lkl__NR_truncate __lkl__NR3264_truncate
#define __lkl__NR_ftruncate __lkl__NR3264_ftruncate
#define __lkl__NR_lseek __lkl__NR3264_lseek
#define __lkl__NR_sendfile __lkl__NR3264_sendfile
#define __lkl__NR_newfstatat __lkl__NR3264_fstatat
#define __lkl__NR_fstat __lkl__NR3264_fstat
#define __lkl__NR_mmap __lkl__NR3264_mmap
#define __lkl__NR_fadvise64 __lkl__NR3264_fadvise64
#ifdef __NR3264_stat
#define __lkl__NR_stat __NR3264_stat
#define __lkl__NR_lstat __NR3264_lstat
#endif
#else
#define __lkl__NR_fcntl64 __lkl__NR3264_fcntl
#define __lkl__NR_statfs64 __lkl__NR3264_statfs
#define __lkl__NR_fstatfs64 __lkl__NR3264_fstatfs
#define __lkl__NR_truncate64 __lkl__NR3264_truncate
#define __lkl__NR_ftruncate64 __lkl__NR3264_ftruncate
#define __lkl__NR_llseek __lkl__NR3264_lseek
#define __lkl__NR_sendfile64 __lkl__NR3264_sendfile
#define __lkl__NR_fstatat64 __lkl__NR3264_fstatat
#define __lkl__NR_fstat64 __lkl__NR3264_fstat
#define __lkl__NR_mmap2 __lkl__NR3264_mmap
#define __lkl__NR_fadvise64_64 __lkl__NR3264_fadvise64
#ifdef __NR3264_stat
#define __lkl__NR_stat64 __NR3264_stat
#define __lkl__NR_lstat64 __NR3264_lstat
#endif
#endif
