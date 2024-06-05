#include <stdio.h>
#include <time.h>

int main() {
  time_t rawtime;
  time(&rawtime);
  struct tm *t = gmtime(&rawtime);
  printf("%ld\n", sizeof(*t) - __builtin_cheri_length_get(t));
  return 0;
}
