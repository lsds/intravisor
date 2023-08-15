#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

#include "loader.h"

static int lkl_mount_blockdev(const char *dev_str, const char *mnt_point, const char *fs_type, int flags, const char *data) {
	char _data[4096];
	int err;
	err = lkl_sys_access("/mnt", LKL_S_IRWXO);
	if(err < 0) {
		if(err == -LKL_ENOENT)
			err = lkl_sys_mkdir("/mnt", 0700);
		if(err < 0)
			goto fail;
	}
	err = lkl_sys_mkdir(mnt_point, 0700);
	if(err < 0)
		goto fail;
	if(data) {
		strncpy(_data, data, sizeof(_data));
		_data[sizeof(_data) - 1] = 0;
	} else {
		_data[0] = 0;
	}
	err = lkl_sys_mount((char *) dev_str, (char *) mnt_point, (char *) fs_type, flags, _data);
	if(err < 0) {
		lkl_sys_rmdir(mnt_point);
		goto fail;
	}

      fail:
	return err;
}

static void lkl_mount_shmtmpfs() {
	int err = lkl_sys_mount("tmpfs", "/dev/shm", "tmpfs", 0, "rw,nodev");
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(tmpfs) (/dev/shm): %s\n", lkl_strerror(err));
		//while(1);
	}
}

static void lkl_mount_tmpfs() {
	int err = lkl_sys_mount("tmpfs", "/tmp", "tmpfs", 0, "mode=0777");
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(tmpfs): %s\n", lkl_strerror(err));
		//while(1);
	}
}

char cap_file[] = "Hello world from cap!\n";

static void lkl_mount_capfs() {
	int err = lkl_sys_access("/cap", LKL_S_IRWXO);
	if(err < 0) {
		if(err == -LKL_ENOENT)
			err = lkl_sys_mkdir("/cap", 0700);
		if(err < 0) {
			lkl_printf("cannot create /txt %s\n", lkl_strerror(err));
		}
	}

	err = lkl_sys_mount("tmpfs", "/cap", "tmpfs", 0, "mode=0777");
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(tmpfs): %s\n", lkl_strerror(err));
		while(1) ;
	}

	for(int i = 1; i < 3; i++) {
		char fname[256];
		snprintf(fname, 256, "/cap/cf%d", i);
		lkl_printf("creating %s %d\n", fname, i);
		err = lkl_sys_mknod(fname, LKL_S_IFCHR | 0666, LKL_MKDEV(43, i));
		if(err != 0) {
			lkl_printf("Error: lkl_sys_mknod(%s) %s\n", fname, lkl_strerror(err));
			while(1) ;
		}
	}

	for(int i = 1; i < 5; i++) {
		char fname[256];
		snprintf(fname, 256, "/cap/ch%d", i);
		lkl_printf("creating %s %d\n", fname, i);
		err = lkl_sys_mknod(fname, LKL_S_IFCHR | 0666, LKL_MKDEV(45, i));
		if(err != 0) {
			lkl_printf("Error: lkl_sys_mknod(%s) %s\n", fname, lkl_strerror(err));
			while(1) ;
		}
	}

#ifdef GD
	for(int i = 1; i < 5; i++) {
		char fname[256];
		snprintf(fname, 256, "/cap/cg%d", i);
		lkl_printf("creating %s %d\n", fname, i);
		err = lkl_sys_mknod(fname, LKL_S_IFCHR | 0666, LKL_MKDEV(50, i));
		if(err != 0) {
			lkl_printf("Error: lkl_sys_mknod(%s) %s\n", fname, lkl_strerror(err));
			while(1) ;
		}
	}

#endif

}

static void lkl_mount_mntfs() {
	int err = lkl_sys_mount("tmpfs", "/mnt", "tmpfs", 0, "mode=0777");
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(tmpfs): %s\n", lkl_strerror(err));
		//while(1);
	}
}

static void lkl_mount_sysfs() {
	int err = lkl_sys_mount("none", "/sys", "sysfs", 0, NULL);
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(sysfs): %s\n", lkl_strerror(err));
		//while(1);
	}
}

static void lkl_mount_runfs() {
	int err = lkl_sys_mount("tmpfs", "/run", "tmpfs", 0, "mode=0700");
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(tmpfs): %s\n", lkl_strerror(err));
		//while(1);
	}
}

static void lkl_mount_procfs() {
	int err = lkl_sys_mount("proc", "/proc", "proc", 0, NULL);
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(procfs): %s\n", lkl_strerror(err));
		//while(1);
	}
}

static void lkl_mknods() {
	lkl_sys_unlink("/dev/null");
	int err = lkl_sys_mknod("/dev/null", LKL_S_IFCHR | 0666,
				LKL_MKDEV(1, 3));
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mknod(/dev/null) %s\n", lkl_strerror(err));
		//while(1);
	}

	lkl_sys_unlink("/dev/zero");
	err = lkl_sys_mknod("/dev/zero", LKL_S_IFCHR | 0666, LKL_MKDEV(1, 5));
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mknod(/dev/zero) %s\n", lkl_strerror(err));
		//while(1);
	}
	lkl_sys_unlink("/dev/random");
	err = lkl_sys_mknod("/dev/random", LKL_S_IFCHR | 0444, LKL_MKDEV(1, 8));
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mknod(/dev/random) %s\n", lkl_strerror(err));
		//while(1);
	}
	lkl_sys_unlink("/dev/urandom");
	err = lkl_sys_mknod("/dev/urandom", LKL_S_IFCHR | 0444, LKL_MKDEV(1, 9));
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mknod(/dev/urandom) %s\n", lkl_strerror(err));
		//while(1);
	}
}

