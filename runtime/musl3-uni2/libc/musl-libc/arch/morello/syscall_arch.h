#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#if 0
#define __asm_syscall(...) do { \
	__asm__ __volatile__ ( "svc 0" \
	: "=C"(x0) : __VA_ARGS__ : "memory", "cc"); \
	return x0; \
	} while (0)
#else

#endif

//	return c_out(); \
//	__asm__ __volatile__ ( "bl	c_out" :  : __VA_ARGS__ : "memory"); \
//	return x0; \

//	__asm__ __volatile__ ( "adrp	c6, outer_asm \n\r add c6, c6, :lo12:outer_asm\n\r blr c6\n\r " : "=C"(x0) : __VA_ARGS__ : "memory", "cc"); \

intptr_t c_out0(intptr_t n);
intptr_t c_out1(intptr_t n, intptr_t a);
intptr_t c_out2(intptr_t n, intptr_t a, intptr_t b);
intptr_t c_out3(intptr_t n, intptr_t a, intptr_t b, intptr_t c);
intptr_t c_out4(intptr_t n, intptr_t a, intptr_t b, intptr_t c, intptr_t d);
intptr_t c_out5(intptr_t n, intptr_t a, intptr_t b, intptr_t c, intptr_t d, intptr_t e);
intptr_t c_out6(intptr_t n, intptr_t a, intptr_t b, intptr_t c, intptr_t d, intptr_t e, intptr_t f);

static inline intptr_t __syscall0(intptr_t n)
{
	return c_out0(n);
}

static inline intptr_t __syscall1(intptr_t n, intptr_t a)
{
	return c_out1(n, a);
}

static inline intptr_t __syscall2(intptr_t n, intptr_t a, intptr_t b)
{
	return c_out2(n, a, b);
}

static inline intptr_t __syscall3(intptr_t n, intptr_t a, intptr_t b, intptr_t c)
{
	return c_out3(n, a, b, c);
}

static inline intptr_t __syscall4(intptr_t n, intptr_t a, intptr_t b, intptr_t c, intptr_t d)
{
	return c_out4(n, a, b, c, d);
}

static inline intptr_t __syscall5(intptr_t n, intptr_t a, intptr_t b, intptr_t c, intptr_t d, intptr_t e)
{
	return c_out5(n, a, b, c, d, e);
}

static inline intptr_t __syscall6(intptr_t n, intptr_t a, intptr_t b, intptr_t c, intptr_t d, intptr_t e, intptr_t f)
{
	return c_out6(n, a, b, c, d, e, f);
}

#ifndef INTRAVISOR
#define VDSO_USEFUL
#define VDSO_CGT_SYM "__kernel_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6.39"
#endif

#define IPC_64 0
