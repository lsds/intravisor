#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

char *argv[] = {"mosquitto",  "-c", "/mosquitto.conf", NULL};
int argc = 3;


int main(int argc0, char **argv0) {
	printf("app main\n");
	extern int mosquitto_main(int argc, char **argv);
	mosquitto_main(argc, argv);

	exit(0);
}
