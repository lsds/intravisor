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

.global cinv_sp
.type cinv_sp,%function
cinv_sp:
	mv sp, a2

.global cinv
.type cinv,%function
cinv:
#ifdef SIM
//outdated
		mv	t0, a7
		sd	a2, COMP_DDC(t0)
		sd	a3, HC_PCC(t0)
		sd	a4, MON_DDC(t0)

		sd	a6, RET_COMP_PPC(t0)
		sd	a2, RET_COMP_DDC(t0)

		jr a0

#else

		mv	t0, a0
		lc	ca2, (16*2)(a1)
		sc	ca2, COMP_DDC(t0)	//compartment ddc

		lc	ca3, (16*3)(a1)
		sc	ca3, HC_PCC(t0)	//hostcalls code

		lc	ca4, (16*4)(a1)
		sc	ca4, MON_DDC(t0)	//sealed mon ddc

		lc	ca5, (16*5)(a1)
		sc	ca5, RET_CINV2_PPC(t0)	//ret into mon as OCALL

		lc	ca6, (16*6)(a1)
		sc	ca6, RET_COMP_PPC(t0)	//ret from mon sealed PPC

		lc	ca0, (16*1)(a1)
		sc	ca0, RET_COMP_DDC(t0)	//sealed data cap for ret from mon, the same as ca1

		lc	ca0, (16*7)(a1)

		cgettag		s4, ca0
		bnez     s4, .cinv_run_as_pure
        j       .cinv_next

.cinv_run_as_pure:
		lc	ca6, (16*8)(a1)
		cmove	ctp, ca6
		cmove	csp, ca0
.cinv_next:


//we need something better
		cmove	cra, ca0

		lc	ca0, (16*0)(a1)
		lc	ca2, (16*2)(a1)
		lc	ca1, (16*1)(a1)

		cspecialw	ddc, ca2
		CInvoke ca0, ca1
#endif

.global cinv2_sp
.type cinv2_sp,%function
cinv2_sp:
	mv sp, a4

.global cinv2
.type cinv2,%function
cinv2:
#ifndef SIM
#if 0
//hybrid, outdated
//why do we save S registers? we are caller
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
#endif

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


.global hostcall_asm
.type hostcall_asm,%function
hostcall_asm:
#ifndef SIM

//sp here is cap-relative and we need to translate it into absolute. we add the base of the compartment to sp prior updating DDC
		cgettag		s4, csp
		bnez     s4, .run_as_pure
        j       .run_as_hyb

.run_as_hyb:
		cspecialr	cs6, ddc
		cgetbase	s4, cs6
        add     sp, sp, s4
		cspecialw	ddc, ct6 //dcc-pcc should be the same 

		j	.next

.run_as_pure:
		cspecialw	ddc, ct6 //dcc-pcc should be the same 
		sc	csp, -64(sp)	// lets save cap 
.next:



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


		li			t3, 1
		cgetflags	t4, ct0
		and			t4, t4, t3

		bnez     t4, .ret_as_pure
        j       .ret_as_hyb

.ret_as_hyb:
//sp is absolute here and we should transle it to compartment-relative
		cgetbase	s4, ct2
		sub sp, sp, s4

		j	.ret_next

.ret_as_pure:
		lc	csp, -64(sp)
.ret_next:

		cspecialw	ddc, ct2

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

