#include <stdlib.h>

#define _GNU_SOURCE

#include <libgen.h>

#include <unistd.h>
#include <limits.h>

#include <stdio.h>
#include <string.h>


static int test_a64l();
static int test_basename();
static int test_dirname();
static int test_getcwd();
//static int test_getwd();
static int test_get_current_dir_name();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
	case '0': return test_a64l();
	case '1': return test_basename();
	case '2': return test_dirname();
	case '3': return test_getcwd();
//	case '4': return test_getwd(); // getwd is not implemented in Musl
	case '5': return test_get_current_dir_name();
	default: return 2;
	}
}

static int test_a64l()
{
	long z = a64l("hello");
	char *res = l64a(z);
	printf("res = %s\n", res);
	return strncmp(res, "hello", 6);
}

static int test_basename()
{
	char path0[] = "/usr/lib";
	if (strcmp(basename(path0), "lib")) { return 1; }
	char path1[] = "/usr/";
	if (strcmp(basename(path1), "usr")) { return 1; }
	char path2[] = "usr";
	if (strcmp(basename(path2), "usr")) { return 1; }
	char path3[] = "/";
	if (strcmp(basename(path3), "/")) { return 1; }
	char path4[] = ".";
	if (strcmp(basename(path4), ".")) { return 1; }
	char path5[] = "..";
	if (strcmp(basename(path5), "..")) { return 1; }
	return 0;
}

static int test_dirname()
{
	char path0[] = "/usr/lib";
	if (strcmp(dirname(path0), "/usr")) { return 1; }
	char path1[] = "/usr/";
	if (strcmp(dirname(path1), "/")) { return 1; }
	char path2[] = "usr";
	if (strcmp(dirname(path2), ".")) { return 1; }
	char path3[] = "/";
	if (strcmp(dirname(path3), "/")) { return 1; }
	char path4[] = ".";
	if (strcmp(dirname(path4), ".")) { return 1; }
	char path5[] = "..";
	if (strcmp(dirname(path5), ".")) { return 1; }
	return 0;
}

static int test_getcwd()
{
	char *res;
	res = getcwd(NULL, 0);
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 0) {
		free(res);
		return 1;
	}
	free(res);
	res = getcwd(NULL, 2);
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 1) {
		free(res);
		return 1;
	}
	free(res);
	char buffer[PATH_MAX];
	res = getcwd(buffer, sizeof(buffer));
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 0) {
		return 1;
	}
	char buffer1[2];
	res = getcwd(buffer1, sizeof(buffer1));
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 1) {
		return 1;
	}
	res = getcwd(NULL, (size_t)-1);
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 1) {
		return 1;
	}
	return 0;
}

//static int test_getwd()
//{
//	char buffer[PATH_MAX];
//	char *res = getwd(buffer);
//	printf("res = %s\n", res);
//	if (__builtin_cheri_tag_get(res) == 0) {
//		return 1;
//	}
//	return 0;
//}

static int test_get_current_dir_name()
{
	char *res = get_current_dir_name();
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 0) {
		free(res);
		return 1;
	}
	free(res);
	return 0;
}
