#if 0
#define COMP_DDC (16*2)
#define HC_PCC (16*3)
#define MON_DDC (16*4)
//5--6
#define RA  (16*7)
#define RET_COMP_PPC (16*11)
#define RET_COMP_DDC (16*12)
#define RET_CINV2_PPC (16*13)
#else
#define COMP_DDC(A)		[A, #32]
#define HC_PCC(A)		[A, #48]
#define MON_DDC(A)		[A, #64]
//5--6
#define RA(A)			[A, #112]
#define RET_COMP_PPC(A)		[A, #176]
#define RET_COMP_DDC(A)		[A, #192]
#define RET_CINV2_PPC(A)	[A, #208]
#endif

//todo:
//  lui        t0, %hi(symbol)     // R_RISCV_HI20
//  addi       t0, t0, %lo(symbol) // R_RISCV_LO12_I


#define MV	mov
#define LC	ldr
#define SC	str

#define LD	ldr
#define SD	str

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


.global cinv
.type cinv,%function
cinv:
		MV	T0, A0
//		lc	ca2, (16*2)(A1)
//		sc	ca2, COMP_DDC(T0)	//compartment ddc
		ldr	CA2, [A1, #32]
		str	CA2, COMP_DDC(T0)

//		lc	ca3, (16*3)(a1)
//		sc	ca3, HC_PCC(t0)	//hostcalls code
		ldr	CA3, [A1, #48]
		str	CA3, HC_PCC(T0)

//		lc	ca4, (16*4)(a1)
//		sc	ca4, MON_DDC(t0)	//sealed mon ddc
		ldr	CA4, [A1, #64]
		str	CA4, MON_DDC(T0)


//		lc	ca5, (16*5)(a1)
//		sc	ca5, RET_CINV2_PPC(t0)	//ret into mon as OCALL
		ldr	CA5, [A1, #80]
		str	CA5, RET_CINV2_PPC(T0)


//		lc	ca6, (16*6)(a1)
//		sc	ca6, RET_COMP_PPC(t0)	//ret from mon sealed PPC
		ldr	CA6, [A1, #96]
		str	CA6, RET_COMP_PPC(T0)

//		lc	ca0, (16*1)(a1)
//		sc	ca0, RET_COMP_DDC(t0)	//sealed data cap for ret from mon, the same as ca1
		ldr	CA0, [A1, #16]
		str	CA0, RET_COMP_DDC(T0)


//		lc	ca0, (16*7)(a1)
		ldr	CA0, [A1, #112]


//todo: run hybrid cap-vms, see riscv arch
//		lc	ca6, (16*8)(a1)
		ldr	CA6, [A1, #128]

//		cmove	ctp, ca6
//		cmove	csp, ca0
		msr ctpidr_el0, CA6
		mov csp, CA0


//we need something better
//		cmove	cra, ca0
		mov	clr, CA0

//		lc	ca0, (16*0)(a1)
//		lc	ca2, (16*2)(a1)
//		lc	ca1, (16*1)(a1)
		ldr	CA0, [A1, #0]
		ldr	CA2, [A1, #32]
		ldr	CA1, [A1, #16]

//		cspecialw	ddc, ca2
		msr		DDC, CA2

//		CInvoke ca0, ca1
		blrs c29, CA0, CA1 //the same as CInvoke, c29 = unsealed ca1



.global hostcall_asm
.type hostcall_asm,%function
hostcall_asm:
//only pure-cap supported

//		cspecialw	ddc, ct6 //dcc-pcc should be the same 
		msr		DDC, c29 //c29 -- unsealed ca1 from blrs

//		sc	csp, -64(sp)	// lets save cap 
		MV	CT3,	csp
		SC	CT3, [sp, #-64]	// lets save cap 


//		addi	sp, sp, -112
		sub	sp, sp, #112

//		sd	s0, 0(sp)
//		sd	ra, 16(sp)
		SD	S0, [sp, #0]
		SD	clr, [sp, #16]

//		addi	s0,sp, 112
		add	S0,sp, #112

//		sc	ct0, -16(s0)	//ret_from_mon pcc
//		sc	ct1, -32(s0)	//reg_from_mod ignore
//		sc	ct2, -48(s0)	//comp ddc unsealed

		SC	CT0, [S0, #-16]	//ret_from_mon pcc
		SC	CT1, [S0, #-32]	//reg_from_mod ignore
		SC	CT2, [S0, #-48]	//comp ddc unsealed


//		jal hostcall
		bl hostcall

//		lc	ct0, -16(s0)	//ret_from_mon pcc
//		lc	ct1, -32(s0)	//ret_from_mon ignore
//		lc	ct2, -48(s0)	//comp ddc unsealed

		LC	CT0, [S0, #-16]	//ret_from_mon pcc
		LC	CT1, [S0, #-32]	//ret_from_mon ignore
		LC	CT2, [S0, #-48]	//comp ddc unsealed


//		ld	s0, 0(sp)
//		ld	ra, 16(sp)

		LD	S0, [sp, #0]
		LD	clr, [sp, #16]

//		addi	sp, sp, 112
		add	sp, sp, #112

//only ret as pure
//		lc	csp, -64(sp)
		LC	CT3, [sp, #-64]
		MV	csp, CT3

//		cspecialw	ddc, ct2
		msr		DDC, CT2

//		CInvoke ct0, ct1

		blrs c29, CT0, CT1 

.global st_cap
.type st_cap,%function
st_cap:
	str	CA1, [A0, #0]
	ret

.global cinv2_sp
.type cinv2_sp,%function
cinv2_sp:
		mov	csp, CA4


.global cinv2
.type cinv2,%function
cinv2:

		msr		ddc, CA3
		blrs c29, CA1, CA2


.global ret_from_cinv2
.type ret_from_cinv2,%function
ret_from_cinv2:
    BRK 0
