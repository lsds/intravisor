#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

extern int speedtest_main(int argc, char **argv);

char *argv[] = {"speedtest1", "/abc", "--size", "100", NULL};
int argc = 4;


int main(int argc0, char *argv0[]) {
	speedtest_main(argc, argv);

	exit(0);
}
