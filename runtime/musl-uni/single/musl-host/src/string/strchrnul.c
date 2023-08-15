#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>

#include "cheri_helpers.h"

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

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
	if (LT_IF_CHERI_ELSE(i + sizeof(word) - 1, max_i, true)) {
		for (w = (void *)s;
		     LT_IF_CHERI_ELSE(i + sizeof(word) - 1, max_i, true) &&
		       !HASZERO(*w) && !HASZERO(*w ^ k);
		     w++, i+=sizeof(word))
		   ;
		s = (void *)w;
	}
#endif
	for (; *s && *(unsigned char *)s != c; s++);
	return ((char *)s);
}

weak_alias(__strchrnul, strchrnul);
