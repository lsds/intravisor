#include <string.h>

extern char *__stpcpy(char *restrict d, const char *restrict s);

char *strcpy(char *restrict dest, const char *restrict src)
{
	__stpcpy(dest, src);
	return dest;
}
