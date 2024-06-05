#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static int (*volatile psprintf)(char *, const char *, ...);

static int format_vs(char *buffer, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int z = vsprintf(buffer, fmt, args);
	va_end(args);
	return z;
}

int test_psprintf(int argc, char *argv[]) {
	char buffer[64] = {};
	psprintf(buffer, "hello %s %d %p", "morello", argc, (void *)argv);
	printf("%s\n", buffer);
	return strncmp(buffer, "hello morello 2 0x", 18);
}

int test_asprintf(int argc, char *argv[]) {
	char *buffer = NULL;
	size_t len = asprintf(&buffer, "hello %s %d %p", "morello", argc, (void *)argv);
	printf("%s\n", buffer);
	if (len < 18) return 1;
	return strncmp(buffer, "hello morello 2 0x", 18);
}

int main (int argc, char *argv[]) {
	switch (argv[1][0]) {
	case '0':
		psprintf = sprintf;
		return test_psprintf(argc, argv);
	case '1':
		psprintf = format_vs;
		return test_psprintf(argc, argv);
	case '2':
		return test_asprintf(argc, argv);
	default:
		return 1;
	}
}
