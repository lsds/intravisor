#ifndef SYS_AUXV_H
#define SYS_AUXV_H

#include "../../../include/sys/auxv.h"

#if (__SIZEOF_LONG__ == 8)
typedef Elf64_auxv_t auxv_entry;
#else
typedef Elf32_auxv_t auxv_entry;
#endif

#include <features.h>

hidden unsigned long __getauxval(unsigned long);
#ifdef __CHERI__
hidden void *__getauxptr(unsigned long);
#endif

#endif
