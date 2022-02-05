#include <stddef.h>
#include "dynlink.h"
#include "libc.h"

//#define SIM	1

#ifndef START
#define START "_dlstart"
#endif

#define SHARED

#include "crt_arch.h"

#ifndef GETFUNCSYM
#define GETFUNCSYM(fp, sym, got) do { \
	hidden void sym(); \
	static void (*static_func_ptr)() = sym; \
	__asm__ __volatile__ ( "" : "+m"(static_func_ptr) : : "memory"); \
	*(fp) = static_func_ptr; } while(0)
#endif

#define __asm_syscall(...) \
	__asm__ __volatile__ ("ecall\n\t" \
	: "=r"(a0) : __VA_ARGS__ : "memory"); \
	return a0; \


//		__syscall3(64, 1, a, 10);
static inline long __syscall3(long n, long a, long b, long c)
{
	register long t0 __asm__("a7") = n;
	register long a0 __asm__("a0") = a;
	register long a1 __asm__("a1") = b;
	register long a2 __asm__("a2") = c;
	__asm_syscall("r"(t0), "0"(a0), "r"(a1), "r"(a2))
}

static unsigned int
mini_strlen(const char *s)
{
	unsigned int len = 0;
	while (s[len] != '\0') len++;
	return len;
}

static unsigned int
mini_itoa(int value, unsigned int radix, unsigned int uppercase, unsigned int unsig,
	 char *buffer, unsigned int zero_pad)
{
	char	*pbuffer = buffer;
	int	negative = 0;
	unsigned int	i, len;

	/* No support for unusual radixes. */
	if (radix > 16)
		return 0;

	if (value < 0 && !unsig) {
		negative = 1;
		value = -value;
	}

	/* This builds the string back to front ... */
	do {
		int digit = value % radix;
		*(pbuffer++) = (digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
		value /= radix;
	} while (value > 0);

	for (i = (pbuffer - buffer); i < zero_pad; i++)
		*(pbuffer++) = '0';

	if (negative)
		*(pbuffer++) = '-';

	*(pbuffer) = '\0';

	/* ... now we reverse it (could do it recursively but will
	 * conserve the stack space) */
	len = (pbuffer - buffer);
	for (i = 0; i < len / 2; i++) {
		char j = buffer[i];
		buffer[i] = buffer[len-i-1];
		buffer[len-i-1] = j;
	}

	return len;
}

struct mini_buff {
	char *buffer, *pbuffer;
	unsigned int buffer_len;
};

static int
_putc(int ch, struct mini_buff *b)
{
	if ((unsigned int)((b->pbuffer - b->buffer) + 1) >= b->buffer_len)
		return 0;
	*(b->pbuffer++) = ch;
	*(b->pbuffer) = '\0';
	return 1;
}

static int
_puts(char *s, unsigned int len, struct mini_buff *b)
{
	unsigned int i;

	if (b->buffer_len - (b->pbuffer - b->buffer) - 1 < len)
		len = b->buffer_len - (b->pbuffer - b->buffer) - 1;

	/* Copy to buffer */
	for (i = 0; i < len; i++)
		*(b->pbuffer++) = s[i];
	*(b->pbuffer) = '\0';

	return len;
}

int
mini_vsnprintf(char *buffer, unsigned int buffer_len, const char *fmt, va_list va)
{
	struct mini_buff b;
	char bf[24];
	char ch;

	b.buffer = buffer;
	b.pbuffer = buffer;
	b.buffer_len = buffer_len;

	while ((ch=*(fmt++))) {
		if ((unsigned int)((b.pbuffer - b.buffer) + 1) >= b.buffer_len)
			break;
		if (ch!='%')
			_putc(ch, &b);
		else {
			char zero_pad = 0;
			char *ptr;
			unsigned int len;

			ch=*(fmt++);

			/* Zero padding requested */
			if (ch=='0') {
				ch=*(fmt++);
				if (ch == '\0')
					goto end;
				if (ch >= '0' && ch <= '9')
					zero_pad = ch - '0';
				ch=*(fmt++);
			}

			switch (ch) {
				case 0:
					goto end;

				case 'u':
				case 'd':
					len = mini_itoa(va_arg(va, unsigned int), 10, 0, (ch=='u'), bf, zero_pad);
					_puts(bf, len, &b);
					break;

				case 'x':
				case 'X':
					len = mini_itoa(va_arg(va, unsigned int), 16, (ch=='X'), 1, bf, zero_pad);
					_puts(bf, len, &b);
					break;

				case 'c' :
					_putc((char)(va_arg(va, int)), &b);
					break;

				case 's' :
					ptr = va_arg(va, char*);
					_puts(ptr, mini_strlen(ptr), &b);
					break;

				default:
					_putc(ch, &b);
					break;
			}
		}
	}
end:
	return b.pbuffer - b.buffer;
}


int
mini_snprintf(char* buffer, unsigned int buffer_len, const char *fmt, ...)
{
	int ret;
	va_list va;
	va_start(va, fmt);
	ret = mini_vsnprintf(buffer, buffer_len, fmt, va);
	va_end(va);

	return ret;
}

hidden void _dlstart_c(size_t *sp, size_t *dynv)
{
	size_t i, aux[AUX_CNT], dyn[DYN_CNT];
	size_t *rel, rel_size, base;

	int argc = *sp;
	char **argv = (void *)(sp+1);

	for (i=argc+1; argv[i]; i++);
	size_t *auxv = (void *)(argv+i+1);

	for (i=0; i<AUX_CNT; i++) aux[i] = 0;
	for (i=0; auxv[i]; i+=2) if (auxv[i]<AUX_CNT)
		aux[auxv[i]] = auxv[i+1];

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
		base = aux[AT_BASE];
		if (!base) base = aux[AT_PHDR] & -4096;
		segs = &fakeseg;
		segs[0].addr = base;
		segs[0].p_vaddr = 0;
		segs[0].p_memsz = -1;
		Ehdr *eh = (void *)base;
		Phdr *ph = (void *)(base + eh->e_phoff);
		size_t phnum = eh->e_phnum;
		size_t phent = eh->e_phentsize;
		while (phnum-- && ph->p_type != PT_DYNAMIC)
			ph = (void *)((size_t)ph + phent);
		dynv = (void *)(base + ph->p_vaddr);
	}
#endif

	for (i=0; i<DYN_CNT; i++) dyn[i] = 0;
	for (i=0; dynv[i]; i+=2) if (dynv[i]<DYN_CNT)
		dyn[dynv[i]] = dynv[i+1];

#if DL_FDPIC
	for (i=0; i<DYN_CNT; i++) {
		if (i==DT_RELASZ || i==DT_RELSZ) continue;
		if (!dyn[i]) continue;
		for (j=0; dyn[i]-segs[j].p_vaddr >= segs[j].p_memsz; j++);
		dyn[i] += segs[j].addr - segs[j].p_vaddr;
	}
	base = 0;

	const Sym *syms = (void *)dyn[DT_SYMTAB];

	rel = (void *)dyn[DT_RELA];
	rel_size = dyn[DT_RELASZ];
	for (; rel_size; rel+=3, rel_size-=3*sizeof(size_t)) {
		if (!IS_RELATIVE(rel[1], syms)) continue;
		for (j=0; rel[0]-segs[j].p_vaddr >= segs[j].p_memsz; j++);
		size_t *rel_addr = (void *)
			(rel[0] + segs[j].addr - segs[j].p_vaddr);
		if (R_TYPE(rel[1]) == REL_FUNCDESC_VAL) {
			*rel_addr += segs[rel_addr[1]].addr
				- segs[rel_addr[1]].p_vaddr
				+ syms[R_SYM(rel[1])].st_value;
			rel_addr[1] = dyn[DT_PLTGOT];
		} else {
			size_t val = syms[R_SYM(rel[1])].st_value;
			for (j=0; val-segs[j].p_vaddr >= segs[j].p_memsz; j++);
			*rel_addr = rel[2] + segs[j].addr - segs[j].p_vaddr + val;
		}
	}
#else
	/* If the dynamic linker is invoked as a command, its load
	 * address is not available in the aux vector. Instead, compute
	 * the load address as the difference between &_DYNAMIC and the
	 * virtual address in the PT_DYNAMIC program header. */
	base = aux[AT_BASE];
	if (!base) {
		size_t phnum = aux[AT_PHNUM];
		size_t phentsize = aux[AT_PHENT];
		Phdr *ph = (void *)aux[AT_PHDR];
		for (i=phnum; i--; ph = (void *)((char *)ph + phentsize)) {
			if (ph->p_type == PT_DYNAMIC) {
				base = (size_t)dynv - ph->p_vaddr;
				break;
			}
		}
	}
#ifndef SIM
//	base = base - 0x20000000;//todo
	base = 0;
#endif

	/* MIPS uses an ugly packed form for GOT relocations. Since we
	 * can't make function calls yet and the code is tiny anyway,
	 * it's simply inlined here. */
	if (NEED_MIPS_GOT_RELOCS) {
		size_t local_cnt = 0;
		size_t *got = (void *)(base + dyn[DT_PLTGOT]);
		for (i=0; dynv[i]; i+=2) if (dynv[i]==DT_MIPS_LOCAL_GOTNO)
			local_cnt = dynv[i+1];
		for (i=0; i<local_cnt; i++) got[i] += base;
	}

	rel = (void *)(base+dyn[DT_REL]);

	rel_size = dyn[DT_RELSZ];
	for (; rel_size; rel+=2, rel_size-=2*sizeof(size_t)) {
		if (!IS_RELATIVE(rel[1], 0)) continue;
		size_t *rel_addr = (void *)(base + rel[0]);
		*rel_addr += base;
	}



	rel = (void *)(base+dyn[DT_RELA]);
	rel_size = dyn[DT_RELASZ];

	for (; rel_size; rel+=3, rel_size-=3*sizeof(size_t)) {
		if (!IS_RELATIVE(rel[1], 0)) continue;
		size_t *rel_addr = (void *)(base + rel[0]);

		*rel_addr = base + rel[2];
	}
#endif
	stage2_func dls2;
	GETFUNCSYM(&dls2, __dls2, base+dyn[DT_PLTGOT]);
//	__asm__ __volatile__("mv a0, %0; ebreak;" :: "r"(dls2) : "memory");
	dls2((void *)base, sp);
}
