#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

#if 0
char *argv[] = {"python",  "-B", "-c", "print('hello world')",NULL};
int argc = 4;
#endif

#if 1
char *argv[] = {"python",  "-B", "/helloworld.py",NULL};
int argc = 3;
#endif

int main(int argc0, char **argv0) {
	printf("app main\n");
	extern int python_main(int argc, char **argv);
	python_main(argc, argv);

	exit(0);
}
