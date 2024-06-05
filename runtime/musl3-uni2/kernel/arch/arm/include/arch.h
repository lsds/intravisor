static __inline__ long getT5(void) {
    register long t5 asm("r14");
    asm ("" : "=r"(t5));
    return t5;
}

static __inline__ __intcap_t * getTLS(void) {
    register __intcap_t * ctp;
    __asm__ ("mrs %0,ctpidr_el0" : "=C"(ctp));

    return ctp;
}

static __inline__ void my_abort(void) {
    __asm__ __volatile__ ("brk 0");
}
