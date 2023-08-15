#include <string.h>
#include <libgen.h>
#include <limits.h>
#include "cheri_helpers.h"

char *basename(char *s)
{
	size_t i, sz;
	static char d[PATH_MAX];

	if (!s || !*s) return ".";
	i = strlen(s)-1;
	for (; i&&s[i]=='/'; i--);
	for (sz=i+1; i&&s[i-1]!='/'; i--);

	sz -= i;
	strncpy(d, s+i, sz);
	d[sz] = 0;
	return RESTRICT_BNDS_IF_CHERI(d, sz+1);
}

weak_alias(basename, __xpg_basename);
