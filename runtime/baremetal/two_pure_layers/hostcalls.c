#include "hostcalls.h"

int host_write(char *ptr, int size) {
#if 0
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return a0; 

#else
	return c_out_2(1, (long) ptr, (long) size);
#endif


}

void host_exit() {
#if 0
	int tmp = 13;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
#else
	c_out_2(13, 0, 0);
#endif
}

int host_cap_prb(char *key, void *location) {
#if 0
	int tmp = 406;
	register long a0 __asm__("a0") = (long) key;
	register long a1 __asm__("a1") = (long) location;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
#else
	return c_out_2(406, (long) key, location);
#endif
}


int host_get_my_inner(void *ptr) {
#if 0
	int tmp = 700;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0;
#else
	return c_out_2(700, (long) ptr, 0);
#endif
}