static void lkl_prepare_rootfs(const char *dirname, int perm) {
	int err = lkl_sys_access(dirname, /*LKL_S_IRWXO */ F_OK);
	if(err < 0) {
		if(err == -LKL_ENOENT) {
			err = lkl_sys_mkdir(dirname, perm);
		}
		if(err < 0) {
			lkl_printf("Error: Unable to mkdir %s: %s\n", dirname, lkl_strerror(err));
			//while(1);
		}
	}
}

static void lkl_mount_devtmpfs(const char *mntpoint) {
	int err = lkl_sys_mount("devtmpfs", (char *) mntpoint, "devtmpfs", 0,
				NULL);
	if(err != 0) {
		lkl_printf("Error: lkl_sys_mount(devtmpfs): %s\n", lkl_strerror(err));
		//while(1);
	}
}

static int lkl_call(int nr, int args, ...) {
	long params[6];
	va_list vl;
	int i;

	va_start(vl, args);
	for(i = 0; i < args; i++)
		params[i] = va_arg(vl, long);
	va_end(vl);
	return lkl_syscall(nr, params);
}

void tree(char *basePath, const int root) {
	int i;
	char path[1000];
	struct dirent *dp;
//	printf("MUSL: %x %x %x\n", O_RDONLY, O_DIRECTORY, O_CLOEXEC);
//	printf("LKL: %x %x %x\n", LKL_O_RDONLY, LKL_O_DIRECTORY, LKL_O_CLOEXEC);
	DIR *dir = opendir(basePath);

	if(!dir)
		return;

	while((dp = readdir(dir)) != NULL) {
		if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
			for(i = 0; i < root; i++) {
				if(i % 2 == 0 || i == 0)
					printf("%c", 179);
				else
					printf(" ");

			}

			printf("%c%c%s\n", '-', '-', dp->d_name);

			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);
			tree(path, root + 2);
		}
	}

	closedir(dir);
}

