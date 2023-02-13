#include <stdlib.h>
#include "cheri_helpers.h"

void *bsearch(const void *key, const void *base, size_t nel, size_t width, int (*cmp)(const void *, const void *))
{
	void *try;
	int sign;
	while (nel > 0) {
		try = (char *)base + width*(nel/2);
		sign = cmp(key, RESTRICT_BNDS_IF_CHERI(try, width));
		if (sign < 0) {
			nel /= 2;
		} else if (sign > 0) {
			base = (char *)try + width;
			nel -= nel/2+1;
		} else {
		  return try;
		}
	}
	return NULL;
}
