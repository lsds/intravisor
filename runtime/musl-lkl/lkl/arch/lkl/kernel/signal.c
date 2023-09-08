#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/ptrace.h>
#include <asm-generic/ucontext.h>
#include <asm/cpu.h>
#include <asm/host_ops.h>


static void initialize_uctx(struct ucontext *uctx, const struct pt_regs *regs)
{
    if(regs)
    {
#if 0
        uctx->uc_mcontext.rax = regs->rax;
        uctx->uc_mcontext.rbx = regs->rbx;
        uctx->uc_mcontext.rcx = regs->rcx;
        uctx->uc_mcontext.rdx = regs->rdx;
        uctx->uc_mcontext.rbp = regs->rbp;
        uctx->uc_mcontext.rsp = regs->rsp;
        uctx->uc_mcontext.rdi = regs->rdi;
        uctx->uc_mcontext.rsi = regs->rsi;
        uctx->uc_mcontext.r8  = regs->r8;
        uctx->uc_mcontext.r9  = regs->r9;
        uctx->uc_mcontext.r10 = regs->r10;
        uctx->uc_mcontext.r11 = regs->r11;
        uctx->uc_mcontext.r12 = regs->r12;
        uctx->uc_mcontext.r13 = regs->r13;
        uctx->uc_mcontext.r14 = regs->r14;
        uctx->uc_mcontext.r15 = regs->r15;
        uctx->uc_mcontext.rip = regs->rip;
#endif
    }
    return;
}

/* 
 * Function to invoke the signal handler of LKL application. This works for 
 * sig handler installed using sigaction or signal API. This will remove the
 * overhead of injecting the stack frame to pass the user context to user
 * space application (could lead to inclusion of ARCH specific code)
 * 
 * MUST be called owning the lock.
 */
static void handle_signal(struct ksignal *ksig, struct ucontext *uctx)
{
    lkl_thread_t self;

    /* In DEBUG build check that the lock is currently held by this task */
    lkl_assert_cpu_owner();

	/*
	 *  Give up the cpu lock while we invoke the signal handler because we are returning
     *  to userspace.
	 */

    lkl_cpu_put();

    /* In case it was recursively locked */
    lkl_assert_cpu_not_owner();

    /* Get the current thread before we invoke the signal handler */
    self = lkl_ops->thread_self();

#if 0
    ksig->ka.sa.sa_handler(ksig->sig, (void*)&ksig->info, (void*)uctx);
#else
    lkl_printf("not implemented %s\n", __func__);
#endif
    /* 
     *  Check if the apparent current thread changes while processing the signal.
     *  Should not happen.
     */

	BUG_ON(!lkl_ops->thread_equal(self, lkl_ops->thread_self()));

    /* take back the lock */
	lkl_cpu_get();
}

/*
 *  Return only the signal of a given number, while snipping it from the list
 *  Used by the trap handler for sync signals such as SEGV, FPE.
 * 
 *  Returns 1 meaning a signal was found, 0 otherwise.
 */
int get_given_ksignal(struct thread_info *task, struct ksignal* sig, int which)
{
    struct ksignal_list_node *next;
    struct ksignal_list_node *node;
    struct ksignal_list_node *previous;

    spin_lock(&task->signal_list_lock);
    node = task->signal_list_head;
    previous = NULL;

    while (node != NULL) {
        next = node->next;
        if (node->sig.sig == which) { 
           /* first remove the node we found from the linked list */
           
            if (previous != NULL) /* not at the front? */
                previous->next = next;
            else
                task->signal_list_head = next;

            if (next == NULL)                       /* was that the last node? */
                task->signal_list_tail = previous;  /* yes, have the tail point at the previous or be null */

            spin_unlock(&task->signal_list_lock);
            memcpy(sig, &node->sig, sizeof(*sig));  /* copy the signal back to the caller */
            LKL_TRACE("Fetching task %p signal %d\n", current, sig->sig);
            kfree(node);
            return 1;
        }
        previous = node;
        node = next;
    }
    
    spin_unlock(&task->signal_list_lock);
    return 0;
}  

