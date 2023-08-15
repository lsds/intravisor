#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

extern void copy_cpio(__intcap_t *);
extern long host_get_cpio_size( char *);
extern long host_load_cpio(char *, __intcap_t, long);

char *argv[] = {"uros2", NULL};
int argc = 1;

extern void host_close(int);

int net_close(int fildes) {
	host_close(fildes);
}

void app_main() {
	printf("app main\n");

	printf("--------- MicroROS2 ------- \n");

	extern int main(int argc, char **argv);
	main(argc, argv);



}