#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "syscalls.h"
#include <sys/stat.h>

#include <dirent.h>
#include <string.h>


#define CONFIG_LIBVFSCORE_ROOTFS "ramfs"
static const char *rootfs   = CONFIG_LIBVFSCORE_ROOTFS;
static const char *rootdev  = "";
static unsigned long	rootflags;
static const char *rootopts = "";

print_stat() {
	struct stat st_libos;
	printf("Size of libos stat: %zu\n", sizeof(struct stat));

	printf("Offset of st_dev:	%zu, Size: %zu\n", offsetof(struct stat, st_dev), sizeof(st_libos.st_dev));
	printf("Offset of st_ino:	%zu, Size: %zu\n", offsetof(struct stat, st_ino), sizeof(st_libos.st_ino));
	printf("Offset of st_mode:	%zu, Size: %zu\n", offsetof(struct stat, st_mode), sizeof(st_libos.st_mode));
	printf("Offset of st_nlink:	%zu, Size: %zu\n", offsetof(struct stat, st_nlink), sizeof(st_libos.st_nlink));
	printf("Offset of st_uid:	%zu, Size: %zu\n", offsetof(struct stat, st_uid), sizeof(st_libos.st_uid));
	printf("Offset of st_gid:	%zu, Size: %zu\n", offsetof(struct stat, st_gid), sizeof(st_libos.st_gid));
	printf("Offset of st_rdev:	%zu, Size: %zu\n", offsetof(struct stat, st_rdev), sizeof(st_libos.st_rdev));
	printf("Offset of __pad:	%zu, Size: %zu\n", offsetof(struct stat, __pad), sizeof(st_libos.__pad));
	printf("Offset of si_size:	%zu, Size: %zu\n", offsetof(struct stat, st_size), sizeof(st_libos.st_size));
	printf("Offset of st_blksize:	%zu, Size: %zu\n", offsetof(struct stat, st_blksize), sizeof(st_libos.st_blksize));
	printf("Offset of __pad2:	%zu, Size: %zu\n", offsetof(struct stat, __pad2), sizeof(st_libos.__pad2));
	printf("Offset of st_blocks:	%zu, Size: %zu\n", offsetof(struct stat, st_blocks), sizeof(st_libos.st_blocks));
	printf("Offset of st_atim:	%zu, Size: %zu\n", offsetof(struct stat, st_atim), sizeof(st_libos.st_atim));
	printf("Offset of st_mtim:	%zu, Size: %zu\n", offsetof(struct stat, st_mtim), sizeof(st_libos.st_mtim));
	printf("Offset of st_ctim:	%zu, Size: %zu\n", offsetof(struct stat, st_ctim), sizeof(st_libos.st_ctim));
	printf("Offset of unused:	%zu, Size: %zu\n", offsetof(struct stat, unused), sizeof(st_libos.unused));


	printf("S_IFMT = %lx, S_IFDIR = %lx\n", S_IFMT, S_IFDIR);
	printf("O_DIRECTORY = 0x%lx\n", O_DIRECTORY);

#if 0
	char tp[] = "/dev/stdin";
	int err = stat(tp, &st_libos);
	if(err != 0) {
		fprintf(stderr, "Error: stat(%s) %s\n", tp, strerror(err));
	}
	printf("st_libos.st_mode = %lx\n", st_libos.st_mode);
	printf("st_libos.st_nlink = %lx\n", st_libos.st_nlink);
	printf("st_libos.st_uid = %lx\n", st_libos.st_uid);
	printf("st_libos.st_gid = %lx\n", st_libos.st_gid);

	printf("is_dir(/dev/stdin): %d (libos)\n", S_ISDIR(st_musl.st_mode));
#endif
}

void unikraft_init(void) {
	printf("prepare nolibos init\n\n");



	void *ptr = malloc(1024);
	printf("ptr = %p, %x\n", ptr, (int) ptr);
	vfscore_init();
	printf("%d\n", __LINE__);
	vfscore_automount();
	printf("%d\n", __LINE__);
	init_posix_fdtab();
	term_posix_fdtab();
	printf("%d\n", __LINE__);
	devfs_automount();
	printf("%d\n", __LINE__);
	devfs_register();
	printf("%d\n", __LINE__);
	devfs_register_null();
	printf("%d\n", __LINE__);
	devfs_register_stdout();
	printf("%d\n", __LINE__);
	init_stdio();
	printf("%d\n", __LINE__);
#ifdef DEBUG_VFS 
	vfscore_mount_dump();
#endif
	printf("%d\n", __LINE__);
	print_stat();
	printf("%d\n", __LINE__);
	_uk_swrand_init();
	printf("%d\n", __LINE__);
	posix_socket_family_lib_init();
	printf("%d\n", __LINE__);

	int fd = -5;
	fd = open("/test", 02 | 0100, 0666);
	printf("fd = %d\n", fd);
	int ret1 = write(fd, "hello world", sizeof("hello world"));
	close(fd);
	printf("wrote %d \n", ret1);

	fd = open("/test", 02, 0666);
//	fd = open("/test", 02, 0666);
//	fd = open("/test", 02, 0666);
//	fd = open("/test", 02, 0666);
	printf("fd = %d\n", fd);
	char data[128];
	int ret2 = read(fd, data, 128);
	printf("read %d from file = %s\n", ret2, data);
	close(fd);

	printf("....testing /dev/zero\n");
	fd = open("/dev/zero", 02, 0666);
	printf("/dev/zero fd = %d\n", fd);
	ret2 = read(fd, data, 128);
	printf("read %d bytes from /dev/zero\n", ret2);
	close(fd);
	printf("....testing /dev/random\n");
	fd = open("/dev/random", 02, 0666);
	printf("/dev/zero fd = %d\n", fd);
	unsigned long rd;
	ret2 = read(fd, &rd, sizeof(rd));
	printf("read %d bytes from /dev/random, rd=%lx\n", ret2, rd);
	close(fd);

	printf("....testing /dev/stdout\n");
	fd = open("/dev/stdout", 02, 0666);
	printf("/dev/stdout fd = %d\n", fd);
	char hs[]="Hello /dev/stdout\n";
	printf("write %d bytes to /dev/stdout ('%s')\n", sizeof(hs), hs);
	write(fd, hs, sizeof(hs));
	close(fd);

}

