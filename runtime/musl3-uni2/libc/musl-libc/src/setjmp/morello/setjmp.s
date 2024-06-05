.global __setjmp
.global _setjmp
.global setjmp
.type __setjmp,@function
.type _setjmp,@function
.type setjmp,@function
__setjmp:
_setjmp:
setjmp:
	// 102205_aapcs-morello.pdf 6.1.1 callee saved registers
	stp c19, c20, [c0,#0]
	stp c21, c22, [c0,#32]
	stp c23, c24, [c0,#64]
	stp c25, c26, [c0,#96]
	stp c27, c28, [c0,#128]
	stp c29, c30, [c0,#160]
	mov c2, csp
	str c2, [c0,#208]
	stp  d8,  d9, [c0,#224]
	stp d10, d11, [c0,#240]
	stp d12, d13, [c0,#256]
	stp d14, d15, [c0,#272]
	mov x0, #0
	ret
