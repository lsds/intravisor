.global _longjmp
.global longjmp
.type _longjmp,%function
.type longjmp,%function
_longjmp:
longjmp:
	// 102205_aapcs-morello.pdf 6.1.1 callee saved registers
	ldp c19, c20, [c0,#0]
	ldp c21, c22, [c0,#32]
	ldp c23, c24, [c0,#64]
	ldp c25, c26, [c0,#96]
	ldp c27, c28, [c0,#128]
	ldp c29, c30, [c0,#160]
	ldr c2, [c0,#208]
	mov csp, c2
	ldp d8 , d9, [c0,#224]
	ldp d10, d11, [c0,#240]
	ldp d12, d13, [c0,#256]
	ldp d14, d15, [c0,#272]

	cmp w1, 0
	csinc w0, w1, wzr, ne
	br c30
