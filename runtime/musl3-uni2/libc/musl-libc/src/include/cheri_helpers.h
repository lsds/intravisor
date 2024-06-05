#ifndef MUSL_CHERI_HELPERS_H
#define MUSL_CHERI_HELPERS_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cap_perms.h>

#ifdef __CHERI_PURE_CAPABILITY__

#define RESTRICT_BNDS_IF_CHERI(c, w) __builtin_cheri_bounds_set(c, w)
#define CAP_TAIL_LENGTH(cap) __builtin_cheri_length_get(cap) - __builtin_cheri_offset_get(cap)
#define LT_IF_CHERI_ELSE(a, b, e) (a < b)
#define VA_ARG_IF_IN_BOUNDS(v, l) ( \
	((v) != ((void*)0) && __builtin_cheri_length_get(v) >= (__builtin_cheri_offset_get(v) + sizeof(l))) \
	? va_arg(v, l) : ((l){0})    \
)

/**
 * Change a cap with base B, value V and length L to a cap with base V, value V
 * and length L-(V-B)
 */
inline void *restrict_bounds_to_tail(void *cap) {
  size_t off = __builtin_cheri_offset_get(cap);
  size_t len = __builtin_cheri_length_get(cap);
  return __builtin_cheri_bounds_set(cap, len - off);
}

#define MUSL_CAP_PROT_MAPFILE (READ_CAP_PERMS | __CHERI_CAP_PERMISSION_GLOBAL__)
#define MUSL_CAP_PROT_THREAD (READ_CAP_PERMS | WRITE_CAP_PERMS | __CHERI_CAP_PERMISSION_GLOBAL__)
#define MUSL_CAP_PROT_MALLOC (READ_CAP_PERMS | WRITE_CAP_PERMS | ROOT_CAP_PERMS)
#define MUSL_CAP_PROT_SEM (READ_CAP_PERMS | WRITE_CAP_PERMS | __CHERI_CAP_PERMISSION_GLOBAL__)
#define MUSL_CAP_PROT_NONE (0)

#define __CHERI_CAP_PERMISSION_USER0__	(1u << 2u)
#define __CHERI_CAP_PERMISSION_USER1__	(1u << 3u)
#define __CHERI_CAP_PERMISSION_USER2__	(1u << 4u)
#define __CHERI_CAP_PERMISSION_USER3__	(1u << 5u)
#define __CHERI_CAP_PERMISSION_VMEM__	__CHERI_CAP_PERMISSION_USER0__

#else

#define RESTRICT_BNDS_IF_CHERI(c, w) c
#define CAP_TAIL_LENGTH(cap) SIZE_MAX
#define LT_IF_CHERI_ELSE(a, b, e) e
#define VA_ARG_IF_IN_BOUNDS(v, l) va_arg(v, l)

#endif // __CHERI_PURE_CAPABILITY__

#endif // MUSL_CHERI_HELPERS_H
