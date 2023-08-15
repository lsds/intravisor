#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stddef.h>

main() {
	printf("hello world\n");

	char tp[]="/dev/stdin";
	struct stat stat2;
        int err = stat(tp, &stat2);
        if (err != 0) {
            fprintf(stderr, "Error: stat(%s) %s\n",
                tp, strerror(err));
        }

        printf("stat2.st_mode = %lx\n", stat2.st_mode);
        printf("stat2.st_nlink = %lx\n", stat2.st_nlink);
        printf("stat2.st_uid = %lx\n", stat2.st_uid);
	printf("stat2.st_gid = %lx\n", stat2.st_gid);

	printf("Size of stat: %zu\n", sizeof(struct stat));
	printf("Offset of st_mode:	%zu, Size: %zu\n", offsetof(struct stat, st_mode), sizeof(stat2.st_mode));
	printf("Offset of st_nlink:	%zu, Size: %zu\n", offsetof(struct stat, st_nlink), sizeof(stat2.st_nlink));
	printf("Offset of st_uid:	%zu, Size: %zu\n", offsetof(struct stat, st_uid), sizeof(stat2.st_uid));
	printf("Offset of st_gid:	%zu, Size: %zu\n", offsetof(struct stat, st_gid), sizeof(stat2.st_gid));
}
