#include <unistd.h>
#include <stdio.h>

static int test_getlogin();
static int test_getlogin_r();
static int test_ttyname();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
		case '0': return test_getlogin();
		case '1': return test_getlogin_r();
		case '2': return test_ttyname();
		default: return 2;
	}
}

static int test_getlogin()
{
	char *login = getlogin();
	printf("getlogin = %s\n", login);
	if (__builtin_cheri_tag_get(login) == 0) {
		return 1;
	}
	return 0;
}

static int test_getlogin_r()
{
	char login[32] = {};
	int r = getlogin_r(login, sizeof(login));
	printf("getlogin_r = %s\n", login);
	if (r) {
		perror("getlogin_r");
	}
	return r;
}

static int test_ttyname()
{
	char *name = ttyname(0); // stdin
	printf("ttyname = %s\n", name);
	if (__builtin_cheri_tag_get(name) == 0) {
		return 1;
	}
	return 0;
}
