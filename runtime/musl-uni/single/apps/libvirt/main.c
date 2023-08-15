#include <stdio.h>
#include <stdlib.h>


extern void copy_cpio(__intcap_t *);
extern long host_get_cpio_size( char *);
extern long host_load_cpio(char *, __intcap_t, long);

char *argv[] = {"libvirt", "-v", "-l", "-f", "/libvirt.conf", NULL};
int argc = 5;


void app_main() {
	printf("app main\n");

	long size = host_get_cpio_size("root_libvirt.cpio");
	__intcap_t *cpio = malloc(size);
	long size2 = host_load_cpio("root_libvirt.cpio", cpio, size);
	printf("size2 = %d, size = %d\n", size2, size);
	copy_cpio((__intcap_t *) cpio);
	free(cpio);

	printf("--------- LibVirt ------- \n");

	extern int libvirt_main(int argc, char **argv);
	libvirt_main(argc, argv);



}