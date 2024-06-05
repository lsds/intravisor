#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

extern void copy_cpio(__intcap_t *);
extern long host_get_cpio_size( char *);
extern long host_load_cpio(char *, __intcap_t, long);


#define ROOT_CPIO "root.cpio"

void app_main() {
	printf("app_main inside kernel, just init ramfs\n\n");

#if 1
	long size = host_get_cpio_size(ROOT_CPIO);

	__intcap_t *cpio = malloc(size);

	long size2 = host_load_cpio(ROOT_CPIO, cpio, size);
	printf("size2 = %d, size = %d\n", size2, size);

	copy_cpio((__intcap_t *) cpio);

	free(cpio);
#endif
}