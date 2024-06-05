#ifndef SHARED
#include <stddef.h>
#include <stdint.h>
#include <sys/auxv.h>
#include "elf.h"
#include "cap_perms.h"
#include "reloc.h"
#endif

__asm__(
".text \n"
".global " START "\n"
".type " START ",%function\n"
START ":\n"
"	mov x29, #0\n"
"	mov x30, #0\n"

#ifdef INTRAVISOR
"	sub csp, csp, 0x1000\n" //int argc, char **argv, char **envp, auxv_entry *auxv)
"	mov c0, csp\n"
"	sub csp, csp, 0x1000\n" //char **argv
"	mov c1, csp\n"
"	sub csp, csp, 0x1000\n" //char **envp
"	mov c2, csp\n"
"	sub csp, csp, 0x1000\n"//auxv_entry *auxv;
"	mov c3, csp\n"
"	mov c20, c0\n"
"	mov c21, c1\n"
"	mov c22, c2\n"
"	mov c23, c3\n"
"	adrp c19, __morello_args_init\n"
"	add c19, c19, #:lo12:__morello_args_init\n"
"	blr c19\n"
"	mov c0, c20\n"
"	mov c1, c21\n"
"	mov c2, c22\n"
"	mov c3, c23\n"
#endif

#ifndef SHARED
"	mov c20, c0\n"
"	mov c21, c1\n"
"	mov c22, c2\n"
"	mov c23, c3\n"
"	bl __morello_init_static\n"
#else
"	mov c5, c3\n"
"	mov c4, c2\n"
"	mov c3, c1\n"
"	mov c2, c0\n"
#endif
"	mov c0, csp\n"
".weak _DYNAMIC\n"
".hidden _DYNAMIC\n"
"	adrp c1, _DYNAMIC\n"
"	add c1, c1, #:lo12:_DYNAMIC\n"
"	alignd csp, csp, #4\n"
#ifndef SHARED
"	mov c2, c20\n"
"	mov c3, c21\n"
"	mov c4, c22\n"
"	mov c5, c23\n"
#endif
"	b " START "_c\n"
".size " START ", .-" START "\n"
);

#ifndef SHARED

// #ifdef CAP_RELOCS
typedef struct {
	uint64_t location;	/* Capability location */
	uint64_t base;		/* Object referred to by the capability */
	size_t offset;		/* Offset in the object */
	size_t size;		/* Size */
	size_t permissions;	/* Inverted permissions mask */
} cap_relocs_entry;

inline static void
__do_morello_cap_relocs(void *rw, void *rx)
{
	cap_relocs_entry *__cap_relocs_start, *__cap_relocs_end;

	__asm__ (
		".p2align 4\n"
		".weak __cap_relocs_start\n"
		"adrp 	%0, __cap_relocs_start\n"
		"add	%0, %0, :lo12:__cap_relocs_start\n"
		".weak __cap_relocs_end\n"
		"adrp 	%1, __cap_relocs_end\n"
		"add	%1, %1, :lo12:__cap_relocs_end" : "=C"(__cap_relocs_start), "=C"(__cap_relocs_end));

	for (const cap_relocs_entry *r = __cap_relocs_start; r != __cap_relocs_end; r++) {
		if (r->base) { // if capability is not null
			void *cap = NULL;
			size_t perm = ~r->permissions;
			_Bool is_fun_ptr = perm & __CHERI_CAP_PERMISSION_PERMIT_EXECUTE__;
			_Bool is_writable = perm & __CHERI_CAP_PERMISSION_PERMIT_STORE__;
			if (is_writable) {
				cap = __builtin_cheri_address_set(rw, r->base);
			} else {
				cap = __builtin_cheri_address_set(rx, r->base);
			}
			cap = __builtin_cheri_perms_and(cap, perm);
			cap = __builtin_cheri_bounds_set_exact(cap, r->size);
			cap = __builtin_cheri_offset_set(cap, r->offset);
			if (is_fun_ptr) {
				// RB-seal function pointer
				cap = __builtin_cheri_seal_entry(cap);
			}
			// store capability
			void **loc = __builtin_cheri_address_set(rw, r->location);
			loc = __builtin_cheri_bounds_set_exact(loc, sizeof(void *));
			*loc = cap;
		}
	}
}

inline static void
__do_morello_relative_relocs(void *rw, void *rx)
{
	Elf64_Rela *__rela_dyn_start, *__rela_dyn_end;
	__asm__ (
		".p2align 4\n"
		".weak __rela_dyn_start\n"
		".hidden __rela_dyn_start\n"
		"adrp 	%0, __rela_dyn_start\n"
		"add	%0, %0, :lo12:__rela_dyn_start\n"
		".weak __rela_dyn_end\n"
		".hidden __rela_dyn_end\n"
		"adrp 	%1, __rela_dyn_end\n"
		"add	%1, %1, :lo12:__rela_dyn_end"  : "=C"(__rela_dyn_start), "=C"(__rela_dyn_end));

	for (const Elf64_Rela *r = __rela_dyn_start; r != __rela_dyn_end; r++) {
		if (r->r_info != R_MORELLO_RELATIVE) continue;
		void *cap = NULL;
		void **loc = __builtin_cheri_address_set(rw, r->r_offset);
		const morello_reloc_cap_t *u = (morello_reloc_cap_t *)loc;
		switch (u->perms) {
			case MORELLO_RELA_PERM_R:
				cap = __builtin_cheri_perms_and(rx, __CHERI_CAP_PERMISSION_GLOBAL__ | READ_CAP_PERMS);
				break;
			case MORELLO_RELA_PERM_RW:
				cap = __builtin_cheri_perms_and(rw, __CHERI_CAP_PERMISSION_GLOBAL__ | READ_CAP_PERMS | WRITE_CAP_PERMS);
				break;
			case MORELLO_RELA_PERM_RX:
				cap = __builtin_cheri_perms_and(rx, __CHERI_CAP_PERMISSION_GLOBAL__ | READ_CAP_PERMS | EXEC_CAP_PERMS);
				break;
			default:
				cap = __builtin_cheri_perms_and(rx, 0);
				break;
		}
		cap = __builtin_cheri_address_set(cap, u->address);
		cap = __builtin_cheri_bounds_set_exact(cap, u->length);
		cap = cap + r->r_addend;
		if (u->perms == MORELLO_RELA_PERM_RX) {
			cap = __builtin_cheri_seal_entry(cap);
		}
		*loc = cap;
	}
}

