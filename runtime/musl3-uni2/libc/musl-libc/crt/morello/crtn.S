#include "crt_regs.inc"

.section .init
	ldp r_FP,r_LR,[r_SP],#INC
	ret

.section .fini
	ldp r_FP,r_LR,[r_SP],#INC
	ret
