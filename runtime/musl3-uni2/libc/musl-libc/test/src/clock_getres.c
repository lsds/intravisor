#include <time.h>

int main() {
  struct timespec spec;
  int ret = clock_getres(CLOCK_REALTIME, &spec);
  // We can't really check for the 'correct' value of res, but we can at least
  // check the return value, which is -1 for failure and 0 for success
  if (ret != 0) return 1;
  return 0;
}
