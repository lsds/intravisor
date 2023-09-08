#ifndef _ASM_LKL_SYSCALLS_H
#define _ASM_LKL_SYSCALLS_H

/* Initialise system call handling */
int syscalls_init(void);

/* Initialise parent host task for all syscalls */
int host0_init(void);

/* Shutdown system call handling */
void syscalls_cleanup(void);

/* Main entry point for LKL system calls */
long lkl_syscall(long no, long *params);

/* Trigger idle task */
void wakeup_idle_host_task(void);

#define sys_mmap sys_mmap_pgoff
#define sys_mmap2 sys_mmap_pgoff
#define sys_vfork sys_ni_syscall
#define sys_rt_sigreturn sys_ni_syscall

#include <asm-generic/syscalls.h>

#endif /* _ASM_LKL_SYSCALLS_H */
