int host_write(char *ptr, int size) {
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );

	return a0; 
}

void host_exit() {
	int tmp = 13;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
}

int host_cap_prb(char *key, void *location) {
	int tmp = 406;
	register long a0 __asm__("a0") = (long) key;
	register long a1 __asm__("a1") = (long) location;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
}


int host_get_my_inner(void *ptr) {
	int tmp = 700;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
}