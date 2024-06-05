#ifndef SYS_DYNV_H
#define SYS_DYNV_H

#include <elf.h>

#if (__SIZEOF_LONG__ == 8)
typedef Elf64_Dyn dynv_entry;
#else
typedef Elf32_Dyn dynv_entry;
#endif

#endif
