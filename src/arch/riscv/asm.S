#define COMP_DDC (16*2)
#define HC_PCC (16*3)
#define MON_DDC (16*4)
//5--6
#define RA  (16*7)
#define RET_COMP_PPC (16*11)
#define RET_COMP_DDC (16*12)

#define RET_CINV2_PPC (16*13)

//todo:
//  lui        t0, %hi(symbol)     // R_RISCV_HI20
//  addi       t0, t0, %lo(symbol) // R_RISCV_LO12_I

//#define SIM 1

.global cinv
.type cinv,%function
cinv:
#ifdef SIM
		mv	t0, a7
		sd	a2, COMP_DDC(t0)
		sd	a3, HC_PCC(t0)
		sd	a4, MON_DDC(t0)

		sd	a6, RET_COMP_PPC(t0)
		sd	a2, RET_COMP_DDC(t0)

		jr a0

#else
		mv	t0, a7
		sc	ca2, COMP_DDC(t0)	//compartment ddc
		sc	ca3, HC_PCC(t0)	//hostcalls code
		sc	ca4, MON_DDC(t0)	//sealed mon ddc

		sc	ca5, RET_CINV2_PPC(t0)	//ret into mon as OCALL
		sc	ca6, RET_COMP_PPC(t0)	//ret from mon sealed PPC
		sc	ca1, RET_COMP_DDC(t0)	//sealed data cap for ret from mon, the same as ca1

		cspecialw	ddc, ca2
		CInvoke ca0, ca1
#endif


.global cinv2
.type cinv2,%function
cinv2:
#ifndef SIM
		addi	sp, sp, -112
		sd	ra,  (8*1)(sp)
		sd	s0,  (8*2)(sp)
		sd	s1,  (8*3)(sp)
		sd	s2,  (8*4)(sp)
		sd	s3,  (8*5)(sp)
		sd	s4,  (8*6)(sp)
		sd	s5,  (8*7)(sp)
		sd	s6,  (8*8)(sp)
		sd	s7,  (8*9)(sp)

		cgetbase	s4, ca3	//take the bottom of the compartment
        sub     sp, sp, s4	//make sp cap-relative

		cspecialw	ddc, ca3
		CInvoke ca1, ca2

.global ret_from_cinv2
ret_from_cinv2:
		cspecialr	cs6, ddc
		cgetbase	s4, cs6
        add     sp, sp, s4

// 48 is the sp shift in wrap_ocall_exist. we omit epilogue in this function so we should move the stack manually
// in general it is very wrong design and shoud changed. instead of giving pointers to functions in CF_Calls, we should
// use a dedicated function that later calls our callback. then we will have defined routine inside compartments 
// and will avoid moving of the $sp.
//
// 0000000000322432 <portal_write>:
// ; static ssize_t portal_write(int id) {
//   322432: 01 11        	addi	sp, sp, -32
//   322434: 06 ec        	sd	ra, 24(sp)
//   322436: 22 e8        	sd	s0, 16(sp)
//   322438: 26 e4        	sd	s1, 8(sp)
//   32243a: 00 10        	addi	s0, sp, 32

		addi	sp, sp, 48
		addi	sp, sp, 32

		cspecialw	ddc, ct6 //dcc-pcc should be the same 

		ld	ra,  (8*1)(sp)
		ld	s0,  (8*2)(sp)
		ld	s1,  (8*3)(sp)
		ld	s2,  (8*4)(sp)
		ld	s3,  (8*5)(sp)
		ld	s4,  (8*6)(sp)
		ld	s5,  (8*7)(sp)
		ld	s6,  (8*8)(sp)
		ld	s7,  (8*9)(sp)

		addi	sp, sp, 112

		ret

#else
		jr	a1
#endif


.global tp_write
.type tp_write,%function
tp_write:
#ifndef SIM

//sp here is cap-relative and we need to translate it into absolute. we add the base of the compartment to sp prior updating DDC
		cspecialr	cs6, ddc
		cgetbase	s4, cs6
        add     sp, sp, s4

		cspecialw	ddc, ct6 //dcc-pcc should be the same 

#endif

		addi	sp, sp, -112
		sd	s0, 0(sp)
		sd	ra, 16(sp)
		addi	s0,sp, 112
#ifndef SIM
		sc	ct0, -16(s0)	//ret_from_mon pcc
		sc	ct1, -32(s0)	//reg_from_mod ignore
		sc	ct2, -48(s0)	//comp ddc unsealed
#else
		sd	t0, -16(s0)
		sd	t1, -32(s0)
		sd	t2, -48(s0)
#endif

		jal hostcall

#ifndef SIM
		lc	ct0, -16(s0)	//ret_from_mon pcc
		lc	ct1, -32(s0)	//ret_from_mon ignore
		lc	ct2, -48(s0)	//comp ddc unsealed
#else
		ld	t0, -16(s0)
		ld	t1, -32(s0)
		ld	t2, -48(s0)
#endif

		ld	s0, 0(sp)
		ld	ra, 16(sp)

		addi	sp, sp, 112
#ifndef SIM
		cspecialw	ddc, ct2

//sp is absolute here and we should transle it to compartment-relative
		cgetbase	s4, ct2
		sub sp, sp, s4

		CInvoke ct0, ct1
#else
		jr t0
#endif

.global st_cap
.type st_cap,%function
st_cap:
#ifndef SIM
	  sc ca1, 0(a0)
#else
	  sd a1, 0(a0)
#endif
	  ret

