int host_write_out(char __capability *ptr, int size) {
	return (int) c_out_3(1, ptr, (long) size, 0);
}

void host_exit() {
	c_out_3(13, 0, 0, 0);
}


int host_cap_prb(char *key, void *location, long *size) {
#if 0
	int tmp = 406;
	register long a0 __asm__("a0") = (long) key;
	register long a1 __asm__("a1") = (long) location;
	register long a2 __asm__("a2") = (long) size;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "r"(a2) : "memory" );
	return (int) a0; 
#else
	return (int) c_out_3(406, key, location, size);
#endif
}
