#define COMP_DDC (16*2)
#define HC_PCC (16*3)
#define MON_DDC (16*4)
//5--6
#define RA  (16*7)
#define RET_COMP_PPC (16*11)
#define RET_COMP_DDC (16*12)

#define CAPF (16*10)

//#define SIM 1

.text

.global c_out_2
.type c_out_2,%function
.option capmode

c_out_2:
		move	t5,	a0
		cmove	ca0,	ca1
		cmove	ca1,	ca2


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
		cincoffset	csp, csp, 112

		cret


