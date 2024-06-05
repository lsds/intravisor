.global sigsetjmp
.global __sigsetjmp
.type sigsetjmp,%function
.type __sigsetjmp,%function
sigsetjmp:
__sigsetjmp:
	cbz x1,setjmp

	str c30,[c0,#288]
	str c19,[c0,#288+16+16]
	mov c19,c0

	bl setjmp

	mov w1,w0
	mov c0,c19
	ldr c30,[c0,#288]
	ldr c19,[c0,#288+16+16]

.hidden __sigsetjmp_tail
	b __sigsetjmp_tail
