// __clone(func, stack, flags, arg, ptid, tls, ctid)
//         x0,   x1,    w2,    x3,  x4,   x5,  x6
// new vararg PCS:  c0,c1,w2,c3,[c9+0],[c9+16],[c9+32]
// syscall(SYS_clone, flags, stack, ptid, tls, ctid)
//         x8,        x0,    x1,    x2,   x3,  x4

.global __clone
.hidden __clone
.type   __clone,%function
__clone:
	// align stack
	alignd c1,c1,#4
	// load var args
	mov     w4, #0
	mov     w5, #0
	mov     w6, #0
	gclen   x7, c9
	cmp     x7, #48
	b.lt    1f
	ldr     c6, [c9, #32]
1:	cmp     x7, #32
	b.lt    1f
	ldr     c5, [c9, #16]
1:	cmp     x7, #16
	b.lt    1f // no args
	ldr     c4, [c9, #0]
1:
	// store func, arg
	stp c0,c3,[c1,#-32]!

	uxtw x0,w2
	mov c2,c4
	mov c3,c5
	mov c4,c6
#ifndef INTRAVISOR
	mov x8,#220 // SYS_clone
	svc #0
#else
	mov x14,#220
	b c_out
#endif

	cbz x0,1f
	// parent
	ret

	// child
1:	ldp c1,c0,[csp],#32

2:	blr c1

//note: in fact we do jump to this code
#ifndef INTRAVISOR
	mov x8,#93 // SYS_exit
	svc #0
#else
	mov x14,#93
	b c_out
#endif
.size __clone, .-__clone;
