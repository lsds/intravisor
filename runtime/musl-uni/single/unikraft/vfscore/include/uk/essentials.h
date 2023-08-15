
#if arm_sim
#define DEQUALIFY(t, a) ((t)(const volatile void *)(a))
#else
#define DEQUALIFY(t, a) ((t)(__uintcap_t)(const volatile void *)(a))
#endif
/* The following code was taken from FreeBSD: sys/sys/cdefs.h */
/*
 * Macro to test if we're using a specific version of gcc or later.
 */
#ifndef __GNUC_PREREQ__
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__GNUC_PREREQ__(ma, mi)	\
	(__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define __GNUC_PREREQ__(ma, mi) 0
#endif
#endif /* !__GNUC_PREREQ__ */



#ifndef __offsetof
#if __GNUC_PREREQ__(4, 1)
#define __offsetof(t, field)       __builtin_offsetof(t, field)
#else
#define __offsetof(t, field) \
	((__sz)(__uptr)((const volatile void *)&((t *)0)->field))
#endif
#endif /* !__offsetof */


/*
 * Given the pointer x to the member m of the struct s, return
 * a pointer to the containing structure.  When using GCC, we first
 * assign pointer x to a local variable, to check that its type is
 * compatible with member m.
 */
#ifndef __containerof
#if __GNUC_PREREQ__(3, 1)
#define __containerof(x, s, m) ({ \
	const volatile __typeof(((s *)0)->m) *__x = (x); \
	DEQUALIFY(s *, (const volatile char *)__x - __offsetof(s, m)); \
})
#else
#define __containerof(x, s, m) \
	DEQUALIFY(s *, (const volatile char *)(x) - __offsetof(s, m))
#endif
#endif /* !__containerof */



/**
 * Perform a atomic fetch and add operation.
 */
#define ukarch_fetch_add(src, value) \
	__atomic_fetch_add(src, value, __ATOMIC_SEQ_CST)

/**
 * Perform a atomic increment/decrement operation and return the
 * previous value.
 */
#define ukarch_inc(src) \
	ukarch_fetch_add(src, 1)
#define ukarch_dec(src) \
	__atomic_fetch_sub(src, 1, __ATOMIC_SEQ_CST)

#ifndef MIN
#define MIN(a, b)                                                              \
	({                                                                     \
		__typeof__(a) __a = (a);                                       \
		__typeof__(b) __b = (b);                                       \
		__a < __b ? __a : __b;                                         \
	})
#endif
#ifndef MIN3
#define MIN3(a, b, c) MIN(MIN((a), (b)), (c))
#endif
#ifndef MIN4
#define MIN4(a, b, c, d) MIN(MIN((a), (b)), MIN((c), (d)))
#endif

#ifndef MAX
#define MAX(a, b)                                                              \
	({                                                                     \
		__typeof__(a) __a = (a);                                       \
		__typeof__(b) __b = (b);                                       \
		__a > __b ? __a : __b;                                         \
	})
#endif
#ifndef MAX3
#define MAX3(a, b, c) MAX(MAX((a), (b)), (c))
#endif
#ifndef MAX4
#define MAX4(a, b, c, d) MAX(MAX((a), (b)), MAX((c), (d)))
#endif

#ifndef POWER_OF_2
#define POWER_OF_2(v) ((0 != v) && (0 == (v & (v - 1))))
#endif

#ifndef DIV_ROUND_UP
#define DIV_ROUND_UP(v, d) (((v) + (d)-1) / (d))
#endif

/* Note: a has to be a power of 2 */
#ifndef ALIGN_UP
#define ALIGN_UP(v, a) (((v) + (a)-1) & ~((a)-1))
#endif

/* Note: a has to be a power of 2 */
#ifndef ALIGN_DOWN
#define ALIGN_DOWN(v, a) ((v) & ~((a)-1))
#endif



#define __PAGE_SHIFT		12

#ifdef __ASSEMBLY__
#define __PAGE_SIZE		(1 << __PAGE_SHIFT)
#define __PAGE_MASK		(~((__PAGE_SIZE) - 1))
#else
#define __PAGE_SIZE		(1ULL << __PAGE_SHIFT)
#define __PAGE_MASK		(~((__PAGE_SIZE) - 1))
#endif


#define __unused               __attribute__((unused))

#ifndef __maybe_unused
#define __maybe_unused         __attribute__((unused))
#endif