void
__morello_init_static(int argc, char **argv, char **envp, auxv_entry *auxv)
{
	void *rw = NULL, *rx = NULL;
	size_t phnum = 0, phent = 0;
	Elf64_Phdr *ph = NULL;
	for (; auxv->a_type; auxv++) {
		if (auxv->a_type == AT_CHERI_EXEC_RW_CAP) {
			rw = auxv->a_un.a_ptr; // used to derive read-only and rw objects
		} else if (auxv->a_type == AT_CHERI_EXEC_RX_CAP) {
			rx = auxv->a_un.a_ptr; // used to derive function pointers
		} else if (auxv->a_type == AT_PHDR) {
			ph = auxv->a_un.a_ptr;
		} else if (auxv->a_type == AT_PHNUM) {
			phnum = auxv->a_un.a_val;
		} else if (auxv->a_type == AT_PHENT) {
			phent = auxv->a_un.a_val;
		}
		if (rw && rx && ph && phnum && phent) {
			break;
		}
	}

	while(phnum--) {
		if (ph->p_type == PT_INTERP) {
			return;
		}
		ph = (void *)((char *)ph + phent);
	}

	__do_morello_cap_relocs(rw, rx);
	__do_morello_relative_relocs(rw, rx);
}
#endif

//#define BBB 0x440200000
#define BBB 0x440000000

void
__morello_args_init(int *argc, char *argv, char *envp, auxv_entry *auxv)
{
	*argc = 2;
	intcap_t *i = (intcap_t *) argv;
	intcap_t *e = (intcap_t *) envp;
//
	i[0]=&argv[500];
	i[1]=&argv[600];
	i[2]=0;
	argv[500]='/';
	argv[501]='l';
	argv[502]='d';
	argv[503]='s';
	argv[504]='o';
	argv[505]='\0';

	argv[600]='/';
	argv[601]='a';
	argv[602]='p';
	argv[603]='p';
	argv[604]='1';
	argv[605]='\0';
//
#if 1
	e[0] = &envp[500];
#else
	e[0] = 0;
#endif
	e[1] = 0;

//LD_LIBRARY_PATH
	envp[500] = 'L';
	envp[501] = 'D';
	envp[502] = '_';
	envp[503] = 'L';
	envp[504] = 'I';
	envp[505] = 'B';
	envp[506] = 'R';
	envp[507] = 'A';
	envp[508] = 'R';
	envp[509] = 'Y';
	envp[510] = '_';
	envp[511] = 'P';
	envp[512] = 'A';
	envp[513] = 'T';
	envp[514] = 'H';
	envp[515] = '=';
	envp[516] = '/';
	envp[517] = 'u';
	envp[518] = 's';
	envp[519] = 'r';
	envp[520] = '/';
	envp[521] = 'l';
	envp[522] = 'i';
	envp[523] = 'b';
	envp[524] = '\0';
//

	auxv[0].a_type = AT_IGNORE;
	auxv[0].a_un.a_val = 0;

	auxv[1].a_type = AT_EXECFD;
	auxv[1].a_un.a_val = 5;

	auxv[2].a_type = AT_PHDR;
	auxv[2].a_un.a_ptr = __builtin_cheri_address_set( __builtin_cheri_global_data_get(),BBB + 0x40);

	auxv[3].a_type = AT_PHENT;
	auxv[3].a_un.a_val = 56;

	auxv[4].a_type = AT_PHNUM;
	auxv[4].a_un.a_val = 8;

	auxv[5].a_type = AT_PAGESZ;
	auxv[5].a_un.a_val = 4096;

	auxv[6].a_type = AT_BASE;
	auxv[6].a_un.a_ptr = __builtin_cheri_address_set(__builtin_cheri_program_counter_get(),BBB);

	auxv[7].a_type = AT_HWCAP;
	auxv[7].a_un.a_val = 0;

	auxv[8].a_type = AT_CHERI_EXEC_RX_CAP;
	auxv[8].a_un.a_ptr = __builtin_cheri_address_set(__builtin_cheri_program_counter_get(),BBB);

	auxv[9].a_type = AT_CHERI_EXEC_RW_CAP;
	auxv[9].a_un.a_ptr = __builtin_cheri_address_set( __builtin_cheri_global_data_get(),BBB);

	auxv[10].a_type = AT_NULL;
	auxv[10].a_un.a_val = 0;
}
