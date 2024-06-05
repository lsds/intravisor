#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stddef.h>

static int test_ctime();
static int test_ctime_r();
static int test_getdate();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
	case '0': return test_ctime();
	case '1': return test_ctime_r();
	case '2': return test_getdate();
	default: return 2;
	}
}

static int test_ctime()
{
	time_t x = 0;
	char *res = ctime(&x);
	printf("res = %s", res);
	if (!res) {
		return 1;
	}
	return 0;
}

static int test_ctime_r()
{
	time_t x = 0;
	char buf[256];
	char *res = ctime_r(&x, buf);
	printf("res = %s", res);
	if (!res) {
		return 1;
	}
	size_t sz = __builtin_cheri_length_get(res);
	if (sz != sizeof(buf)) {
		return 2;
	}
	return 0;
}

static int test_getdate()
{
	struct tm *res = getdate("2009-12-28");
	printf("res = %p\n", (void *)res);
	if (!res) {
		printf("getdate_err = %d\n", getdate_err);
		return 1;
	} else {
		printf("%04d-%02d-%02d\n", 1900 + res->tm_year, 1 + res->tm_mon, res->tm_mday);
	}
	return 0;
}
