#ifndef _SYS_AUXV_H
#define _SYS_AUXV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <elf.h>
#include <bits/hwcap.h>

unsigned long getauxval(unsigned long);
#ifdef __CHERI__
void *getauxptr(unsigned long);
#endif

#ifdef __cplusplus
}
#endif

#endif
