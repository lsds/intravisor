#include <string.h>
#include <libgen.h>
#include <limits.h>
#include "cheri_helpers.h"

char *dirname(char *s)
{
	size_t i;
	static char d[PATH_MAX];

	if (!s || !*s) return ".";
	i = strlen(s)-1;
	for (; s[i]=='/'; i--) if (!i) return "/";
	for (; s[i]!='/'; i--) if (!i) return ".";
	for (; s[i]=='/'; i--) if (!i) return "/";

	strncpy(d, s, ++i);
	d[i] = 0;
	return RESTRICT_BNDS_IF_CHERI(d, i+1);
}
