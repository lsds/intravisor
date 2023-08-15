#define COMP_DDC (16*2)
#define HC_PCC (16*3)
#define MON_DDC (16*4)
//5--6
#define RA  (16*7)
//8--9
#define CAPF (16*10)
#define RET_COMP_PPC (16*11)
#define RET_COMP_DDC (16*12)


#define RET_TO_INNER_PPC	(16*13)
#define RET_TO_INNER_DDC	(16*14)
#define INNER_DDC			(16*15)

#define MV	mov
#define LC	ldr
#define SC	str

#define A0	x0
#define A1	x1
#define A2	x2
#define A3	x3
#define A4	x4
#define A5	x5
#define A6	x6
#define A7	x7

#define CA0	c0
#define CA1	c1
#define CA2	c2
#define CA3	c3
#define CA4	c4
#define CA5	c5
#define CA6	c6
#define CA7	c7

#define DDC	ddc
#define CRA	clr

#define T0	x9
#define T1	x10
#define T2	x11
#define T3	x12
#define T4	x13
#define T5	x14
#define T6	x15

#define CT0	c9
#define CT1	c10
#define CT2	c11
#define CT3	c12
#define CT4	c13
#define CT5	c14
#define CT6	c15

#define CS0	c19
#define CS1	c20
#define CS2	c21
#define CS3	c22
#define CS4	c23
#define CS5	c24
#define CS6	c25
#define CS7	c26
#define CS8	c27
#define CS9	c28

#define S0	x19
#define S1	x20
#define S2	x21
#define S3	x22
#define S4	x23
#define S5	x24
#define S6	x25
#define S7	x26
#define S8	x27
#define S9	x28


.text

.global c_out_3
.type c_out_3,%function
c_out_3:
		MV	T5,	A0
		MV	CA0,	CA1
		MV	CA1,	CA2
		MV	CA2,	CA3
		b c_out

.global c_out_5
.type c_out_5,%function
c_out_5:
		MV	T5,	A0
		MV	CA0,	CA1
		MV	CA1,	CA2
		MV	CA2,	CA3
		MV	CA3,	CA4
		MV	CA4,	CA5
		b c_out


.global c_out_7
.type c_out_7,%function
c_out_7:
		MV	T5,	A0
		MV	CA0,	CA1
		MV	CA1,	CA2
		MV	CA2,	CA3
		MV	CA3,	CA4
		MV	CA4,	CA5
		MV	CA5,	CA6
		MV	CA6,	CA7
		b c_out


.global c_out
.type c_out,%function
c_out:
		sub	sp, sp, #256

		SC	S2, [sp, #(16*0)]
		SC	S3, [sp, #(16*1)]
		SC	S4, [sp, #(16*2)]
		SC	S5, [sp, #(16*3)]
		SC	S6, [sp, #(16*4)]
		SC	lr, [sp, #(16*5)]
		SC	S0, [sp, #(16*6)]
		SC	S1, [sp, #(16*7)]
		SC	S7, [sp, #(16*8)]
		SC	S8, [sp, #(16*9)]
		SC	S9, [sp, #(16*10)]


//tt:
//		auipcc	ct0, %captab_pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
//		cincoffset	ct0, ct0, %pcrel_lo(tt)

#if 0
//todo: cvtp here also doesnt work without problem DDC_RELATIVE flag
		mrs CT0, ctpidr_el0
		LC	T0, [CT0, #0]
		cvtp	CT0, T0
#else
//so, we contruct the local_cap_store cap manually. 
		ldr	T0, =0
		ldr	T1, =(CVM_MAX_SIZE - 0x2000000 + 0x1000)
		add	T0, T0, T1
//
#endif


//		clc	cs2, COMP_DDC(ct0) //my ddc
//		clc	cs3, HC_PCC(ct0) //hostcall code sealed
//		clc	cs4, MON_DDC(ct0) //mon.ddc sealed
//		clc	ct1, RET_COMP_DDC(ct0)
//		clc	ct0, RET_COMP_PPC(ct0)

		LC	CS2, [T0, #COMP_DDC]
		LC	CS3, [T0, #HC_PCC]
		LC	CS4, [T0, #MON_DDC]
		LC	CT1, [T0, #RET_COMP_DDC]
		LC	CT0, [T0, #RET_COMP_PPC]

		MV	CT2, CS2

//		CInvoke cs3, cs4
		blrs c29, CS3, CS4


.global ret_from_monitor
ret_from_monitor:
//		clc	cs2,  (16*0)(csp)
//		clc	cs3,  (16*1)(csp)
//		clc	cs4,  (16*2)(csp)
//		clc	cs5,  (16*3)(csp)
//		clc	cs6,  (16*4)(csp)
//		clc	cra,  (16*5)(csp)
//		clc	cs0,  (16*6)(csp)
//		clc	cs1,  (16*7)(csp)
//		clc	cs7,  (16*8)(csp)
//		clc	cs8,  (16*9)(csp)
//		clc	cs9,  (16*10)(csp)
//		clc	cs10,  (16*11)(csp)
//		clc	cs11,  (16*12)(csp)

		LC	S2, [sp, #(16*0)]
		LC	S3, [sp, #(16*1)]
		LC	S4, [sp, #(16*2)]
		LC	S5, [sp, #(16*3)]
		LC	S6, [sp, #(16*4)]
		LC	lr, [sp, #(16*5)]
		LC	S0, [sp, #(16*6)]
		LC	S1, [sp, #(16*7)]
		LC	S7, [sp, #(16*8)]
		LC	S8, [sp, #(16*9)]
		LC	S9, [sp, #(16*10)]



//		addi	sp, sp, 112
//		cincoffset	csp, csp, 256
		add	csp, csp, #256

		ret


.global syscall_handler
.type syscall_handler,%function
syscall_handler:
	brk 0



//extern copy_from_cap(void *dst, void *src_cap_location, int len);
.global copy_from_cap
.type copy_from_cap,%function
copy_from_cap:
	LC	CT1, [A1]
	add	A2, A0, A2

9:
	ldr A4, [CT1]
	str A4, [A0]
	add A0, A0, 8
	add CT1, CT1, 8
	cmp A0, A2
	b.lo 9b

	ret


//extern copy_to_cap(void *src_cap_location, void *src, int len);
.global copy_to_cap
.type copy_to_cap,%function
copy_to_cap:
    ldr c9, [x0]         // Load 64-bit value from address in x0 to x9
    add x2, x1, x2       // Calculate destination address (x1 + x2)

10:
    ldr x4, [x1]         // Load 64-bit value from address in x1 to x4
    str x4, [c9]      // Store capability-guarded value from x4 to address in x9
    add x1, x1, #8       // Increment source address by 8
    add c9, c9, #8       // Increment destination capability address by 8
    cmp x1, x2           // Compare source address with destination address
    b.lo 10b             // Branch to label 10 if x1 is less than x2

    ret

