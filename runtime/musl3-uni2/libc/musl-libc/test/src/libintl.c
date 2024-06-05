#include <stdio.h>

char *bindtextdomain(const char *, const char *);

static int
test_bindtextdomain()
{
	char *res = bindtextdomain("morello", "musl");
	printf("%s\n", res);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
	case '0': return test_bindtextdomain();
	default: return 2;
	}
}
