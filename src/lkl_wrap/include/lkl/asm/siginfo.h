#ifndef _LKL_ASM_LKL_SIGINFO_H
#define _LKL_ASM_LKL_SIGINFO_H

#ifdef LKL_CONFIG_64BIT
#define __LKL__ARCH_SI_PREAMBLE_SIZE	(4 * sizeof(int))
#endif

#include <lkl/asm-generic/siginfo.h>

#endif /* _LKL_ASM_LKL_SIGINFO_H */
