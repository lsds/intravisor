
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <sys/select.h>
#include <time.h>

int test_poll();
int test_select();
int test_pselect();

int main(int argc, char **argv) {
  if (argc < 2) return -1;

  switch (argv[1][0]) {
    case '0':
      return test_poll();
    case '1':
      return test_select();
    case '2':
      return test_pselect();
  }

  return -1;
}

int test_poll() {
  struct pollfd fd = (struct pollfd) {
    .fd = STDOUT_FILENO,
    .events = POLLOUT
  };

  if (poll(&fd, 1, 1000) != 1) return 1;
  if (!(fd.revents & POLLOUT)) return 2;

  return 0;
}

int test_select() {
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  fd_set writefds;
  FD_ZERO(&writefds);
  FD_SET(STDOUT_FILENO, &writefds);

  struct timeval timeout = {
    .tv_sec = 5,
    .tv_usec = 0
  };

  if (select(1, &readfds, &writefds, NULL, &timeout) < 0) return 1;

  return 0;
}

int test_pselect() {
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(STDIN_FILENO, &readfds);

  fd_set writefds;
  FD_ZERO(&writefds);
  FD_SET(STDOUT_FILENO, &writefds);

  struct timespec timeout = {
    .tv_sec = 5,
    .tv_nsec = 0
  };

  if (pselect(1, &readfds, &writefds, NULL, &timeout, NULL) < 0) return 1;

  return 0;
}
