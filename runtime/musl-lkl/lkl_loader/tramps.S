#define COMP_DDC (16*2)
#define HC_PCC (16*3)
#define MON_DDC (16*4)
//5--6
#define RA  (16*7)
#define RET_COMP_PPC (16*11)
#define RET_COMP_DDC (16*12)

#define RET_CINV2_PPC (16*13)

#define CAPF (16*10)

//#define SIM 1

.text

#ifndef SIM
//.align 12
.global _dlstart
.type _dlstart,%function
_dlstart:
		tail _dlstart_asm
#endif

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

#if SIM
tt:
		auipc	t0, %pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		addi       t0, t0, %pcrel_lo(tt)
		ld	t0, 0(t0)

		ld	s3, HC_PCC(t0) //ppc
		ld	t1, RET_COMP_DDC(t0)
		ld	t0, RET_COMP_PPC(t0)

		jr s3
#else
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
#endif


.global o_out
.type o_out,%function
o_out:
tt_o:
		auipc	t0, %pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		addi       t0, t0, %pcrel_lo(tt_o)
		ld	t0, 0(t0)

		lc	cs2, COMP_DDC(t0) //my ddc
		lc	cs3, RET_CINV2_PPC(t0) //hostcall code sealed
		lc	cs4, MON_DDC(t0) //mon.ddc sealed

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

//extern int extern int read_cap(void *dst, unused, int len);
.global read_cap
.type read_cap,%function
read_cap:
#ifndef SIM
		lui	t5, 0xe001
		lc	ct1, CAPF(t5)

		lui	a1, 0 //why?
		add	a2, a0, a2
7:
		ld.cap a4, 0(ct1)
		sd a4, 0(a0)
		addi a0, a0, 8
		cincoffsetimm ct1, ct1, 8
		bltu a0, a2, 7b

#else
tt_read:
		auipc	t5, %pcrel_hi(local_cap_store)    // R_RISCV_PCREL_HI20
		addi       t5, t5, %pcrel_lo(tt_read)
		ld	t5, 0(t5)

		ld	a1, CAPF(t5)

		add	a2, a0, a2

7:
		ld a4, 0(a1)
		sd a4, 0(a0)
		addi a0, a0, 8
		addi a1, a1, 8

		bltu a0, a2, 7b
#endif
		ret

//extern int extern int write_cap(void *src, unused, int len);
.global write_cap
.type write_cap,%function
write_cap:
#ifndef SIM
		lui	t5, 0x1e001
		lc	ct1, CAPF(t5)

		lui	a1, 0
		add	a2, a0, a2
8:
		ld a4, 0(a0)
		sd.cap a4, 0(ct1)
		addi a0, a0, 8
		cincoffsetimm ct1, ct1, 8
		bltu a0, a2, 8b

		lui	a1, 65536
		addiw	a2, a1, -1
		and	ra, ra, a2
		or	ra, ra, a1
#endif
		ret


.global my_memcpy
.type my_memcpy,%function
my_memcpy:
		add	a2, a0, a2
8:
		ld a4, 0(a1)
		sd a4, 0(a0)
		addi a0, a0, 8
		addi a1, a1, 8
		bltu a0, a2, 8b

		ret


//extern copy_from_cap(void *dst, void *src_cap_location, int len);
.global copy_from_cap
.type copy_from_cap,%function
copy_from_cap:
		lc	ct1, 0(a1)
		add	a2, a0, a2

9:
		ld.cap a4, 0(ct1)
		sd a4, 0(a0)
		addi a0, a0, 8
		cincoffsetimm ct1, ct1, 8
		bltu a0, a2, 9b

		ret

//extern copy_to_cap(void *src_cap_location, void *src, int len);
.global copy_to_cap
.type copy_to_cap,%function
copy_to_cap:
		lc	ct1, 0(a0)
		add	a2, a1, a2

10:
		ld a4, 0(a1)
		sd.cap a4, 0(ct1)
		addi a1, a1, 8
		cincoffsetimm ct1, ct1, 8
		bltu a1, a2, 10b

		ret
