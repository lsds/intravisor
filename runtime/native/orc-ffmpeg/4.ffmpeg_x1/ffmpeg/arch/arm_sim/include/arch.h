static __inline__ long getT5(void) {
    register long t5 asm("r14");
    asm ("" : "=r"(t5));
    return t5;
}

static __inline__ unsigned long * getTLS(void) {
    register unsigned long * tp;
    __asm__ ("mrs %0,tpidr_el0" : "=r"(tp));

    return tp;
}
