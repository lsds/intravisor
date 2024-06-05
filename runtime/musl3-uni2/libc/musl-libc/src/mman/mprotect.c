#include <sys/mman.h>
#include "libc.h"
#include "syscall.h"

int __mprotect(void *addr, size_t len, int prot)
{
	uintptr_t start, end;
	start = (uintptr_t)addr & -PAGE_SIZE;
	end = (uintptr_t)((char *)addr + len + PAGE_SIZE-1) & -PAGE_SIZE;
	return syscall(SYS_mprotect, start, end-start, prot);
}

weak_alias(__mprotect, mprotect);
