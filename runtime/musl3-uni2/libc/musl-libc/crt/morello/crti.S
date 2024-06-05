#include "crt_regs.inc"

.section .init
.global _init
.type _init,%function
_init:
	stp r_FP,r_LR,[r_SP,-INC]!
	mov r_FP,r_SP
.L_init_end:
    .size   _init, .L_init_end-_init

.section .fini
.global _fini
.type _fini,%function
_fini:
	stp r_FP,r_LR,[r_SP,-INC]!
	mov r_FP,r_SP
.L_fini_end:
    .size   _fini, .L_fini_end-_fini
