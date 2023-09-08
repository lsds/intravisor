#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "morello_helpers.h"
#include "hostcalls.h"

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

       void *my_malloc(size_t size);
       void my_free(void *ptr);
       void *my_realloc(void *ptr, size_t size);


#define true 1

#if 1
char *__strchrnul(const char *s, int c)
{
  c = (unsigned char)c;
  if (!c) return (char *)s + strlen(s);

  size_t i = 0;
  size_t max_i = CAP_TAIL_LENGTH(s);

#ifdef __GNUC__
  typedef size_t __attribute__((__may_alias__)) word;
  const word *w;
  for (; (uintptr_t)s % ALIGN; s++, i++)
    if (!*s || *(unsigned char *)s == c)
      return ((char *)s);
  size_t k = ONES * c;
  if (LT_IF_MORELLO_ELSE(i + sizeof(word) - 1, max_i, true)) {
	for (w = (void *)s;
	     LT_IF_MORELLO_ELSE(i + sizeof(word) - 1, max_i, true) &&
	       !HASZERO(*w) && !HASZERO(*w ^ k);
	     w++, i+=sizeof(word))
	   ;
	s = (void *)w;
  }
#endif
  for (; *s && *(unsigned char *)s != c; s++);
  return ((char *)s);
}
#else
char *__strchrnul(const char *s, int c);
#endif

#define BITOP(a,b,op) \
 ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))

size_t strcspn(const char *s, const char *c)
{
  const char *a = s;
  size_t byteset[32/sizeof(size_t)];

  if (!c[0] || !c[1]) return __strchrnul(s, *c)-a;

  memset(byteset, 0, sizeof byteset);
  for (; *c && BITOP(byteset, *(unsigned char *)c, |=); c++);
  for (; *s && !BITOP(byteset, *(unsigned char *)s, &); s++);
  return s-a;
}

int strncmp(const char *_l, const char *_r, size_t n)
{
  const unsigned char *l=(void *)_l, *r=(void *)_r;
  if (!n--) return 0;
  for (; *l && *r && n && *l == *r ; l++, r++, n--);
  return *l - *r;
}


#ifdef __GNUC__
typedef __attribute__((__may_alias__)) void* WT;
#define WS (sizeof(WT))
#endif

#define SS (sizeof(size_t))

void *memchr(const void *src, int c, size_t n)
{
  const unsigned char *s = src;
  c = (unsigned char)c;

  size_t i = 0;
  size_t max_i = CAP_TAIL_LENGTH(src);

#ifdef __GNUC__
  for (; ((uintptr_t)s & ALIGN) && n && *s != c; s++, n--, i++);
  if (n && *s != c) {
	typedef size_t __attribute__((__may_alias__)) word;
	const word *w;
	size_t k = ONES * c;
	for (w = (const void *)s;
	     n >= SS &&
	     LT_IF_MORELLO_ELSE(i + sizeof(word) - 1, max_i, true)
	     && !HASZERO(*w ^ k);
	     w++, n -= SS, i += sizeof(word))
	  ;
	s = (const void *)w;
  }
#endif
  for (; n && *s != c; s++, n--);
  return n ? ((void *)s) : 0;
}

void *memrchr(const void *m, int c, size_t n)
{
  const unsigned char *s = m;
  c = (unsigned char)c;
  while (n--) if (s[n]==c) return ((void *)(s+n));
  return 0;
}

int strcmp(const char *l, const char *r)
{
  for (; *l==*r && *l; l++, r++);
  return *(unsigned char *)l - *(unsigned char *)r;
}


char *strrchr(const char *s, int c)
{
  return memrchr(s, c, strlen(s) + 1);
}


int memcmp(const void *vl, const void *vr, size_t n)
{
  const unsigned char *l=vl, *r=vr;
  for (; n && *l == *r; n--, l++, r++);
  return n ? *l-*r : 0;
}

int bcmp(const void *s1, const void *s2, size_t n)
{
	return memcmp(s1, s2, n);
}


void *memset(void *dest, int c, size_t n)
{
  unsigned char *s = dest;
  size_t k;

  /* Fill head and tail with minimal branching. Each
   * conditional ensures that all the subsequently used
   * offsets are well-defined and in the dest region. */

  if (!n) return dest;
  s[0] = c;
  s[n-1] = c;
  if (n <= 2) return dest;
  s[1] = c;
  s[2] = c;
  s[n-2] = c;
  s[n-3] = c;
  if (n <= 6) return dest;
  s[3] = c;
  s[n-4] = c;
  if (n <= 8) return dest;

  /* Advance pointer to align it at a 4-byte boundary,
   * and truncate n to a multiple of 4. The previous code
   * already took care of any head/tail that get cut off
   * by the alignment. */

  k = -(uintptr_t)s & 3;
  s += k;
  n -= k;
  n &= -4;

#ifdef __GNUC__
  typedef uint32_t __attribute__((__may_alias__)) u32;
  typedef uint64_t __attribute__((__may_alias__)) u64;

  u32 c32 = ((u32)-1)/255 * (unsigned char)c;

  /* In preparation to copy 32 bytes at a time, aligned on
   * an 8-byte bounary, fill head/tail up to 28 bytes each.
   * As in the initial byte-based head/tail fill, each
   * conditional below ensures that the subsequent offsets
   * are valid (e.g. !(n<=24) implies n>=28). */

  *(u32 *)(s+0) = c32;
  *(u32 *)(s+n-4) = c32;
  if (n <= 8) return dest;
  *(u32 *)(s+4) = c32;
  *(u32 *)(s+8) = c32;
  *(u32 *)(s+n-12) = c32;
  *(u32 *)(s+n-8) = c32;
  if (n <= 24) return dest;
  *(u32 *)(s+12) = c32;
  *(u32 *)(s+16) = c32;
  *(u32 *)(s+20) = c32;
  *(u32 *)(s+24) = c32;
  *(u32 *)(s+n-28) = c32;
  *(u32 *)(s+n-24) = c32;
  *(u32 *)(s+n-20) = c32;
  *(u32 *)(s+n-16) = c32;

  /* Align to a multiple of 8 so we can fill 64 bits at a time,
   * and avoid writing the same bytes twice as much as is
   * practical without introducing additional branching. */

  k = 24 + ((uintptr_t)s & 4);
  s += k;
  n -= k;

  /* If this loop is reached, 28 tail bytes have already been
   * filled, so any remainder when n drops below 32 can be
   * safely ignored. */

  u64 c64 = c32 | ((u64)c32 << 32);
  for (; n >= 32; n-=32, s+=32) {
	*(u64 *)(s+0) = c64;
	*(u64 *)(s+8) = c64;
	*(u64 *)(s+16) = c64;
	*(u64 *)(s+24) = c64;
  }
#else
  /* Pure C fallback with no aliasing violations. */
  for (; n; n--, s++) *s = c;
#endif

  return dest;
}


