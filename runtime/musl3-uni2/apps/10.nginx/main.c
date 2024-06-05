#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

char *argv[] = {"nginx",  "-c", "/nginx/nginx.conf", NULL};
int argc = 3;


int main(int argc0, char **argv0) {
	printf("app main\n");
	extern int nginx_main(int argc, char **argv);
	nginx_main(argc, argv);

	exit(0);
}
