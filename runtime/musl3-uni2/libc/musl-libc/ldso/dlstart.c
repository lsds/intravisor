#include <stddef.h>
#include <sys/dynv.h>
#include "dynlink.h"
#include "libc.h"

#ifndef START
#define START "_dlstart"
#endif

#ifndef SHARED
#define SHARED
#endif

#include "crt_arch.h"

#ifndef GETFUNCSYM
#define GETFUNCSYM(fp, sym, got) do { \
	hidden void sym(); \
	static void (*static_func_ptr)() = sym; \
	__asm__ __volatile__ ( "" : "+m"(static_func_ptr) : : "memory"); \
	*(fp) = static_func_ptr; } while(0)
#endif

#define AUX_TYPE(p) ((p)->a_type)
#define AUX_VAL(p) ((p)->a_un.a_val)
#define AUX_PTR(p) ((p)->a_un.a_ptr)
#define DYN_TAG(p) ((p).d_tag)
#define DYN_VAL(p) ((p).d_un.d_val)
#define DYN_PTR(p) ((p).d_un.d_ptr)

#if defined(__CHERI_PURE_CAPABILITY__)
hidden void _dlstart_c(uintptr_t *sp, size_t *dynv_raw, int argc, char *argv[], char *envp[], auxv_entry *auxv)
#else
hidden void _dlstart_c(uintptr_t *sp, size_t *dynv_raw)
#endif
{
	size_t i;
	auxv_entry aux_null = {0}, *aux[AUX_CNT];
	dynv_entry dyn[DYN_CNT] = {{0}};
	size_t *rel, rel_size, rel_count;
	Rel_t *rel_ptr;
	Rela_t *rela_ptr;
	char *base_rx;
#if !defined(__CHERI_PURE_CAPABILITY__)
	auxv_entry *auxv;
	int argc = *sp;
	char **argv = (void *)(sp+1);
	char **envp = argv+argc+1;
	for (i=0; envp[i]; i++);
	auxv = (void *)(envp+i+1);
#endif
	dynv_entry *dynv = (void *)dynv_raw;

	for (i=0; i<AUX_CNT; i++) aux[i] = &aux_null;
	for (i=0; auxv[i].a_type; i++) if (auxv[i].a_type<AUX_CNT)
		aux[auxv[i].a_type] = auxv + i;

#ifdef __CHERI_PURE_CAPABILITY__
	const _Bool is_interpreter = (AUX_PTR(aux[AT_CHERI_INTERP_RW_CAP]) != NULL);
	char *const rw_cap = AUX_PTR(aux[is_interpreter ?
	                                 AT_CHERI_INTERP_RW_CAP :
	                                 AT_CHERI_EXEC_RW_CAP]);
	char *const rx_cap = AUX_PTR(aux[is_interpreter ?
	                                 AT_CHERI_INTERP_RX_CAP :
	                                 AT_CHERI_EXEC_RX_CAP]);
#endif

#if DL_FDPIC
	struct fdpic_loadseg *segs, fakeseg;
	size_t j;
	if (dynv) {
		/* crt_arch.h entry point asm is responsible for reserving
		 * space and moving the extra fdpic arguments to the stack
		 * vector where they are easily accessible from C. */
		segs = ((struct fdpic_loadmap *)(sp[-1] ? sp[-1] : sp[-2]))->segs;
	} else {
		/* If dynv is null, the entry point was started from loader
		 * that is not fdpic-aware. We can assume normal fixed-
		 * displacement ELF loading was performed, but when ldso was
		 * run as a command, finding the Ehdr is a heursitic: we
		 * have to assume Phdrs start in the first 4k of the file. */
		base_rx = AUX_PTR(aux[AT_BASE]);
		if (!base_rx) {
			base_rx = __builtin_align_down(AUX_PTR(aux[AT_PHDR]), 4096);
		}
		segs = &fakeseg;
		segs[0].addr = base_rx;
		segs[0].p_vaddr = 0;
		segs[0].p_memsz = -1;
		Ehdr *eh = (void *)base_rx;
		Phdr *ph = (void *)(base_rx + eh->e_phoff);
		size_t phnum = eh->e_phnum;
		size_t phent = eh->e_phentsize;
		while (phnum-- && ph->p_type != PT_DYNAMIC)
			ph = (void *)((size_t)ph + phent);
		dynv = (void *)(base_rx + ph->p_vaddr);
	}
#endif

	for (i=0; dynv[i].d_tag; i++) if (dynv[i].d_tag<DYN_CNT)
		dyn[dynv[i].d_tag] = dynv[i];

#if DL_FDPIC
	for (i=0; i<DYN_CNT; i++) {
		if (i==DT_RELASZ || i==DT_RELSZ) continue;
		if (!dyn[i].d_tag) continue;
		for (j=0; DYN_VAL(dyn[i])-segs[j].p_vaddr >= segs[j].p_memsz; j++);
		DYN_VAL(dyn[i]) += segs[j].addr - segs[j].p_vaddr;
	}
	base_rx = 0;

	const Sym *syms = DYN_PTR(dyn[DT_SYMTAB]);

	rel = DYN_PTR(dyn[DT_RELA]);
	rel_size = DYN_VAL(dyn[DT_RELASZ]);
	for (; rel_size; rel+=3, rel_size-=3*sizeof(size_t)) {
		if (!IS_RELATIVE(rel[1], syms)) continue;
		for (j=0; rel[0]-segs[j].p_vaddr >= segs[j].p_memsz; j++);
		size_t *rel_addr = (void *)
			(rel[0] + segs[j].addr - segs[j].p_vaddr);
		if (R_TYPE(rel[1]) == REL_FUNCDESC_VAL) {
			*rel_addr += segs[rel_addr[1]].addr
				- segs[rel_addr[1]].p_vaddr
				+ syms[R_SYM(rel[1])].st_value;
			rel_addr[1] = DYN_PTR(dyn[DT_PLTGOT]);
		} else {
			size_t val = syms[R_SYM(rel[1])].st_value;
			for (j=0; val-segs[j].p_vaddr >= segs[j].p_memsz; j++);
			*rel_addptr = rel[2] + segs[j].addr - segs[j].p_vaddr + val;
		}
	}
#else
	/* If the dynamic linker is invoked as a command, its load
	 * address is not available in the aux vector. Instead, compute
	 * the load address as the difference between &_DYNAMIC and the
	 * virtual address in the PT_DYNAMIC program header. */

	// AT_BASE is always a raw 64-bit value.
	base_rx = AUX_PTR(aux[AT_BASE]);
#ifdef __CHERI_PURE_CAPABILITY__
	if (is_interpreter)
		base_rx = __builtin_cheri_address_set(rx_cap,
						      AUX_VAL(aux[AT_BASE]));
#endif

	if (!base_rx) {
		size_t phnum = AUX_VAL(aux[AT_PHNUM]);
		size_t phentsize = AUX_VAL(aux[AT_PHENT]);
		Phdr *ph = AUX_PTR(aux[AT_PHDR]);
#ifdef __CHERI_PURE_CAPABILITY__
		// Depending on ABI version AT_PHDR might not be a capability.
		ph = __builtin_cheri_address_set(rx_cap, ph);
#endif
		for (i=phnum; i--; ph = (void *)((char *)ph + phentsize)) {
			if (ph->p_type == PT_DYNAMIC) {
				base_rx = (char*)dynv - ph->p_vaddr;
				break;
			}
		}
	}

	/* MIPS uses an ugly packed form for GOT relocations. Since we
	 * can't make function calls yet and the code is tiny anyway,
	 * it's simply inlined here. */
	if (NEED_MIPS_GOT_RELOCS) {
		size_t local_cnt = 0;
		size_t *got = (void *)(base_rx + DYN_VAL(dyn[DT_PLTGOT]));
		for (i=0; dynv[i].d_tag; i++) if (dynv[i].d_tag==DT_MIPS_LOCAL_GOTNO)
			local_cnt = dynv[i].d_tag;
		for (i=0; i<local_cnt; i++) got[i] += (size_t)base_rx;
	}

	rel_ptr = (void *)(base_rx + DYN_VAL(dyn[DT_REL]));
	rel_count = DYN_VAL(dyn[DT_RELSZ]) / sizeof(Rel_t);
	for (; rel_count; rel_count--, rel_ptr++) {
		if (!IS_RELATIVE(rel_ptr->r_info, 0)) continue;
		size_t **rel_addr = (void *)(base_rx + rel_ptr->r_offset);
		*rel_addr = (void *)(base_rx + (size_t)*rel_addr);
	}

	rela_ptr = (void *)(base_rx + DYN_VAL(dyn[DT_RELA]));
	rel_count = DYN_VAL(dyn[DT_RELASZ]) / sizeof(Rela_t);
	for (; rel_count; rel_count--, rela_ptr++) {
		if (!IS_RELATIVE(rela_ptr->r_info, 0)) continue;
		char **rel_addr = (void *)(base_rx + rela_ptr->r_offset);
#if !defined(__CHERI_PURE_CAPABILITY__)
		*rel_addr = base_rx + rela_ptr->r_addend;
#else
#ifndef INTRAVISOR
		rel_addr = __builtin_cheri_address_set(rw_cap, rel_addr);
		char *v_address = base_rx + ((morello_reloc_cap_t *)rel_addr)->address;
		size_t len = ((morello_reloc_cap_t *)rel_addr)->length;
		size_t perms = ((morello_reloc_cap_t *)rel_addr)->perms;
		char *cap;
		char *cap_rx = __builtin_cheri_bounds_set_exact(v_address, len);
		char *cap_rw = __builtin_cheri_bounds_set_exact(
			__builtin_cheri_address_set(rw_cap, v_address), len);
		switch (perms) {
		  case MORELLO_RELA_PERM_R:
		    cap = __builtin_cheri_perms_and(cap_rx,
				__CHERI_CAP_PERMISSION_GLOBAL__ | READ_CAP_PERMS);
		    break;
		  case MORELLO_RELA_PERM_RW:
		    cap = __builtin_cheri_perms_and(cap_rw,
				__CHERI_CAP_PERMISSION_GLOBAL__ | READ_CAP_PERMS | WRITE_CAP_PERMS);
		    break;
		  case MORELLO_RELA_PERM_RX:
		    cap = __builtin_cheri_perms_and(cap_rx,
				__CHERI_CAP_PERMISSION_GLOBAL__ | READ_CAP_PERMS | EXEC_CAP_PERMS);
		    break;
		  default:
		    cap = __builtin_cheri_perms_and(cap_rx, 0);
		}
		cap += rela_ptr->r_addend;
		*rel_addr = cap;
#endif
#endif
	}

	rel = (void *)(base_rx+DYN_VAL(dyn[DT_RELR]));
	rel_size = DYN_VAL(dyn[DT_RELRSZ]);
	size_t *relr_addr = 0;
	for (; rel_size; rel++, rel_size-=sizeof(size_t)) {
		if ((rel[0]&1) == 0) {
			relr_addr = (void *)(base_rx + rel[0]);
			*relr_addr++ += (size_t)base_rx;
		} else {
			for (size_t i=0, bitmap=rel[0]; bitmap>>=1; i++)
				if (bitmap&1)
					relr_addr[i] += (size_t)base_rx;
			relr_addr += 8*sizeof(size_t)-1;
		}
	}
#endif

	stage2_func dls2;
	GETFUNCSYM(&dls2, __dls2, base_rx+DYN_VAL(dyn[DT_PLTGOT]));
#if defined(__CHERI_PURE_CAPABILITY__)
	dls2 = __builtin_cheri_seal_entry(dls2);
	dls2((void *)base_rx, (void *)rw_cap, sp, argc, argv, envp, (uintptr_t *)auxv);
#else
	dls2((void *)base_rx, sp);
#endif
}
