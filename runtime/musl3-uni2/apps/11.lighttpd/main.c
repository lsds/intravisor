#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

char *argv[] = {"lighttpd",  "-f", "/lighttpd/lighttpd.conf", NULL};
int argc = 3;


int main(int argc0, char **argv0) {
	printf("app main\n");
	extern int server_main(int argc, char **argv);
	server_main(argc, argv);

	exit(0);
}
