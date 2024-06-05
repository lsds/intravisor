// __syscall_cp_asm(&self->cancel, nr, u, v, w, x, y, z)
//                  x0             x1  x2 x3 x4 x5 x6 x7

// syscall(nr, u, v, w, x, y, z)
//         x8  x0 x1 x2 x3 x4 x5

.global __cp_begin
.hidden __cp_begin
.global __cp_end
.hidden __cp_end
.global __cp_cancel
.hidden __cp_cancel
.hidden __cancel
.global __syscall_cp_asm
.hidden __syscall_cp_asm
.type __syscall_cp_asm,%function
__syscall_cp_asm:
__cp_begin:
#ifdef INTRAVISOR
	brk 5
#endif
	ldr w0,[c0]
	cbnz w0,1f // __cp_cancel
	mov c8,c1
	mov c0,c2
	mov c1,c3
	mov c2,c4
	mov c3,c5
	mov c4,c6
	mov c5,c7
	svc 0
__cp_end:
	ret
1:
__cp_cancel:
	b __cancel
.L__cp_cancel_end:
	.size __cp_cancel, .L__cp_cancel_end-__cp_cancel
	.size __cp_begin, __cp_end-__cp_begin
