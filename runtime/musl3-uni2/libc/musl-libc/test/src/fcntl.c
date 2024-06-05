#define _GNU_SOURCE

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "temp_file_helpers.h"

char DIR_PATH[PATH_MAX];

int create_tmp_file() {
  char template[PATH_MAX];
  strcpy(template, DIR_PATH);
  strcat(template, "/testXXXXXX");
  return mkstemp(template);
}

int test_fcntl_flock() {
  int fd = create_tmp_file();
  if (fd < 0) {
    return 1;
  }

  const struct flock fl_set = {
    .l_type = F_WRLCK,
    .l_whence = SEEK_SET, // start of file
    .l_start = 0,
    .l_len = 0,
    .l_pid = 0
  };

  int ret = fcntl(fd, F_SETLK, &fl_set);
  if (ret != 0) {
    return 3;
  }

  struct flock fl_get = {
    .l_type = F_RDLCK,
    .l_whence = SEEK_SET,
    .l_start = 0,
    .l_len = 0,
    .l_pid = 0
  };

  ret = fcntl(fd, F_GETLK, &fl_get);
  if (fl_get.l_type != F_UNLCK || ret != 0) {
    return 4;
  }

  if (close(fd)) {
    return 2;
  }

  return 0;
}

int test_fcntl_fd() {
  int fd = create_tmp_file();
  if (fd < 0) {
    return 1;
  }

  int fd_flags = fcntl(fd, F_GETFD);
  if (fd_flags != 0) {
    return 5;
  }

  int err = fcntl(fd, F_SETFD, FD_CLOEXEC);
  if (err != 0) {
    return 6;
  }

  fd_flags = fcntl(fd, F_GETFD);
  if (fd_flags != FD_CLOEXEC) {
    return 7;
  }

  if (close(fd)) {
    return 2;
  }

  return 0;
}

int test_fcntl_fl() {
  int fd = create_tmp_file();
  if (fd < 0) {
    return 1;
  }

  int status_flags = fcntl(fd, F_GETFL);
  if (status_flags & O_NOATIME) {
    return 8;
  }

  int ret = fcntl(fd, F_SETFL, status_flags | O_NOATIME);
  if (ret != 0) {
    return 9;
  }

  status_flags = fcntl(fd, F_GETFL);
  if (!(status_flags & O_NOATIME)) {
    return 10;
  }

  if (close(fd)) {
    return 2;
  }

  return 0;
}

int test_fcntl_own() {
  struct f_owner_ex owner;

  int fd = create_tmp_file();
  if (fd < 0) {
    fprintf(stderr, "Failed to create temporary file.\n");
    return 1;
  }

  int ret = fcntl(fd, F_GETOWN_EX, &owner);
  if (ret != 0) {
    fprintf(stderr, "Failed to get file descriptor owner.\n");
    return 2;
  }

  if (close(fd)) {
    fprintf(stderr, "Failed to close file descriptor.\n");
    return 3;
  }

  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) return -1;

  if (create_temp_directory("morello-musl-tests-fcntl/", DIR_PATH) != 0)
    return -1;

  switch (argv[1][0]) {
    case '0': // fcntl_flck
      return test_fcntl_flock();
    case '1': // fcntl_fd
      return test_fcntl_fd();
    case '2': // fcntl_fl
      return test_fcntl_fl();
    case '3': // fcntl_own
      return test_fcntl_own();
  }

  return -1;
}
