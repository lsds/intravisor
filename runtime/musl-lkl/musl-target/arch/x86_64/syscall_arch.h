

#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#define CHERI 1

#ifdef CHERI 

#include "stdarg.h"
extern long lkl_syscall(long no, long *params);

static int lkl_call(int nr, int args, ...)
{
	long params[6];
	va_list vl;
	int i;

	va_start(vl, args);
	for (i = 0; i < args; i++)
		params[i] = va_arg(vl, long);
	va_end(vl);
	return lkl_syscall(nr, params);
}
#endif

static  long __syscall0(long n)
{
	unsigned long ret;
#ifndef CHERI
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 0);
#endif
	return ret;
}

static  long __syscall1(long n, long a1)
{
	unsigned long ret;
#ifndef CHERI
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 1, a1);
#endif
	return ret;
}

static  long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;
#ifndef CHERI
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
//						  : "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 2, a1, a2);
#endif
	return ret;
}

static  long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;
#ifndef CHERI
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
//						  "d"(a3) : "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 3, a1, a2, a3);
#endif
	return ret;
}

static  long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
#ifndef CHERI
//	register long r10 __asm__("r10") = a4;
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
//						  "d"(a3), "r"(r10): "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 4, a1, a2, a3, a4);
#endif
	return ret;
}

static  long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
#ifndef CHERI
//	register long r10 __asm__("r10") = a4;
//	register long r8 __asm__("r8") = a5;
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
//						  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 5, a1, a2, a3, a4, a5);
#endif
	return ret;
}

static  long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
#ifndef CHERI
//	register long r10 __asm__("r10") = a4;
//	register long r8 __asm__("r8") = a5;
//	register long r9 __asm__("r9") = a6;
//	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
//						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
#else
	ret = lkl_call(n, 6, a1, a2, a3, a4, a5, a6);
#endif
	return ret;
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
#define VDSO_GETCPU_SYM "__vdso_getcpu"
#define VDSO_GETCPU_VER "LINUX_2.6"

#define IPC_64 0
