static __inline__ void my_abort(void) {
    __asm__ __volatile__ ("ebreak");
}


