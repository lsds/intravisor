#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#include "cheri_helpers.h"

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

size_t strlen(const char *s)
{
	const char *a = s;
	size_t i = 0;
	size_t max_i = CAP_TAIL_LENGTH(s);
#if defined(__GNUC__)
	typedef size_t __attribute__((__may_alias__)) word;
	const word *w;
	for (; (uintptr_t)s % ALIGN; s++, i++) if (!*s) return s - a;
	for (w = (const void *)s;
	     LT_IF_CHERI_ELSE(i + sizeof(word) - 1, max_i, true) && !HASZERO(*w);
	     w++, i += sizeof(word))
	  ;
	s = (const void *)w;
#endif
	for (; *s; s++);
	return s-a;
}
