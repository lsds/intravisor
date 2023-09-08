#ifndef _ASM_LKL_CPU_H
#define _ASM_LKL_CPU_H

int lkl_cpu_get(void);
void lkl_cpu_put(void);

#ifdef DEBUG
/* Bug if you do not have the cpu lock. */
void lkl_assert_cpu_owner(void);
/* Bug if you do have the cpu lock. */
void lkl_assert_cpu_not_owner(void);
/* Prints values of the various locking structure to aid debugging. */
void lkl_print_cpu_lock_state(const char *func_name);
#else
static inline void lkl_assert_cpu_owner(void) {}
static inline void lkl_assert_cpu_not_owner(void) {}
static inline void lkl_print_cpu_lock_state(const char *func_name) {}
#endif


int lkl_cpu_try_run_irq(int irq);
int lkl_cpu_init(void);
void lkl_cpu_shutdown(void);
void lkl_cpu_wait_shutdown(void);
void lkl_cpu_change_owner(lkl_thread_t owner);
void lkl_cpu_set_irqs_pending(void);

#endif /* _ASM_LKL_CPU_H */
