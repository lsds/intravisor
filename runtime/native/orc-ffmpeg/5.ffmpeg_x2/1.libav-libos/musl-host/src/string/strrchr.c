#include <string.h>

extern void *__memrchr(const void *m, int c, size_t n);

char *strrchr(const char *s, int c)
{
	return __memrchr(s, c, strlen(s) + 1);
}
