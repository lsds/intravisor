#if defined(MUSL_USE_COMPILER_BUILTINS)

#ifndef _ATOMIC_BUILTINS_H
#define _ATOMIC_BUILTINS_H

#if !defined(_ATOMIC_H)
#error "Include 'atomic.h' instead"
#endif

// The functions below were checked that they produce the same or stronger
// machine code for the indicated compilers only:
//
//   AArch64: clang 9.0.0 (19 Sep 2019)
//            gcc   7.3   (25 Jan 2018)
//
//   x86_64:  clang 8.0.0 (20 Mar 2019)
//            gcc   7.1   (2 May 2017)
//
// Used flags: '-O2'
//
// musl-libc supports very old posix memory model, therefore we require SEQ_CST
// conservatively, even if the builtins produce more restrictive code.
//
// Not all of these functions are atomics, but that's how the original
// implementation calls them.

#define a_cas a_cas
static inline int a_cas(volatile int *p, int t, int s) {
  __atomic_compare_exchange_n(p, &t, s, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
  return t;
}

#define a_cas_p a_cas_p
static inline void *a_cas_p(volatile void *p, void *t, void *s) {
  __atomic_compare_exchange_n((void *volatile *)p, &t, s,
                              0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
  return t;
}

#define a_swap a_swap
static inline int a_swap(volatile int *p, int v) {
  return __atomic_exchange_n(p, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_add a_fetch_add
static inline int a_fetch_add(volatile int *p, int v) {
  return __atomic_fetch_add(p, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_or a_fetch_or
static inline int a_fetch_or(volatile int *p, int v) {
  return __atomic_fetch_or(p, v, __ATOMIC_SEQ_CST);
}

#define a_fetch_and a_fetch_and
static inline int a_fetch_and(volatile int *p, int v) {
  return __atomic_fetch_and(p, v, __ATOMIC_SEQ_CST);
}

#define a_and a_and
static inline void a_and(volatile int *p, int v) {
  __atomic_fetch_and(p, v, __ATOMIC_SEQ_CST);
}

#define a_or a_or
static inline void a_or(volatile int *p, int v) {
  __atomic_fetch_or(p, v, __ATOMIC_SEQ_CST);
}

#define a_and_64 a_and_64
static inline void a_and_64(volatile uint64_t *p, uint64_t v) {
  __atomic_fetch_and(p, v, __ATOMIC_SEQ_CST);
}

#define a_or_64 a_or_64
static inline void a_or_64(volatile uint64_t *p, uint64_t v) {
  __atomic_fetch_or(p, v, __ATOMIC_SEQ_CST);
}

#define a_or_l a_or_l
static inline void a_or_l(volatile void *p, long v) {
  __atomic_fetch_or((volatile long *)p, v, __ATOMIC_SEQ_CST);
}

#define a_inc a_inc
static inline void a_inc(volatile int *p) {
  __atomic_fetch_add(p, 1, __ATOMIC_SEQ_CST);
}

#define a_dec a_dec
static inline void a_dec(volatile int *p) {
  __atomic_fetch_add(p, -1, __ATOMIC_SEQ_CST);
}

#define a_store a_store
static inline void a_store(volatile int *p, int x) {
  __atomic_store_n(p, x, __ATOMIC_SEQ_CST);
}

#define a_ctz_32 a_ctz_32
static inline int a_ctz_32(uint32_t x) {
  return __builtin_ctz(x);
}

#define a_ctz_64 a_ctz_64
static inline int a_ctz_64(uint64_t x) {
  return __builtin_ctzl(x);
}

#define a_ctz_l a_ctz_l
static inline int a_ctz_l(unsigned long x) {
  return __builtin_ctzl(x);
}

#define a_clz_32 a_clz_32
static inline int a_clz_32(uint32_t x) {
  return __builtin_clz(x);
}

#define a_clz_64 a_clz_64
static inline int a_clz_64(uint64_t x) {
  return __builtin_clzl(x);
}

#define a_barrier a_barrier
static inline void a_barrier() {
  __atomic_thread_fence(__ATOMIC_SEQ_CST);
}

#endif // _ATOMIC_BUILTINS_H

#endif // MUSL_USE_COMPILER_BUILTINS
