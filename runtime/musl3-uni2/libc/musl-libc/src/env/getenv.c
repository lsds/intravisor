#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cheri_helpers.h"

char *getenv(const char *name)
{
	size_t l = __strchrnul(name, '=') - name;
	if (l && !name[l] && __environ)
		for (char **e = __environ; *e; e++)
			if (!strncmp(name, *e, l) && l[*e] == '=') {
				char* res = *e + l+1;
				return RESTRICT_BNDS_IF_CHERI(res, strlen(res) + 1);
			}
	return 0;
}
