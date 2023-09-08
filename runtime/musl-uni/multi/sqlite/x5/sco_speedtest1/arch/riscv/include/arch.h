
static __inline__ void * getT5(void) {
    register void * t5 asm("t5");
    asm ("" : "=r"(t5));
    return t5;
}

static __inline__ __intcap_t * getTLS(void) {
    register __intcap_t * t5 asm("ctp");
    asm ("" : "=C"(t5));
    return t5;
}
