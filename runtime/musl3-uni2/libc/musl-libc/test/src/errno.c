#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(int argc, char **argv) {
	switch (argv[1][0]) {
	case '0':
		printf("%s\n", strerror(ERESERVATION));
		break;
	default:
		return 1;
	}

	return 0;
}
