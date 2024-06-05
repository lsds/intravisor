#include <time.h>
#include <signal.h>

int main() {
  timer_t t;
  struct itimerspec it = {
    .it_interval = { 10, 0},
    .it_value = {10, 0}
  };
  struct itimerspec it_ret;
  struct sigevent sig = {
    .sigev_notify=SIGEV_NONE,
    .sigev_signo=SIGRTMIN,
    .sigev_value.sival_ptr = &t
  };

  if (timer_create(CLOCK_REALTIME, &sig, &t) != 0) return 1;
  if (timer_settime(t, 0, &it, &it_ret) != 0) return 2;

  // Get timer interval and check this matches set value
  if (timer_gettime(t, &it_ret) != 0) return 3;
  if (it_ret.it_interval.tv_sec != 10) return 4;

  if (timer_getoverrun(t) == -1) return 5;
  if (timer_delete(t) != 0) return 6;
  return 0;
}
