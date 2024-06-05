#include <time.h>


int main() {
  struct timespec ts_cpuclk;
  clockid_t clk_cpu;
  if (clock_getcpuclockid(0, &clk_cpu) != 0) return 1;
  // Check clk_cpu is valid
  if (clock_gettime(clk_cpu, &ts_cpuclk) != 0) return 2;
  return 0;
}
