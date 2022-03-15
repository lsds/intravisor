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

.global c_out_2
.type c_out_2,%function
.option capmode

c_out_2:
		move	t5,	a0
		move	a0,	a1
		move	a1,	a2

.global c_out
.type c_out,%function
.option capmode
c_out:
//		addi	csp, csp, -112
		cincoffset	csp, csp, -112
		csc	cs2,  (16*0)(csp)
		csc	cs3,  (16*1)(csp)
		csc	cs4,  (16*2)(csp)
		csc	cs5,  (16*3)(csp)
		csc	cs6,  (16*4)(csp)

		csc	cra,  (16*5)(csp)
		csc	cs0,  (16*6)(csp)

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
//		addi	sp, sp, 112
		cincoffset	csp, csp, 112

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
//sp here is cap-relative and we need to translate it into absolute. we add the base of the compartment to sp prior updating DDC
//		cspecialr	cs6, ddc
//		cgetbase	s4, cs6
//      add     sp, sp, s4

//we write unsealed DDC into DDC
		cspecialw	ddc, ct6 //dcc-pcc should be the same 

//now we should again make relative to our DDC, so absolute -> relative
//in the case of nested layers with the same base, there is no need in these two changes -- SP is the same because the bottom is the same

		csc	csp, -64(csp)	// lets save sp cap 

		cincoffset	csp, csp, -112
		csc	cs0, 0(csp)
		csc	cra, 16(csp)
		cincoffset	cs0, csp, 112

		jal syscall

tt2:
		auipcc	ct0, %captab_pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		cincoffset	ct0, ct0, %pcrel_lo(tt2)
		clc	ct0, 0(ct0)

		clc	ct1, RET_TO_INNER_DDC(ct0)
		clc	ct2, INNER_DDC(ct0)
		clc	ct0, RET_TO_INNER_PPC(ct0)

		clc	cs0, 0(csp)
		clc	cra, 16(csp)

		addi	sp, sp, 112

		cspecialw	ddc, ct2

		csc	csp, 64(csp)	// lets save sp cap 

//todo: sanitize registers
		CInvoke ct0, ct1
