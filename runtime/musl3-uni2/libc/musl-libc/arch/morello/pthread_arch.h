#if !defined(MUSL_USE_COMPILER_BUILTINS)
static inline uintptr_t __get_tp()
{
	uintptr_t tp;
	__asm__ ("mrs %0,ctpidr_el0" : "=C"(tp));
	return tp;
}
#endif

#define TLS_ABOVE_TP
#define GAP_ABOVE_TP 16

#define MC_PC pc
