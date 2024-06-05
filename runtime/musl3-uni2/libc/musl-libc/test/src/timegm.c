#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime;
  time(&rawtime);
  struct tm *t = gmtime(&rawtime);
  time_t rettime = timegm(t);
  printf("%ld\n", rettime - rawtime);
  return 0;
}
