static __inline__ void * getSP(void) {
    register void * sp asm("sp");
    asm ("" : "=r"(sp));
    return sp;
}

static __inline__ void * __capability getT5(void) {
    register void * __capability ctp asm("ctp");
    asm ("" : "=C"(ctp));
    return ctp;
}

static __inline__ void my_abort(void) {
    __asm__ __volatile__ ("ebreak");
}


