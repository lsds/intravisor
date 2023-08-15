#ifndef _LKL_ASM_UAPI_LKL_BYTEORDER_H
#define _LKL_ASM_UAPI_LKL_BYTEORDER_H

#include <lkl/asm/config.h>

#if defined(LKL_CONFIG_BIG_ENDIAN)
#include <lkl/linux/byteorder/big_endian.h>
#else
#include <lkl/linux/byteorder/little_endian.h>
#endif

#endif /* _LKL_ASM_UAPI_LKL_BYTEORDER_H */