typedef	__intcap_t word;	/* "word" used for optimal copy speed */
#define	wsize	sizeof(word)
#define	wmask	(wsize - 1)
#define __CAP	__capability

void * memcpy(void * __CAP dst0, const void *  __CAP src0, size_t length) {
	char * __CAP dst = dst0;
	const char * __CAP src = src0;
	size_t t;

	if (length == 0 || dst == src)		/* nothing to do */
		goto done;

	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)

	if (dst < src) {
		/*
		 * Copy forward.
		 */
		t = (__cheri_addr size_t)src;	/* only need low bits */
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src;
		    src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (__cheri_addr size_t)src;
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize;
		    *(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
done:
	return (dst0);
}

void * memmove(void * __CAP dst0, const void *  __CAP src0, size_t length) {
	char * __CAP dst = dst0;
	const char * __CAP src = src0;
	size_t t;

	if (length == 0 || dst == src)		/* nothing to do */
		goto done;

	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)

	if (dst < src) {
		/*
		 * Copy forward.
		 */
		t = (__cheri_addr size_t)src;	/* only need low bits */
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src;
		    src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (__cheri_addr size_t)src;
		if ((t | (__cheri_addr size_t)dst) & wmask) {
			if ((t ^ (__cheri_addr size_t)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize;
		    *(word * __CAP)(void * __CAP)dst =
		    *(const word * __CAP)(const void * __CAP)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
done:
	return (dst0);
}

size_t strlen(const char *str)
{
	const char *p;

	p = str;

	while (*p != '\0')
		p++;

	return (p - str);
}

#define ALIGN (sizeof(size_t)-1)
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)
#define MIN(a,b) ((a)<(b)?(a):(b))

size_t strlcpy(char *d, const char *s, size_t n)
{
    char *d0 = d;
    size_t *wd;

    int i = 0;
    int max_i = MIN(CAP_TAIL_LENGTH(d), CAP_TAIL_LENGTH(s));

    if (!n--) goto finish;
#ifdef __GNUC__
    typedef size_t __attribute__((__may_alias__)) word;
    const word *ws;
    if (((uintptr_t)s & ALIGN) == ((uintptr_t)d & ALIGN)) {
	for (; ((uintptr_t)s & ALIGN) && n && (*d=*s); n--, s++, d++, i++);
	if (n && *s) {
	    if (LT_IF_MORELLO_ELSE(i + sizeof(word) - 1, max_i, true)) {
		wd=(void *)d; ws=(const void *)s;
		for (; LT_IF_MORELLO_ELSE(i + sizeof(word) - 1, max_i, true) &&
		       n>=sizeof(size_t) && !HASZERO(*ws);
		     n-=sizeof(size_t), ws++, wd++, i += sizeof(word)) *wd = *ws;
		d=(void *)wd; s=(const void *)ws;
	    }
	}
    }
#endif
    for (; n && (*d=*s); n--, s++, d++);
    *d = 0;
finish:
    return d-d0 + strlen(s);
}

size_t strlcat(char *d, const char *s, size_t n)
{
    size_t l = strnlen(d, n);
    if (l == n) return l + strlen(s);
    return l + strlcpy(d+l, s, n-l);
}

size_t strnlen(const char *s, size_t n)
{
    const char *p = memchr(s, 0, n);
    return p ? p-s : n;
}

char *strdup(const char *s)
{
    size_t l = strlen(s);
    char *d = my_malloc(l+1);
    if (!d) return NULL;
    return memcpy(d, s, l+1);
}

char *strndup(const char *s, size_t n)
{
    size_t l = strnlen(s, n);
    char *d = my_malloc(l+1);
    if (!d) return NULL;
    memcpy(d, s, l);
    d[l] = 0;
    return d;
}

char *stpcpy(char *restrict d, const char *restrict s)
{
#ifdef __GNUC__
    typedef size_t __attribute__((__may_alias__)) word;
    word *wd;
    const word *ws;
    if ((uintptr_t)s % ALIGN == (uintptr_t)d % ALIGN) {
	for (; (uintptr_t)s % ALIGN; s++, d++)
	    if (!(*d=*s)) return (d);
	wd=(void *)d; ws=(const void *)s;
	for (; CAP_TAIL_LENGTH(ws) >= sizeof(word) && !HASZERO(*ws); *wd++ = *ws++);
	d=(void *)wd; s=(const void *)ws;
    }
#endif
    for (; (*d=*s); s++, d++);

    return (d);
}


char *strcpy(char *restrict dest, const char *restrict src)
{
    stpcpy(dest, src);
    return dest;
}
