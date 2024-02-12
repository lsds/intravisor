#include <stdio.h>
#include <stdlib.h>


extern void copy_cpio(__intcap_t *);
extern long host_get_cpio_size( char *);
extern long host_load_cpio(char *, __intcap_t, long);

//remove -t 20 for real use

char *argv[] = {"libvirt", "-v", "-l", "-f", "/libvirt.conf", "-t", "20", NULL};
int argc = 7;

extern 	long host_parse_and_spawn_yaml(char *, size_t);

int parse_and_spawn_yaml(char *yaml, size_t len) { 
	return (int) host_parse_and_spawn_yaml(yaml, len);
};

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