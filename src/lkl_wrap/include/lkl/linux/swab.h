/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef _LKL_LINUX_SWAB_H
#define _LKL_LINUX_SWAB_H

#include <lkl/linux/types.h>

#include <lkl/asm/swab.h>

/*
 * casts are necessary for constants, because we never know how for sure
 * how U/UL/ULL map to __lkl__u16, __lkl__u32, __lkl__u64. At least not in a portable way.
 */
#define __lkl___constant_swab16(x) ((__lkl__u16)(				\
	(((__lkl__u16)(x) & (__lkl__u16)0x00ffU) << 8) |			\
	(((__lkl__u16)(x) & (__lkl__u16)0xff00U) >> 8)))

#define __lkl___constant_swab32(x) ((__lkl__u32)(				\
	(((__lkl__u32)(x) & (__lkl__u32)0x000000ffUL) << 24) |		\
	(((__lkl__u32)(x) & (__lkl__u32)0x0000ff00UL) <<  8) |		\
	(((__lkl__u32)(x) & (__lkl__u32)0x00ff0000UL) >>  8) |		\
	(((__lkl__u32)(x) & (__lkl__u32)0xff000000UL) >> 24)))

#define __lkl___constant_swab64(x) ((__lkl__u64)(				\
	(((__lkl__u64)(x) & (__lkl__u64)0x00000000000000ffULL) << 56) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0x000000000000ff00ULL) << 40) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0x0000000000ff0000ULL) << 24) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0x00000000ff000000ULL) <<  8) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0x000000ff00000000ULL) >>  8) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0x0000ff0000000000ULL) >> 24) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0x00ff000000000000ULL) >> 40) |	\
	(((__lkl__u64)(x) & (__lkl__u64)0xff00000000000000ULL) >> 56)))

#define __lkl___constant_swahw32(x) ((__lkl__u32)(			\
	(((__lkl__u32)(x) & (__lkl__u32)0x0000ffffUL) << 16) |		\
	(((__lkl__u32)(x) & (__lkl__u32)0xffff0000UL) >> 16)))

#define __lkl___constant_swahb32(x) ((__lkl__u32)(			\
	(((__lkl__u32)(x) & (__lkl__u32)0x00ff00ffUL) << 8) |		\
	(((__lkl__u32)(x) & (__lkl__u32)0xff00ff00UL) >> 8)))

/*
 * Implement the following as inlines, but define the interface using
 * macros to allow constant folding when possible:
 * ___swab16, ___swab32, ___swab64, ___swahw32, ___swahb32
 */

static __inline__  __lkl__u16 __lkl__fswab16(__lkl__u16 val)
{
#if defined (__arch_swab16)
	return __arch_swab16(val);
#else
	return __lkl___constant_swab16(val);
#endif
}

static __inline__  __lkl__u32 __lkl__fswab32(__lkl__u32 val)
{
#if defined(__lkl__arch_swab32)
	return __lkl__arch_swab32(val);
#else
	return __lkl___constant_swab32(val);
#endif
}

static __inline__  __lkl__u64 __lkl__fswab64(__lkl__u64 val)
{
#if defined (__arch_swab64)
	return __arch_swab64(val);
#elif defined(__LKL__SWAB_64_THRU_32__)
	__lkl__u32 h = val >> 32;
	__lkl__u32 l = val & ((1ULL << 32) - 1);
	return (((__lkl__u64)__lkl__fswab32(l)) << 32) | ((__lkl__u64)(__lkl__fswab32(h)));
#else
	return __lkl___constant_swab64(val);
#endif
}

static __inline__  __lkl__u32 __lkl__fswahw32(__lkl__u32 val)
{
#ifdef __arch_swahw32
	return __arch_swahw32(val);
#else
	return __lkl___constant_swahw32(val);
#endif
}

static __inline__  __lkl__u32 __lkl__fswahb32(__lkl__u32 val)
{
#ifdef __arch_swahb32
	return __arch_swahb32(val);
#else
	return __lkl___constant_swahb32(val);
#endif
}

/**
 * __lkl__swab16 - return a byteswapped 16-bit value
 * @x: value to byteswap
 */
#ifdef __HAVE_BUILTIN_BSWAP16__
#define __lkl__swab16(x) (__lkl__u16)__builtin_bswap16((__lkl__u16)(x))
#else
#define __lkl__swab16(x)				\
	(__builtin_constant_p((__lkl__u16)(x)) ?	\
	__lkl___constant_swab16(x) :			\
	__lkl__fswab16(x))
#endif

/**
 * __lkl__swab32 - return a byteswapped 32-bit value
 * @x: value to byteswap
 */
#ifdef __HAVE_BUILTIN_BSWAP32__
#define __lkl__swab32(x) (__lkl__u32)__builtin_bswap32((__lkl__u32)(x))
#else
#define __lkl__swab32(x)				\
	(__builtin_constant_p((__lkl__u32)(x)) ?	\
	__lkl___constant_swab32(x) :			\
	__lkl__fswab32(x))
#endif

/**
 * __lkl__swab64 - return a byteswapped 64-bit value
 * @x: value to byteswap
 */
