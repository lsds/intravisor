#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "morello_helpers.h"
#include "hostcalls.h"

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

#define true 1

#define NL	1

int carrie_errno;


int *__errno_location(void)
{
//	printf("%s\n", __func__);

//	carrie_errno = host_get_errno();

//	printf("current errno = %d\n", carrie_errno);

	return &carrie_errno; //should be thread-local
}

_Noreturn void __assert_fail(const char *expr, const char *file, int line, const char *func)
{
	printf("Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
	while(1);
}
