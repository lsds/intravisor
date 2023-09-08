#include <stdarg.h>
       #define _GNU_SOURCE
       #include <dirent.h>     /* Defines DT_* constants */
       #include <fcntl.h>
       #include <stdint.h>
       #include <stdio.h>
       #include <unistd.h>
       #include <stdlib.h>
       #include <sys/stat.h>
       #include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <lkl.h>
#include <lkl_host.h>


       struct linux_dirent {
           unsigned long  d_ino;
           off_t          d_off;
           unsigned short d_reclen;
           char           d_name[];
       };

#define BUF_SIZE 1024

static int lkl_call(int nr, int args, ...)
{
	long params[6];
	va_list vl;
	int i;

	va_start(vl, args);
	for (i = 0; i < args; i++)
		params[i] = va_arg(vl, long);
	va_end(vl);
	return lkl_syscall(nr, params);
}

static int lkl_mount_blockdev(const char* dev_str, const char* mnt_point,
                       const char *fs_type, int flags, const char* data) {
    char _data[4096];
    int err;

    err = lkl_sys_access("/mnt", LKL_S_IRWXO);
    if (err < 0) {
        if (err == -LKL_ENOENT)
            err = lkl_sys_mkdir("/mnt", 0700);
        if (err < 0)
            goto fail;
    }

    err = lkl_sys_mkdir(mnt_point, 0700);
    if (err < 0)
        goto fail;

    if (data) {
        strncpy(_data, data, sizeof(_data));
        _data[sizeof(_data) - 1] = 0;
    } else {
        _data[0] = 0;
    }

    err = lkl_sys_mount((char*)dev_str, (char*)mnt_point, (char*)fs_type, flags, _data);
    if (err < 0) {
        lkl_sys_rmdir(mnt_point);
        goto fail;
    }

fail:
    return err;
}

static void lkl_mount_shmtmpfs() {
    int err = lkl_sys_mount("tmpfs", "/dev/shm", "tmpfs", 0, "rw,nodev");
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mount(tmpfs) (/dev/shm): %s\n",
            lkl_strerror(err));
        //while(1);
    }
}

static void lkl_mount_tmpfs() {
    int err = lkl_sys_mount("tmpfs", "/tmp", "tmpfs", 0, "mode=0777");
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mount(tmpfs): %s\n",
            lkl_strerror(err));
        //while(1);
    }
}

static void lkl_mount_mntfs() {
    int err = lkl_sys_mount("tmpfs", "/mnt", "tmpfs", 0, "mode=0777");
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mount(tmpfs): %s\n",
            lkl_strerror(err));
        //while(1);
    }
}

static void lkl_mount_sysfs() {
    int err = lkl_sys_mount("none", "/sys", "sysfs", 0, NULL);
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mount(sysfs): %s\n",
            lkl_strerror(err));
        //while(1);
    }
}

static void lkl_mount_runfs() {
    int err = lkl_sys_mount("tmpfs", "/run", "tmpfs", 0, "mode=0700");
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mount(tmpfs): %s\n",
            lkl_strerror(err));
        //while(1);
    }
}

static void lkl_mount_procfs() {
    int err = lkl_sys_mount("proc", "/proc", "proc", 0, NULL);
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mount(procfs): %s\n",
            lkl_strerror(err));
        //while(1);
    }
}

static void lkl_mknods() {
    lkl_sys_unlink("/dev/null");
    int err = lkl_sys_mknod("/dev/null", LKL_S_IFCHR | 0666, LKL_MKDEV(1,3));
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mknod(/dev/null) %s\n",
            lkl_strerror(err));
        //while(1);
    }
    lkl_sys_unlink("/dev/zero");
    err = lkl_sys_mknod("/dev/zero", LKL_S_IFCHR | 0666, LKL_MKDEV(1,5));
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mknod(/dev/zero) %s\n",
                lkl_strerror(err));
        //while(1);
    }
    lkl_sys_unlink("/dev/random");
    err = lkl_sys_mknod("/dev/random", LKL_S_IFCHR | 0444, LKL_MKDEV(1,8));
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mknod(/dev/random) %s\n",
                lkl_strerror(err));
        //while(1);
    }
    lkl_sys_unlink("/dev/urandom");
    err = lkl_sys_mknod("/dev/urandom", LKL_S_IFCHR | 0444, LKL_MKDEV(1,9));
    if (err != 0) {
        lkl_printf( "Error: lkl_sys_mknod(/dev/urandom) %s\n",
                lkl_strerror(err));
        //while(1);
    }
}


static void lkl_prepare_rootfs(const char* dirname, int perm) {
    int err = lkl_sys_access(dirname, /*LKL_S_IRWXO*/ F_OK);
    if (err < 0) {
        if (err == -LKL_ENOENT)
            err = lkl_sys_mkdir(dirname, perm);
        if (err < 0) {
            lkl_printf("Error: Unable to mkdir %s: %s\n",
                dirname, lkl_strerror(err));
            //while(1);
        }
    }
}


static void lkl_mount_devtmpfs(const char* mntpoint) {
    int err = lkl_sys_mount("devtmpfs", (char*) mntpoint, "devtmpfs", 0, NULL);
    if (err != 0) {
        lkl_printf("Error: lkl_sys_mount(devtmpfs): %s\n",
            lkl_strerror(err));
	  //while(1);
    }
}


main() {
	long nread;
	char buf[BUF_SIZE];
	struct linux_dirent *d;
	char d_type;


	lkl_start_kernel(&lkl_host_ops, "init=/bin/bash");


    lkl_mount_devtmpfs("/dev");
    lkl_prepare_rootfs("/proc", 0700);
    lkl_mount_procfs();
    lkl_prepare_rootfs("/sys", 0700);
    lkl_mount_sysfs();
    lkl_prepare_rootfs("/run", 0700);
    lkl_mount_runfs();
    lkl_mknods();



	struct lkl_disk lkl_disk;
	lkl_disk.fd = open("./disk.img", O_RDWR);
	if(lkl_disk.fd < 0) {
		printf("cannot open disk\n"); while(1);
	}
	lkl_disk.ops = &lkl_dev_blk_ops;

	lkl_printf("ADD disk\n");
	int disk_id = lkl_disk_add((struct lkl_disk *)&lkl_disk);
	if(disk_id < 0) {
		lkl_printf("error = %s\n", lkl_strerror(disk_id));
		lkl_printf("disk id = %d\n", disk_id);
		//while(1);
	}
	lkl_printf("disk id = %d\n", disk_id);

	char *mpoint="/mnt/123/";

	int ret = lkl_mount_dev(disk_id, 1, "ext4", LKL_MS_RDONLY, NULL, mpoint, sizeof(mpoint));
	lkl_printf("lkl mount dev = %d:%s\n", ret, lkl_strerror(ret));

    int err = lkl_mount_blockdev("/dev/vda", mpoint, "ext4",  0, NULL);
    if (err < 0)
        lkl_printf("Error: lkl_mount_blockdev()=%s (%d)\n", lkl_strerror(err), err);

	int fd = lkl_sys_open("/mnt/123/app/helloworld.txt", LKL_O_RDONLY, 0);
	if (fd < 0) {
			lkl_printf("cannot open %s\n", lkl_strerror(fd));
	}

	char hb[1024];
	lkl_sys_read(fd, hb, 1024);
	lkl_printf("readed %s\n", hb);

}
