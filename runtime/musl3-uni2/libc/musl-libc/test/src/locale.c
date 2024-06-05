#include <libintl.h>
#include <stdio.h>

static int test_bind_textdomain_codeset();
static int test_textdomain();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
	case '0': return test_bind_textdomain_codeset();
	case '1': return test_textdomain();
	default: return 2;
	}
}

static int test_bind_textdomain_codeset()
{
	char *res = bind_textdomain_codeset("morello-project.org", 0);
	printf("res = %s\n", res);
	if (res != 0) {
		return 1;
	}
	res = bind_textdomain_codeset("morello-project.org", "utf-8");
	printf("res = %s\n", res);
	if (res != 0) {
		return 1;
	}
	res = bind_textdomain_codeset("morello-project.org", 0);
	printf("res = %s\n", res);
	if (res != 0) {
		return 1;
	}
	return 0;
}

static int test_textdomain()
{
	char *res = textdomain(0);
	if (__builtin_cheri_tag_get(res) == 0) {
		return 1;
	}
	printf("res = %s\n", res);
	res = textdomain("morello-project.org");
	printf("res = %s\n", res);
	if (__builtin_cheri_tag_get(res) == 0) {
		return 1;
	}
	return 0;
}
