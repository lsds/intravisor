#define _GNU_SOURCE

#include <sys/statvfs.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "temp_file_helpers.h"

char DIR_PATH[PATH_MAX];

int test_stat();
int test_mkfifo();
int test_umask();
int test_utimensat_futimensat();
int test_chmod();
int test_statvfs();

mode_t mode = 0666;

int main(int argc, char **argv) {
  if (argc < 2) return -1;

  if (create_temp_directory("morello-musl-tests-stat/", DIR_PATH) != 0)
    return -1;

  switch (argv[1][0]) {
  case '0':
      return test_stat();
  case '1':
      return test_mkfifo();
  case '2':
      return test_umask();
  case '3':
      return test_utimensat_futimensat();
  case '4':
      return test_chmod();
  case '5':
      return test_statvfs();
  }

  return -1;
}

// stat() simply calls fstatat(), so this test pretty much covers fstat(),
// lstat(), and fstatat() too.
int test_stat() {
  struct stat statbuf = { 0 };

  char filename[PATH_MAX];
  strcpy(filename, DIR_PATH);
  strcat(filename, "/statXXXXXX");

  int fd;
  if ((fd = mkstemp(filename)) < 0) return 1;
  if (write(fd, "AAA", 3) != 3) return 2;

  // test stat()
  if (stat(filename, &statbuf)) return 3;
  if (statbuf.st_uid != geteuid()) return 4;
  if (statbuf.st_gid != getegid()) return 5;
  if (statbuf.st_size != 3) return 6;

  if(unlink(filename)) return 7;
  if(close(fd)) return 8;

  return 0;
}

// internally calls mknod()/mknodat(), so this provides some coverage of that.
int test_mkfifo() {
  char filename_buffer[PATH_MAX];
  char *filename = create_temp_file(DIR_PATH, "/statXXXXXX", &filename_buffer[0]);

  if (mkfifo(filename, mode)) return 1;
  if (remove(filename)) return 2;

  if (mkfifoat(0, filename, mode)) return 3;
  if (remove(filename)) return 4;

  return 0;
}

int test_umask() {
  mode_t um = umask(mode);
  umask(um);
  mode_t um2 = umask(mode);

  if (um != um2) return 1;

  return 0;
}

int test_utimensat_futimensat() {
  struct stat statbuf = { 0 };
  char filename[PATH_MAX];
  strcpy(filename, DIR_PATH);
  strcat(filename, "/statXXXXXX");

  int fd;
  if ((fd = mkstemp(filename)) < 0) return 1;

  const struct timespec timespec1[2] = {
    {
      .tv_sec = 100,
      .tv_nsec = 10
    },
    {
      .tv_sec = 200,
      .tv_nsec = 20
    }
  };
  if (utimensat(0, filename, timespec1, 0)) return 2;

  if (stat(filename, &statbuf)) return 3;
  if (statbuf.st_atim.tv_sec != timespec1[0].tv_sec ||
      statbuf.st_atim.tv_nsec != timespec1[0].tv_nsec) return 4;
  if (statbuf.st_mtim.tv_sec != timespec1[1].tv_sec ||
      statbuf.st_mtim.tv_nsec != timespec1[1].tv_nsec) return 5;

  const struct timespec timespec2[2] = {
    {
      .tv_sec = 300,
      .tv_nsec = 30
    },
    {
      .tv_sec = 400,
      .tv_nsec = 40
    }
  };
  if (futimens(fd, timespec2)) return 6;

  if (stat(filename, &statbuf)) return 7;
  if (statbuf.st_atim.tv_sec != timespec2[0].tv_sec ||
      statbuf.st_atim.tv_nsec != timespec2[0].tv_nsec) return 8;
  if (statbuf.st_mtim.tv_sec != timespec2[1].tv_sec ||
      statbuf.st_mtim.tv_nsec != timespec2[1].tv_nsec) return 9;

  if (unlink(filename)) return 10;
  if (close(fd)) return 11;

  return 0;
}

// lchmod() is not tested as it simply wraps fchmodat()
int test_chmod() {
  char filename[PATH_MAX];
  strcpy(filename, DIR_PATH);
  strcat(filename, "/statXXXXXX");

  int fd;
  if ((fd = mkstemp(filename)) < 0) return 1;

  if (chmod(filename, 0600)) return 2;
  if (fchmod(fd, 0600)) return 3;
  if (fchmodat(fd, filename, 0600, AT_SYMLINK_NOFOLLOW)) return 4;

  if (unlink(filename)) return 5;
  if (close(fd)) return 6;

  return 0;
}

int test_statvfs() {
  char filename[PATH_MAX];
  strcpy(filename, DIR_PATH);
  strcat(filename, "/statXXXXXX");
  struct statvfs statvfsbuf = { 0 };

  int fd;
  if ((fd = mkstemp(filename)) < 0) return 1;

  if (statvfs(filename, &statvfsbuf)) return 2;
  if (statvfsbuf.f_namemax == 0) return 3;

  if (unlink(filename)) return 4;
  if (close(fd)) return 5;

  return 0;
}
