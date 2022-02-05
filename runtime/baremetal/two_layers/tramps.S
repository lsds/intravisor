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

.global c_out
.type c_out,%function
c_out:
		addi	sp, sp, -112
		sd	s2,  (8*2)(sp)
		sd	s3,  (8*3)(sp)
		sd	s4,  (8*4)(sp)
		sd	s5,  (8*5)(sp)
		sd	s6,  (8*6)(sp)

#if 0
//previosly, there was a bug in QEMU -- JAL produced global RA but not pc.base relative. remove this in future
		cspecialr	cs2, ddc
		cgetbase	t1, cs2

		sub ra, ra, t1
#endif

		sd	ra,  (8*7)(sp)
		sd	s0,  (8*8)(sp)

tt:
		auipc	t0, %pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		addi       t0, t0, %pcrel_lo(tt)
		ld	t0, 0(t0)

		lc	cs2, COMP_DDC(t0) //my ddc
		lc	cs3, HC_PCC(t0) //hostcall code sealed
		lc	cs4, MON_DDC(t0) //mon.ddc sealed


		lc	ct1, RET_COMP_DDC(t0)
		lc	ct0, RET_COMP_PPC(t0)

		cmove	ct2, cs2
		CInvoke cs3, cs4


.global ret_from_monitor
ret_from_monitor:
		ld	s2,  (8*2)(sp)
		ld	s3,  (8*3)(sp)
		ld	s4,  (8*4)(sp)
		ld	s5,  (8*5)(sp)
		ld	s6,  (8*6)(sp)
		ld	ra,  (8*7)(sp)
		ld	s0,  (8*8)(sp)
		addi	sp, sp, 112

		ret



//extern copy_from_cap(void *dst, void *src_cap_location, int len);
.global copy_from_cap
.type copy_from_cap,%function
copy_from_cap:
		lc	ct1, 0(a1)
		add	a2, a0, a2

7:
		ld.cap a4, 0(ct1)
		sd a4, 0(a0)
		addi a0, a0, 8
		cincoffsetimm ct1, ct1, 8
		bltu a0, a2, 7b

		ret



.global syscall_handler
.type syscall_handler,%function
syscall_handler:

//sp here is cap-relative and we need to translate it into absolute. we add the base of the compartment to sp prior updating DDC
		cspecialr	cs6, ddc
		cgetbase	s4, cs6
        add     sp, sp, s4

//we write unsealed DDC into DDC
		cspecialw	ddc, ct6 //dcc-pcc should be the same 

//now we should again make relative to our DDC, so absolute -> relative
//in the case of nested layers with the same base, there is no need in these two changes -- SP is the same because the bottom is the same
		cgetbase	s4, ct6
        sub     sp, sp, s4

		addi	sp, sp, -112
		sd	s0, 0(sp)
		sd	ra, 16(sp)
		addi	s0,sp, 112

#if 0
//this will not work with nested switches, because comparments cannot store caps
//we dont store these caps on the stack anymore, we use a hostcall for that
		sc	ct0, -16(s0)	//ret_from_mon pcc
		sc	ct1, -32(s0)	//reg_from_mod ignore
		sc	ct2, -48(s0)	//comp ddc unsealed
#endif

		jal syscall

#ifndef SIM
//		lc	ct0, -16(s0)	//ret_from_mon pcc
//		lc	ct1, -32(s0)	//ret_from_mon ignore
//		lc	ct2, -48(s0)	//comp ddc unsealed
tt2:
		auipc	t0, %pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		addi       t0, t0, %pcrel_lo(tt2)
		ld	t0, 0(t0)

		lc	ct1, RET_TO_INNER_DDC(t0)
		lc	ct2, INNER_DDC(t0)
		lc	ct0, RET_TO_INNER_PPC(t0)

#else
		ld	t0, -16(s0)
		ld	t1, -32(s0)
		ld	t2, -48(s0)
#endif

		ld	s0, 0(sp)
		ld	ra, 16(sp)

		addi	sp, sp, 112
#ifndef SIM

//		current_comp --> absolute
		cspecialr	cs4, ddc
		cgetbase	s4, cs4
        add     sp, sp, s4

		cspecialw	ddc, ct2
// 		absolute --> return_comp

//sp is absolute here and we should transle it to compartment-relative
		cgetbase	s4, ct2
		sub sp, sp, s4

//todo: sanitize registers
		CInvoke ct0, ct1
#else
		jr t0
#endif