void *mount_thread(void *arg) {
	struct s_mount *me = (struct s_mount *) arg;

	unsigned long *disk_io = me->disk_io;

#ifdef USE_HOST_NET
	printf("reserver FD for HOST_NET\n");
	for(int i = 0; i < 997; i++) {
		int err = 0;
		lkl_opendir("/", &err);
		if(err != 0) {
			lkl_printf("Error: unable to pad file descriptor table\n");
		}
	}
#endif
	lkl_prepare_rootfs("/dev", 0700);
	lkl_mount_devtmpfs("/dev");
#if 1
	lkl_printf("ADD disk\n");
	int disk_id = lkl_disk_add((struct lkl_disk *) disk_io);
	if(disk_id < 0) {
		lkl_printf("error = %s\n", lkl_strerror(disk_id));
		//while(1);
	}
	lkl_printf("disk id = %d\n", disk_id);
	lkl_printf("------ ADD disk DONE ------- \n");
#endif

	char *mpoint = "/mnt/123";
	int err = lkl_mount_blockdev("/dev/vda", mpoint, "ext4", 0, NULL);
	if(err < 0)
		lkl_printf("Error: lkl_mount_blockdev()=%s (%d)\n", lkl_strerror(err), err);
	lkl_prepare_rootfs("/mnt/123/dev", 0700);
	lkl_mount_devtmpfs("/mnt/123/dev");
//    lkl_copy_blkdev_nodes("/dev/", "/mnt/dev");
	lkl_sys_umount("/dev", 0);
	err = lkl_sys_chroot(mpoint);
	if(err != 0) {
		lkl_printf("Error: lkl_sys_chroot(%s): %s\n", mpoint, lkl_strerror(err));
		while(1) ;
	}
	err = lkl_sys_chdir("/");
	if(err != 0) {
		lkl_printf("Error: lkl_sys_chdir(%s): %s\n", mpoint, lkl_strerror(err));
		while(1) ;
	}
	lkl_printf("%s\t%d\n", __FILE__, __LINE__);
	lkl_printf("------ CHROOT DONE ------- \n");

	lkl_prepare_rootfs("/proc", 0700);
	lkl_mount_procfs();
	lkl_prepare_rootfs("/sys", 0700);
	lkl_mount_sysfs();
	lkl_prepare_rootfs("/run", 0700);
	lkl_mount_runfs();
	lkl_mknods();

	lkl_mount_capfs();

	lkl_printf("------ MOUNTS DONE ------- \n");

#if 1
//        lkl_opendir("/", &err);

		err = lkl_sys_open("/dev/null", O_RDWR, 0);
		printf("pad Descriptor Table: %d (%s)\n", err);
		perror("null");

		err = lkl_sys_open("/dev/null", O_RDWR, 0);
		printf("pad Descriptor Table: %d (%s)\n", err);
		perror("null");

		err = lkl_sys_open("/dev/null", O_RDWR, 0);
		printf("pad Descriptor Table: %d (%s)\n", err);
		perror("null");
#endif

//checks 
//////
	DIR *pDir;
	struct dirent *pDirent;
	pDir = opendir("/");
	if(pDir == NULL) {
		lkl_printf("Cannot open directory '%s'\n", "/");
		goto skip;
	}

	while((pDirent = readdir(pDir)) != NULL) {
		lkl_printf("[%s]\n", pDirent->d_name);
	}
	lkl_printf("------\n");

      skip:
	if(pDir)
		closedir(pDir);

	tree("/cap", 1);



	int rs = symlink("/proc/self/fd/0", "/dev/stdin");
	if(rs != 0) {
		perror("symlink1");
		while(1) ;
	}
	rs = symlink("/proc/self/fd/1", "/dev/stdout");
	if(rs != 0) {
		perror("symlink2");
		while(1) ;
	}
	rs = symlink("/proc/self/fd/2", "/dev/stderr");
	if(rs != 0) {
		perror("symlink3");
		while(1) ;
	}

	struct lkl_stat st_lkl;
	char tp[] = "/dev/stdin";
	err = lkl_sys_stat(tp, &st_lkl);
	if(err != 0) {
		fprintf(stderr, "Error: lkl_sys_stat(%s) %s\n", tp, lkl_strerror(err));
	}
	lkl_printf("st_lkl.st_mode = %lx\n", st_lkl.st_mode);
	lkl_printf("st_lkl.st_nlink = %lx\n", st_lkl.st_nlink);

	struct stat st_musl;
	err = stat(tp, &st_musl);
	if(err != 0) {
		fprintf(stderr, "Error: stat(%s) %s\n", tp, strerror(err));
	}
	lkl_printf("st_musl.st_mode = %lx\n", st_musl.st_mode);
	lkl_printf("st_musl.st_nlink = %lx\n", st_musl.st_nlink);
	lkl_printf("st_musl.st_uid = %lx\n", st_musl.st_uid);
	lkl_printf("st_musl.st_gid = %lx\n", st_musl.st_gid);

	printf("Size of musl stat: %zu\n", sizeof(struct stat));
	printf("Offset of st_mode:	%zu, Size: %zu\n", offsetof(struct stat, st_mode), sizeof(st_musl.st_mode));
	printf("Offset of st_nlink:	%zu, Size: %zu\n", offsetof(struct stat, st_nlink), sizeof(st_musl.st_nlink));
	printf("Offset of st_uid:	%zu, Size: %zu\n", offsetof(struct stat, st_uid), sizeof(st_musl.st_uid));
	printf("Offset of st_gid:	%zu, Size: %zu\n", offsetof(struct stat, st_gid), sizeof(st_musl.st_gid));

	printf("Size of lkl stat: %zu\n", sizeof(struct lkl_stat));
	printf("Offset of st_mode:	%zu, Size: %zu\n", offsetof(struct lkl_stat, st_mode), sizeof(st_lkl.st_mode));
	printf("Offset of st_nlink:	%zu, Size: %zu\n", offsetof(struct lkl_stat, st_nlink), sizeof(st_lkl.st_nlink));
	printf("Offset of st_uid:	%zu, Size: %zu\n", offsetof(struct lkl_stat, st_uid), sizeof(st_lkl.st_uid));
	printf("Offset of st_gid:	%zu, Size: %zu\n", offsetof(struct lkl_stat, st_gid), sizeof(st_lkl.st_gid));

	printf("S_IFMT = %lx, S_IFDIR = %lx\n", S_IFMT, S_IFDIR);
	printf("O_DIRECTORY = 0x%lx\n", O_DIRECTORY);
	printf("is_dir(/dev/stdin): %d (LKL) %d (musl)\n", S_ISDIR(st_lkl.st_mode), S_ISDIR(st_musl.st_mode));

	if((st_musl.st_mode != st_lkl.st_mode)
	   || (st_musl.st_nlink != st_lkl.st_nlink)) {
		lkl_printf("BUG: stat in musl differs from stat in LKL \n");
	}

	int rnd = open("/dev/urandom", O_RDWR);
	if(rnd < 0) {
		lkl_printf("where is random\n");
		while(1) ;
	}

	long rnd_val;
	int rret = write(rnd, &lkl_call, 512);
	printf("wrote %d to urandom\n", rret);
	rret = read(rnd, &rnd_val, sizeof(rnd_val));
	printf(" rret = %d rnd_val = %d\n", rret, rnd_val);
	close(rnd);

#if 0
	int pc = open("/proc/sys/vm/drop_caches", O_RDWR);
	if(pc < 0) {
		lkl_printf("where are caches\n");
		while(1) ;
	}

	char f_cmd = '3';

	int w = write(pc, &f_cmd, 1);
	if(w != 1) {
		perror("write error");
		while(1) ;
	}

	close(pc);
#endif
}
