#define COMP_DDC (16*2)
#define HC_PCC (16*3)
#define MON_DDC (16*4)

#define HC_PCC2 (16*5)
#define MON_DDC2 (16*6)

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

//////////////////


.global c_out2_3
.type c_out2_3,%function
c_out2_3:
		MV	T5,	A0
		MV	CA0,	CA1
		MV	CA1,	CA2
		MV	CA2,	CA3
		b c_out2

.global c_out2_5
.type c_out2_5,%function
c_out2_5:
		MV	T5,	A0
		MV	CA0,	CA1
		MV	CA1,	CA2
		MV	CA2,	CA3
		MV	CA3,	CA4
		MV	CA4,	CA5
		b c_out2


.global c_out2_7
.type c_out2_7,%function
c_out2_7:
		MV	T5,	A0
		MV	CA0,	CA1
		MV	CA1,	CA2
		MV	CA2,	CA3
		MV	CA3,	CA4
		MV	CA4,	CA5
		MV	CA5,	CA6
		MV	CA6,	CA7
		b c_out2

.global c_out2
.type c_out2,%function
c_out2:
//		cincoffset	csp, csp, -256
		sub	csp, csp, #256

		SC	CS2, [csp, #(16*0)]
		SC	CS3, [csp, #(16*1)]
		SC	CS4, [csp, #(16*2)]
		SC	CS5, [csp, #(16*3)]
		SC	CS6, [csp, #(16*4)]
		SC	CRA, [csp, #(16*5)]
		SC	CS0, [csp, #(16*6)]
		SC	CS1, [csp, #(16*7)]
		SC	CS7, [csp, #(16*8)]
		SC	CS8, [csp, #(16*9)]
		SC	CS9, [csp, #(16*10)]
		SC	c29, [csp, #(16*11)]


#if 0
		adrp	CT0, local_cap_store
		add	CT0, CT0, :lo12:local_cap_store
#else
//so, we contruct the local_cap_store cap manually. 
		adr	CT0, #0
		gcbase	T0, CT0
		ldr	T1, =0xE001000
		add	T0, T0, T1
		cvtp	CT0, T0
#endif

//		clc	cs2, COMP_DDC(ct0) //my ddc
//		clc	cs3, HC_PCC(ct0) //hostcall code sealed
//		clc	cs4, MON_DDC(ct0) //mon.ddc sealed
//		clc	ct1, RET_COMP_DDC(ct0)
//		clc	ct0, RET_COMP_PPC(ct0)

		LC	CS2, [CT0, #COMP_DDC]
		LC	CS3, [CT0, #HC_PCC2]
		LC	CS4, [CT0, #MON_DDC2]
		LC	CT1, [CT0, #RET_COMP_DDC]
		LC	CT0, [CT0, #RET_COMP_PPC]

		MV	CT2, CS2

//		CInvoke cs3, cs4

		blrs c29, CS3, CS4


//////////////////


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
//		cincoffset	csp, csp, -256
		sub	csp, csp, #256

//		sc	cs2,  (16*0)(csp)
//		sc	cs3,  (16*1)(csp)
//		sc	cs4,  (16*2)(csp)
//		sc	cs5,  (16*3)(csp)
//		sc	cs6,  (16*4)(csp)
//		sc	cra,  (16*5)(csp)
//		sc	cs0,  (16*6)(csp)
//		sc	cs1,  (16*7)(csp)
//		sc	cs7,  (16*8)(csp)
//		sc	cs8,  (16*9)(csp)
//		sc	cs9,  (16*10)(csp)
//		sc	cs10,  (16*11)(csp)
//		sc	cs11,  (16*12)(csp)

		SC	CS2, [csp, #(16*0)]
		SC	CS3, [csp, #(16*1)]
		SC	CS4, [csp, #(16*2)]
		SC	CS5, [csp, #(16*3)]
		SC	CS6, [csp, #(16*4)]
		SC	CRA, [csp, #(16*5)]
		SC	CS0, [csp, #(16*6)]
		SC	CS1, [csp, #(16*7)]
		SC	CS7, [csp, #(16*8)]
		SC	CS8, [csp, #(16*9)]
		SC	CS9, [csp, #(16*10)]
		SC	c29, [csp, #(16*11)]


#if 0
		adrp	CT0, local_cap_store
		add	CT0, CT0, :lo12:local_cap_store
#else
//so, we contruct the local_cap_store cap manually. 
		adr	CT0, #0
		gcbase	T0, CT0
		ldr	T1, =0xE001000
		add	T0, T0, T1
		cvtp	CT0, T0
#endif

//		clc	cs2, COMP_DDC(ct0) //my ddc
//		clc	cs3, HC_PCC(ct0) //hostcall code sealed
//		clc	cs4, MON_DDC(ct0) //mon.ddc sealed
//		clc	ct1, RET_COMP_DDC(ct0)
//		clc	ct0, RET_COMP_PPC(ct0)

		LC	CS2, [CT0, #COMP_DDC]
		LC	CS3, [CT0, #HC_PCC]
		LC	CS4, [CT0, #MON_DDC]
		LC	CT1, [CT0, #RET_COMP_DDC]
		LC	CT0, [CT0, #RET_COMP_PPC]

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


		LC	CS2, [csp, #(16*0)]
		LC	CS3, [csp, #(16*1)]
		LC	CS4, [csp, #(16*2)]
		LC	CS5, [csp, #(16*3)]
		LC	CS6, [csp, #(16*4)]
		LC	CRA, [csp, #(16*5)]
		LC	CS0, [csp, #(16*6)]
		LC	CS1, [csp, #(16*7)]
		LC	CS7, [csp, #(16*8)]
		LC	CS8, [csp, #(16*9)]
		LC	CS9, [csp, #(16*10)]
		LC	c29, [csp, #(16*11)]



//		cincoffset	csp, csp, 256
		add	csp, csp, #256

		ret


.global syscall_handler
.type syscall_handler,%function
syscall_handler:
//we write unsealed DDC into DDC
//		cspecialr	ct2, ddc
//		cspecialw	ddc, ct6 //dcc-pcc should be the same 

		mrs 	CT2, DDC
		msr 	DDC, c29



//now we should again make relative to our DDC, so absolute -> relative
//in the case of nested layers with the same base, there is no need in these two changes -- SP is the same because the bottom is the same

//		cincoffset	csp, csp, -112
//		csc	cs0, 0(csp)
//		csc	cra, 16(csp)
//		csc ct0, 32(csp)
//		csc ct1, 48(csp)
//		csc ct2, 64(csp)
//		cincoffset	cs0, csp, 112

		sub	csp, csp, #112
		SC	CS0, [csp, #(0*16)]
		SC	CRA, [csp, #(1*16)]
		SC	CT0, [csp, #(2*16)]
		SC	CT1, [csp, #(3*16)]
		SC	CT2, [csp, #(4*16)]
		add	CS0, csp, #112

//jsc:
//		auipcc	ct0, %captab_pcrel_hi(syscall)    // R_RISCV_PCREL_HI20
//		cincoffset	ct0, ct0, %pcrel_lo(jsc)
//		clc	ct0, 0(ct0)
//		cjalr	cra, ct0

		adrp	CT0, syscall
		add	CT0, CT0, :lo12:syscall

		blr	CT0

//		clc	cs0, 0(csp)
//		clc	cra, 16(csp)
//		clc ct0, 32(csp)
//		clc ct1, 48(csp)
//		clc ct2, 64(csp)

		LC	CS0, [csp, #(0*16)]
		LC	CRA, [csp, #(1*16)]
		LC	CT0, [csp, #(2*16)]
		LC	CT1, [csp, #(3*16)]
		LC	CT2, [csp, #(4*16)]

//		cincoffset	csp, csp, 112
		add	csp, csp, #112

//		cspecialw	ddc, ct2
		msr 	DDC, CT2

//todo: sanitize registers
//		CInvoke ct0, ct1

		blrs c29, CT0, CT1 