int get_next_ksignal(struct thread_info *task, struct ksignal* sig)
{
    struct ksignal_list_node *next;
    struct ksignal_list_node *node;

    spin_lock(&task->signal_list_lock);
    node = task->signal_list_head;

    if (!node) {
        spin_unlock(&task->signal_list_lock);
        return 0; /* no pending signals */
    }

    next = node->next;
    task->signal_list_head = next;      /* drop the head */
    if (next == NULL)                   /* was that the last node? */
        task->signal_list_tail = NULL;  /* if so there is now no tail */
        
    
    spin_unlock(&task->signal_list_lock);
    
    memcpy(sig, &node->sig, sizeof(*sig)); /* copy the signal back to the caller */
    LKL_TRACE("Fetching task %p signal %d\n", current, sig->sig);
    kfree(node);
    return 1;
}    


/*
 *  This is the sync signal case and that signal will have just been forced into the
 *  regular task queue of signals so the pre-existing code will work. See lkl_do_trap
 *
 *  Up for debate though is whether it would be better to either directly invoke
 *  the handler in lkl_do_trap or here to have versions of move_signals_to_task, send_current_signals
 *  that operate by scanning the list for signr, the given signal.
 */

/* This is always called while owning the cpu */

void lkl_process_trap(int signr, struct ucontext *uctx)
{
    struct ksignal ksig;

    /* In DEBUG build check that the lock is currently held by this task */
    lkl_assert_cpu_owner();

    LKL_TRACE("enter\n");

    /*
     *  Capture and queue pending signals and traps.
     *  Expect at least the one 'signr'.
     */

    move_signals_to_task();
    
    /*
     *  Walk that queue and find the first one of the type we expect.
     *  Note, no expectation that a trap will happen in order wrt to any
     *  async signal already queued.
     */

    while (get_given_ksignal(task_thread_info(current), &ksig, signr)) {
        /* Handle required signal */
        if (signr == ksig.sig)
        {
            LKL_TRACE("trap task %p %d\n", current, signr);
            handle_signal(&ksig, uctx);
            break;
        }
    }
}

/*
 * Get the end of the list and make it point at the new node,
 * if there were no nodes before then bot head and tail point at this one node
 */

void append_ksignal_node(struct thread_info *task, struct ksignal *ksig)
{
    struct ksignal_list_node *ptr;
    
    /* first make a place to hold our signal */
    struct ksignal_list_node *node = kmalloc(sizeof(struct ksignal_list_node), GFP_ATOMIC);     
    if (node == NULL) {
        lkl_bug("Unable to allocate memory to hold signal state.");
    }
    memcpy(&node->sig, ksig, sizeof(*ksig));
    node->next = NULL;

    /* now put it in the linked list */
    spin_lock(&task->signal_list_lock);
    ptr = task->signal_list_tail;
    if (ptr == NULL) { /* list is empty so point both head and tail at the given node */
        task->signal_list_head = node;
        task->signal_list_tail = node;
    } else { /* otherwise just the tail changes */
        ptr->next = node;
        task->signal_list_tail = node; 
    }

    spin_unlock(&task->signal_list_lock);
}    

/*
 * Must be called with the cpu lock held
 */

void move_signals_to_task(void)
{
    struct ksignal ksig;    /* place to hold retrieved signal */
    /*
     * Get the lkl local version of the current task, so we can store the signals
     * in a list hanging off it.
     */
    struct thread_info *current_task;

    /* In DEBUG build check that the lock is currently held by this task */
    lkl_assert_cpu_owner();

    current_task = task_thread_info(current); 
    /* note that get_signal may never return if the task is dead (eg pending a SIGKILL) */
    while (get_signal(&ksig)) {	
        LKL_TRACE("Appending task %p signal %d\n", current, ksig.sig);
        append_ksignal_node(current_task, &ksig);

/* 
 * TODO check whether the task is runnable here. If it is INTERUPTABLE then set it to RUNNING
 * so it can be scheduled. Check with the ltp test tgkill01.
 * 
 * This will be another PR.
 */

    }
}

/*
 * Must be called WITH the cpu lock held.
 * The signal invoke code drops and retakes the lock.
 */

void send_current_signals(struct ucontext *uctx)
{
    struct ksignal ksig;
    struct ucontext uc;
    
    LKL_TRACE("enter\n");

    if (uctx == NULL) {
        uctx = &uc;
        memset(uctx, 0, sizeof(uc));
        initialize_uctx(uctx, NULL);
    }

    /* In DEBUG build check that the lock is currently held by this task */
    lkl_assert_cpu_owner();

    /* get pending signals */
    while (get_next_ksignal(task_thread_info(current), &ksig)) {
        LKL_TRACE("ksig.sig=%d", ksig.sig);
        
        /* Actually deliver the signal. */

        handle_signal(&ksig, uctx); 
    }
}
