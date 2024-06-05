#include <search.h>
#include <string.h>
#include <sys/param.h>

void *lsearch(const void *key, void *base, size_t *nelp, size_t width,
	int (*compar)(const void *, const void *))
{
	char (*p)[width] = base;
	size_t n = *nelp;
	size_t i;

	for (i = 0; i < n; i++)
		if (compar(key, p[i]) == 0)
			return p[i];
	*nelp = n+1;
#ifdef __CHERI_PURE_CAPABILITY__
	width = MIN(width, __builtin_cheri_length_get(key) - __builtin_cheri_offset_get(key));
#endif
	return memcpy(p[n], key, width);
}

void *lfind(const void *key, const void *base, size_t *nelp,
	size_t width, int (*compar)(const void *, const void *))
{
	char (*p)[width] = (void *)base;
	size_t n = *nelp;
	size_t i;

	for (i = 0; i < n; i++)
		if (compar(key, p[i]) == 0)
			return p[i];
	return 0;
}


