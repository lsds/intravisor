#include <time.h>


int main(int argc, char **argv) {
  int delay_ns = 50000000;
  struct timespec ts_delay = {0, delay_ns};
  struct timespec ts_ret1, ts_ret2;
  if (clock_gettime(CLOCK_REALTIME, &ts_ret1) != 0) return 1;

  switch(argv[1][0]) {

  case '0':
    {
      if (nanosleep(&ts_delay, NULL) != 0) return 2;
      break;
    }
  case '1':
    {
      if (clock_nanosleep(CLOCK_REALTIME, 0, &ts_delay, NULL) != 0) return 2;
      break;
    }
  default:
    return 1;
  }
  clock_gettime(CLOCK_REALTIME, &ts_ret2);
  // Check duration exceeded sleep time
  if (((ts_ret2.tv_nsec - ts_ret1.tv_nsec) < delay_ns) && (ts_ret2.tv_sec <= ts_ret1.tv_sec)) return 3;

  return 0;
}
