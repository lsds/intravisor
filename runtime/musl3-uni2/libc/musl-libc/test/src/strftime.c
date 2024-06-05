#include <stdio.h>
#include <time.h>

int main() {
  size_t buf_size = 40;
  time_t rawtime;
  time(&rawtime);
  struct tm *t = localtime(&rawtime);
  char buf[buf_size];
  strftime(buf, buf_size, "%I:%M", t);
  printf("%s, 40\n", buf);
  return 0;
}
