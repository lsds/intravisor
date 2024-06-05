#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

#if 1
//test-memory for CI
char *argv[] = {"redis-server", "--test-memory", "100",NULL};
int argc = 3;

#else

char *argv[] = {"redis-server", "--daemonize", "no", "--save", "\"\"", "--bind", "127.0.0.1", "--port", "6379", NULL};
int argc = 9;

#endif


int main(int argc0, char **argv0) {
	printf("app main\n");
	extern int redis_main(int argc, char **argv);
	redis_main(argc, argv);

	exit(0);
}
