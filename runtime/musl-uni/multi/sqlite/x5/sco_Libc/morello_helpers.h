#ifndef MUSL_MORELLO_HELPERS_H
#define MUSL_MORELLO_HELPERS_H

//#include <stdint.h>

#ifdef __CHERI_PURE_CAPABILITY__

#define RESTRICT_BNDS_IF_MORELLO(c, w) __builtin_cheri_bounds_set(c, w)
#define CAP_TAIL_LENGTH(cap) __builtin_cheri_length_get(cap) - __builtin_cheri_offset_get(cap)
#define LT_IF_MORELLO_ELSE(a, b, e) (a < b)

#else

#define RESTRICT_BNDS_IF_MORELLO(c, w) c
#define CAP_TAIL_LENGTH(cap) SIZE_MAX
#define LT_IF_MORELLO_ELSE(a, b, e) e

#endif // __CHERI_PURE_CAPABILITY__

#endif // MUSL_MORELLO_HELPERS_H
