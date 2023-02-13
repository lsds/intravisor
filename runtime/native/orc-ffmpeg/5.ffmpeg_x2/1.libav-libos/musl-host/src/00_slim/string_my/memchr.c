#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#include "cheri_helpers.h"

#define SS (sizeof(size_t))
#define ALIGN (sizeof(size_t)-1)
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

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
		     LT_IF_CHERI_ELSE(i + sizeof(word) - 1, max_i, true)
		     && !HASZERO(*w ^ k);
		     w++, n -= SS, i += sizeof(word))
		  ;
		s = (const void *)w;
	}
#endif
	for (; n && *s != c; s++, n--);
	return n ? ((void *)s) : 0;
}
