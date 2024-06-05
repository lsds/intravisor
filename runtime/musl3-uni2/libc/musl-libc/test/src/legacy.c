#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>

static int test_cuserid();
static int test_getusershell();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
	case '0': return test_cuserid();
	case '1': return test_getusershell();
	default: return 2;
	}
}

static int test_cuserid()
{
	char buf[L_cuserid] = {};
	char *res = cuserid(buf); // null use case is not supported
	printf("cuserid = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 0) {
		return 1;
	}
	return 0;
}

static int test_getusershell()
{
	char *res = getusershell();
	printf("getusershell = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 0) {
		return 1;
	}
	return 0;
}
