#include <stdio.h>

int main (int argc, char *argv[])
{
	printf("hello morello\n");
	int len = (int)__builtin_cheri_length_get(argv);
	return len;
}
