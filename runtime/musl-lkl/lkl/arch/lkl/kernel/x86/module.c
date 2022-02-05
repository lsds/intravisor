/*  Kernel module help for x86.
    Copyright (C) 2001 Rusty Russell.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/moduleloader.h>
#include <linux/elf.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/bug.h>
#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/jump_label.h>
#include <linux/random.h>

#include <asm/page.h>
#include <asm/pgtable.h>
#include <asm/setup.h>

#if 1
#define DEBUGP(fmt, ...)				\
	printk(KERN_DEBUG fmt, ##__VA_ARGS__)
#else
#define DEBUGP(fmt, ...)				\
do {							\
	if (0)						\
		printk(KERN_DEBUG fmt, ##__VA_ARGS__);	\
} while (0)
#endif

void *module_alloc(unsigned long size)
{
	void *p;
	unsigned long order, aligned_size;
	aligned_size = (size + 4096-1) & (~(4096-1));
	p = vmalloc(aligned_size);
	p = (((unsigned long)p) + 4096-1) & (~(4096-1));
	return p;
}

// from arch/x86/include/asm/elf.h
/* x86-64 relocation types */
#define R_X86_64_NONE           0       /* No reloc */
#define R_X86_64_64             1       /* Direct 64 bit  */
#define R_X86_64_PC32           2       /* PC relative 32 bit signed */
#define R_X86_64_GOT32          3       /* 32 bit GOT entry */
#define R_X86_64_PLT32          4       /* 32 bit PLT address */
#define R_X86_64_COPY           5       /* Copy symbol at runtime */
#define R_X86_64_GLOB_DAT       6       /* Create GOT entry */
#define R_X86_64_JUMP_SLOT      7       /* Create PLT entry */
#define R_X86_64_RELATIVE       8       /* Adjust by program base */
#define R_X86_64_GOTPCREL       9       /* 32 bit signed pc relative
                                           offset to GOT */
#define R_X86_64_32             10      /* Direct 32 bit zero extended */
#define R_X86_64_32S            11      /* Direct 32 bit sign extended */
#define R_X86_64_16             12      /* Direct 16 bit zero extended */
#define R_X86_64_PC16           13      /* 16 bit sign extended pc relative */
#define R_X86_64_8              14      /* Direct 8 bit sign extended  */
#define R_X86_64_PC8            15      /* 8 bit sign extended pc relative */

#define R_X86_64_NUM            16

int apply_relocate_add(Elf64_Shdr *sechdrs,
		   const char *strtab,
		   unsigned int symindex,
		   unsigned int relsec,
		   struct module *me)
{
	unsigned int i;
	Elf64_Rela *rel = (void *)sechdrs[relsec].sh_addr;
	Elf64_Sym *sym;
	void *loc;
	u64 val;

	DEBUGP("Applying relocate section %u to %u\n",
	       relsec, sechdrs[relsec].sh_info);
	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rel); i++) {
		/* This is where to make the change */
		loc = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rel[i].r_offset;

		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rel[i].r_info);

		DEBUGP("type %d st_value %Lx r_addend %Lx loc %Lx\n",
		       (int)ELF64_R_TYPE(rel[i].r_info),
		       sym->st_value, rel[i].r_addend, (u64)loc);

		val = sym->st_value + rel[i].r_addend;

		switch (ELF64_R_TYPE(rel[i].r_info)) {
		case R_X86_64_NONE:
			break;
		case R_X86_64_64:
			if (*(u64 *)loc != 0)
				goto invalid_relocation;
			*(u64 *)loc = val;
			break;
		case R_X86_64_32:
			if (*(u32 *)loc != 0)
				goto invalid_relocation;
			*(u32 *)loc = val;
			if (val != *(u32 *)loc)
				goto overflow;
			break;
		case R_X86_64_32S:
			if (*(s32 *)loc != 0)
				goto invalid_relocation;
			*(s32 *)loc = val;
			if ((s64)val != *(s32 *)loc)
				goto overflow;
			break;
		case R_X86_64_PC32:
		case R_X86_64_PLT32:
			if (*(u32 *)loc != 0)
				goto invalid_relocation;
			val -= (u64)loc;
			*(u32 *)loc = val;
			if ((s64)val != *(s32 *)loc)
				goto overflow;
			break;
		default:
			pr_err("%s: Unknown rela relocation: %llu\n",
			       me->name, ELF64_R_TYPE(rel[i].r_info));
			return -ENOEXEC;
		}
	}
	return 0;

invalid_relocation:
	pr_err("x86/modules: Skipping invalid relocation target, existing value is nonzero for type %d, loc %p, val %Lx\n",
	       (int)ELF64_R_TYPE(rel[i].r_info), loc, val);
	return -ENOEXEC;

overflow:
	pr_err("overflow in relocation type %d val %Lx\n",
	       (int)ELF64_R_TYPE(rel[i].r_info), val);
	pr_err("`%s' likely not compiled with -mcmodel=kernel\n",
	       me->name);
	return -ENOEXEC;
}

int module_finalize(const Elf_Ehdr *hdr,
		    const Elf_Shdr *sechdrs,
		    struct module *me)
{
	const Elf_Shdr *s, *text = NULL, *alt = NULL, *locks = NULL;
//		*para = NULL, *orc = NULL, *orc_ip = NULL;
	char *secstrings = (void *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	for (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) {
		if (!strcmp(".text", secstrings + s->sh_name))
			text = s;
		if (!strcmp(".altinstructions", secstrings + s->sh_name))
			alt = s;
		if (!strcmp(".smp_locks", secstrings + s->sh_name))
			locks = s;
	}

	/* make jump label nops */
	jump_label_apply_nops(me);

	return 0;
}
