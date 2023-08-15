#include <stdio.h>
#include <stdlib.h>

char *argv[] = {"redis-server", "--daemonize", "no", "--save", "\"\"", "--bind", "127.0.0.1", "--port", "6379", NULL};
int argc = 9;


void app_main() {
	printf("app main\n");
	extern int redis_main(int argc, char **argv);
	redis_main(argc, argv);
}