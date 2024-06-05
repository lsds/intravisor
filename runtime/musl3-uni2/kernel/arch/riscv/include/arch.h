static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

static __inline__ void * __capability getTP(void) {
    register void * __capability ctp asm("ctp");
    asm ("" : "=C"(ctp));
    return ctp;
}

static __inline__ long getT5(void) {
    register long t5 asm("t5");
    asm ("" : "=r"(t5));
    return t5;
}

static __inline__ void my_abort(void) {
    __asm__ __volatile__ ("ebreak");
}


