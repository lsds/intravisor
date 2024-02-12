#include "stdio_impl.h"

#ifdef __GNUC__
__attribute__((__noinline__))
#endif

static inline int do_getc(FILE *f)
{
	return getc_unlocked(f);
}
