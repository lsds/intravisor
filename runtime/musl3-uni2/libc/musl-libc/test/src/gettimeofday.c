#include <sys/time.h>

int main() {
  struct timeval time;
  int ret = gettimeofday(&time, 0);
  // We can't really check for the 'correct' value of time, but we can at least
  // check the return value, which is -1 for failure and 0 for success
  if (ret != 0) return 1;
  return 0;
}
