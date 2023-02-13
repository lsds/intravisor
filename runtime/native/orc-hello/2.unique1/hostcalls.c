#include "hostcalls.h"

extern long c_out(void *);

int host_write_out(char __capability *ptr, int size) {
#if 0
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;

	__asm__ __volatile__("cjr %4" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "C"(c_out) : "memory" );
	return (int) a0; 

#else
	return (int) c_out_3(1, ptr, (long) size, 0);
#endif
}

int host_inv(char *dst, char *src, int size) {
#if 0
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );

	return a0; 
#else
	return c_out_3(1000, dst, src, size);
#endif
}

void host_exit() {
#if 0
	int tmp = 13;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
#else
	c_out_3(13, 0, 0, 0);
#endif
}


int host_get_sc_caps(int me, int they, void *ptr) {
	return c_out_3(702, me, they, ptr);
}

