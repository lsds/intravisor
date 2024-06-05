#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>


extern void so_test(void);

int main(int argc0, char **argv0) {
	printf("app main\n");

	so_test();

	exit(0);
}
