#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

#define HW_FILE "/musl-hello.txt"

int main(int argc, char **argv) {
	write(1, "Hello world\n", sizeof("Hello world\n"));

	printf("Hello using printf\n");

	char buf[100];
	FILE *f = fopen(HW_FILE, "r");
	if (!f) {
		fprintf(stderr, "Could not open file %s: %s\n", HW_FILE, strerror(errno));
		exit(1);
	}

	if (fgets(buf, sizeof(buf), f) == buf) {
		printf("%s", buf);
	} else {
		fprintf(stderr, "Could not read first line of file %s: %s\n", HW_FILE, strerror(errno));
		exit(1);
	}

	struct stat st_musl;
	printf("Size of musl stat: %zu\n", sizeof(struct stat));

	printf("Offset of st_dev:	%zu, Size: %zu\n", offsetof(struct stat, st_dev), sizeof(st_musl.st_dev));
	printf("Offset of st_ino:	%zu, Size: %zu\n", offsetof(struct stat, st_ino), sizeof(st_musl.st_ino));
	printf("Offset of st_mode:	%zu, Size: %zu\n", offsetof(struct stat, st_mode), sizeof(st_musl.st_mode));
	printf("Offset of st_nlink:	%zu, Size: %zu\n", offsetof(struct stat, st_nlink), sizeof(st_musl.st_nlink));
	printf("Offset of st_uid:	%zu, Size: %zu\n", offsetof(struct stat, st_uid), sizeof(st_musl.st_uid));
	printf("Offset of st_gid:	%zu, Size: %zu\n", offsetof(struct stat, st_gid), sizeof(st_musl.st_gid));
	printf("Offset of st_rdev:	%zu, Size: %zu\n", offsetof(struct stat, st_rdev), sizeof(st_musl.st_rdev));
	printf("Offset of __pad:	%zu, Size: %zu\n", offsetof(struct stat, __pad), sizeof(st_musl.__pad));
	printf("Offset of si_size:	%zu, Size: %zu\n", offsetof(struct stat, st_size), sizeof(st_musl.st_size));
	printf("Offset of st_blksize:	%zu, Size: %zu\n", offsetof(struct stat, st_blksize), sizeof(st_musl.st_blksize));
	printf("Offset of __pad2:	%zu, Size: %zu\n", offsetof(struct stat, __pad2), sizeof(st_musl.__pad2));
	printf("Offset of st_blocks:	%zu, Size: %zu\n", offsetof(struct stat, st_blocks), sizeof(st_musl.st_blocks));
	printf("Offset of st_atim:	%zu, Size: %zu\n", offsetof(struct stat, st_atim), sizeof(st_musl.st_atim));
	printf("Offset of st_mtim:	%zu, Size: %zu\n", offsetof(struct stat, st_mtim), sizeof(st_musl.st_mtim));
	printf("Offset of st_ctim:	%zu, Size: %zu\n", offsetof(struct stat, st_ctim), sizeof(st_musl.st_ctim));
	printf("Offset of unused:	%zu, Size: %zu\n", offsetof(struct stat, __unused), sizeof(st_musl.__unused));


	printf("S_IFMT = %lx, S_IFDIR = %lx\n", S_IFMT, S_IFDIR);
	printf("O_DIRECTORY = 0x%lx\n", O_DIRECTORY);

#if 0
	char tp[] = "/dev/stdin";
	int err = stat(tp, &st_musl);
	if(err != 0) {
		fprintf(stderr, "Error: stat(%s) %s\n", tp, strerror(err));
	}
	printf("st_musl.st_mode = %lx\n", st_musl.st_mode);
	printf("st_musl.st_nlink = %lx\n", st_musl.st_nlink);
	printf("st_musl.st_uid = %lx\n", st_musl.st_uid);
	printf("st_musl.st_gid = %lx\n", st_musl.st_gid);
	printf("is_dir(/dev/stdin): %d (musl)\n", S_ISDIR(st_musl.st_mode));
#endif


	exit(0);
}