#ifdef __HAVE_BUILTIN_BSWAP64__
#define __lkl__swab64(x) (__lkl__u64)__builtin_bswap64((__lkl__u64)(x))
#else
#define __lkl__swab64(x)				\
	(__builtin_constant_p((__lkl__u64)(x)) ?	\
	__lkl___constant_swab64(x) :			\
	__lkl__fswab64(x))
#endif

/**
 * __lkl__swahw32 - return a word-swapped 32-bit value
 * @x: value to wordswap
 *
 * __lkl__swahw32(0x12340000) is 0x00001234
 */
#define __lkl__swahw32(x)				\
	(__builtin_constant_p((__lkl__u32)(x)) ?	\
	__lkl___constant_swahw32(x) :		\
	__lkl__fswahw32(x))

/**
 * __lkl__swahb32 - return a high and low byte-swapped 32-bit value
 * @x: value to byteswap
 *
 * __lkl__swahb32(0x12345678) is 0x34127856
 */
#define __lkl__swahb32(x)				\
	(__builtin_constant_p((__lkl__u32)(x)) ?	\
	__lkl___constant_swahb32(x) :		\
	__lkl__fswahb32(x))

/**
 * __lkl__swab16p - return a byteswapped 16-bit value from a pointer
 * @p: pointer to a naturally-aligned 16-bit value
 */
static __lkl__always_inline __lkl__u16 __lkl__swab16p(const __lkl__u16 *p)
{
#ifdef __arch_swab16p
	return __arch_swab16p(p);
#else
	return __lkl__swab16(*p);
#endif
}

/**
 * __lkl__swab32p - return a byteswapped 32-bit value from a pointer
 * @p: pointer to a naturally-aligned 32-bit value
 */
static __lkl__always_inline __lkl__u32 __lkl__swab32p(const __lkl__u32 *p)
{
#ifdef __arch_swab32p
	return __arch_swab32p(p);
#else
	return __lkl__swab32(*p);
#endif
}

/**
 * __lkl__swab64p - return a byteswapped 64-bit value from a pointer
 * @p: pointer to a naturally-aligned 64-bit value
 */
static __lkl__always_inline __lkl__u64 __lkl__swab64p(const __lkl__u64 *p)
{
#ifdef __arch_swab64p
	return __arch_swab64p(p);
#else
	return __lkl__swab64(*p);
#endif
}

/**
 * __lkl__swahw32p - return a wordswapped 32-bit value from a pointer
 * @p: pointer to a naturally-aligned 32-bit value
 *
 * See __lkl__swahw32() for details of wordswapping.
 */
static __inline__ __lkl__u32 __lkl__swahw32p(const __lkl__u32 *p)
{
#ifdef __arch_swahw32p
	return __arch_swahw32p(p);
#else
	return __lkl__swahw32(*p);
#endif
}

/**
 * __lkl__swahb32p - return a high and low byteswapped 32-bit value from a pointer
 * @p: pointer to a naturally-aligned 32-bit value
 *
 * See __lkl__swahb32() for details of high/low byteswapping.
 */
static __inline__ __lkl__u32 __lkl__swahb32p(const __lkl__u32 *p)
{
#ifdef __arch_swahb32p
	return __arch_swahb32p(p);
#else
	return __lkl__swahb32(*p);
#endif
}

/**
 * __lkl__swab16s - byteswap a 16-bit value in-place
 * @p: pointer to a naturally-aligned 16-bit value
 */
static __inline__ void __lkl__swab16s(__lkl__u16 *p)
{
#ifdef __arch_swab16s
	__arch_swab16s(p);
#else
	*p = __lkl__swab16p(p);
#endif
}
/**
 * __lkl__swab32s - byteswap a 32-bit value in-place
 * @p: pointer to a naturally-aligned 32-bit value
 */
static __lkl__always_inline void __lkl__swab32s(__lkl__u32 *p)
{
#ifdef __arch_swab32s
	__arch_swab32s(p);
#else
	*p = __lkl__swab32p(p);
#endif
}

/**
 * __lkl__swab64s - byteswap a 64-bit value in-place
 * @p: pointer to a naturally-aligned 64-bit value
 */
static __lkl__always_inline void __lkl__swab64s(__lkl__u64 *p)
{
#ifdef __arch_swab64s
	__arch_swab64s(p);
#else
	*p = __lkl__swab64p(p);
#endif
}

/**
 * __lkl__swahw32s - wordswap a 32-bit value in-place
 * @p: pointer to a naturally-aligned 32-bit value
 *
 * See __lkl__swahw32() for details of wordswapping
 */
static __inline__ void __lkl__swahw32s(__lkl__u32 *p)
{
#ifdef __arch_swahw32s
	__arch_swahw32s(p);
#else
	*p = __lkl__swahw32p(p);
#endif
}

/**
 * __lkl__swahb32s - high and low byteswap a 32-bit value in-place
 * @p: pointer to a naturally-aligned 32-bit value
 *
 * See __lkl__swahb32() for details of high and low byte swapping
 */
static __inline__ void __lkl__swahb32s(__lkl__u32 *p)
{
#ifdef __arch_swahb32s
	__arch_swahb32s(p);
#else
	*p = __lkl__swahb32p(p);
#endif
}


#endif /* _LKL_LINUX_SWAB_H */
