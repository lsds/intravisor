static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

static __inline__ void * __capability getTP(void) {
    register void * __capability ctp;
    __asm__ ("mrs %0,ctpidr_el0" : "=C"(ctp));

    return ctp;
}


static __inline__ long getT5(void) {
    register long t5 asm("x14");
    asm ("" : "=r"(t5));
    return t5;
}


static __inline__ void mv_sp(unsigned long sp) {
    	__asm__ __volatile__("mov sp, %0;" :: "r"(sp) : "memory");
}

static __inline__ void cmv_ctp(void * __capability ctp) {
	__asm__ __volatile__("msr ctpidr_el0, %0;" :: "C"(ctp) : "memory");
}

static __inline__ void cmv_csp(void * __capability csp) {
	__asm__ __volatile__("mov csp, %0;" :: "C"(csp) : "memory");
}
