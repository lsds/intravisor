#define _BSD_SOURCE
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#include "cheri_helpers.h"

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
			if (LT_IF_CHERI_ELSE(i + sizeof(word) - 1, max_i, true)) {
				wd=(void *)d; ws=(const void *)s;
				for (; LT_IF_CHERI_ELSE(i + sizeof(word) - 1, max_i, true) &&
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
