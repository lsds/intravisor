#ifndef _ASM_LKL_SIGNAL_H
#define _ASM_LKL_SIGNAL_H
#include <asm-generic/signal.h>

struct ucontext;

struct thread_info;
struct ksignal_list_node;
struct ksignal;

void lkl_process_trap(int signr, struct ucontext *uctx);
 
/*
 * Capture pending signals and move them to a task-specific list.
 * Must be called only with the cpu lock held.
 */

void move_signals_to_task(void);

/*
 * Send any signals targeting this task.
 * Must be called only with the cpu lock held, it will be unlocked for the call to user code.
 */

void send_current_signals(struct ucontext *uctx);

#endif