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


//#define SIM 1

.text

.global c_out_3
.type c_out_3,%function
c_out_3:
		move	t5,	a0
		cmove	ca0,	ca1
		cmove	ca1,	ca2
		cmove	ca2,	ca3
		j c_out

.global c_out_5
.type c_out_5,%function
c_out_5:
		move	t5,	a0
		cmove	ca0,	ca1
		cmove	ca1,	ca2
		cmove	ca2,	ca3
		cmove	ca3,	ca4
		cmove	ca4,	ca5
		j c_out


.global c_out_7
.type c_out_7,%function
c_out_7:
		move	t5,	a0
		cmove	ca0,	ca1
		cmove	ca1,	ca2
		cmove	ca2,	ca3
		cmove	ca3,	ca4
		cmove	ca4,	ca5
		cmove	ca5,	ca6
		cmove	ca6,	ca7
		j c_out


.global c_out
.type c_out,%function
.option capmode
c_out:
//		addi	csp, csp, -256
		cincoffset	csp, csp, -256
		csc	cs2,  (16*0)(csp)
		csc	cs3,  (16*1)(csp)
		csc	cs4,  (16*2)(csp)
		csc	cs5,  (16*3)(csp)
		csc	cs6,  (16*4)(csp)

		csc	cra,  (16*5)(csp)
		csc	cs0,  (16*6)(csp)

		csc	cs1,  (16*7)(csp)

		csc	cs7,  (16*8)(csp)
		csc	cs8,  (16*9)(csp)
		csc	cs9,  (16*10)(csp)
		csc	cs10,  (16*11)(csp)
		csc	cs11,  (16*12)(csp)


tt:
		auipcc	ct0, %captab_pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		cincoffset	ct0, ct0, %pcrel_lo(tt)

		clc	ct0, 0(ct0)

		clc	cs2, COMP_DDC(ct0) //my ddc
		clc	cs3, HC_PCC(ct0) //hostcall code sealed
		clc	cs4, MON_DDC(ct0) //mon.ddc sealed


		clc	ct1, RET_COMP_DDC(ct0)
		clc	ct0, RET_COMP_PPC(ct0)

		cmove	ct2, cs2
		CInvoke cs3, cs4


.global ret_from_monitor
ret_from_monitor:
		clc	cs2,  (16*0)(csp)
		clc	cs3,  (16*1)(csp)
		clc	cs4,  (16*2)(csp)
		clc	cs5,  (16*3)(csp)
		clc	cs6,  (16*4)(csp)
		clc	cra,  (16*5)(csp)
		clc	cs0,  (16*6)(csp)

		clc	cs1,  (16*7)(csp)
		clc	cs7,  (16*8)(csp)
		clc	cs8,  (16*9)(csp)
		clc	cs9,  (16*10)(csp)
		clc	cs10,  (16*11)(csp)
		clc	cs11,  (16*12)(csp)


//		addi	sp, sp, 112
		cincoffset	csp, csp, 256

		cret


#if 0
//extern copy_from_cap(void *dst, void *src_cap_location, int len);
.global copy_from_cap
.type copy_from_cap,%function
copy_from_cap:
		clc	ct1, 0(ca1)
		add	a2, a0, a2

7:
		ld.cap a4, 0(ct1)
		sd a4, 0(a0)
		addi a0, a0, 8
		cincoffsetimm ct1, ct1, 8
		bltu a0, a2, 7b

		ret
#endif


.global syscall_handler
.type syscall_handler,%function
syscall_handler:
//we write unsealed DDC into DDC
		cspecialr	ct2, ddc
		cspecialw	ddc, ct6 //dcc-pcc should be the same 

//now we should again make relative to our DDC, so absolute -> relative
//in the case of nested layers with the same base, there is no need in these two changes -- SP is the same because the bottom is the same

		cincoffset	csp, csp, -112
		csc	cs0, 0(csp)
		csc	cra, 16(csp)
		csc ct0, 32(csp)
		csc ct1, 48(csp)
		csc ct2, 64(csp)
		cincoffset	cs0, csp, 112


jsc:
		auipcc	ct0, %captab_pcrel_hi(syscall)    // R_RISCV_PCREL_HI20
		cincoffset	ct0, ct0, %pcrel_lo(jsc)
		clc	ct0, 0(ct0)

		cjalr	cra, ct0
//tt2:
//		auipcc	ct0, %captab_pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
//		cincoffset	ct0, ct0, %pcrel_lo(tt2)
//		clc	ct0, 0(ct0)

//		clc	ct1, RET_TO_INNER_DDC(ct0)
//		clc	ct2, INNER_DDC(ct0)
//		clc	ct0, RET_TO_INNER_PPC(ct0)

		clc	cs0, 0(csp)
		clc	cra, 16(csp)

		clc ct0, 32(csp)
		clc ct1, 48(csp)
		clc ct2, 64(csp)

		cincoffset	csp, csp, 112

		cspecialw	ddc, ct2

//todo: sanitize registers
		CInvoke ct0, ct1
