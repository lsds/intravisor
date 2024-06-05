#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
  time_t t;
  time(&t);
  struct tm *lt = localtime(&t);
  char* at = asctime(lt);
  printf("%s", at);
  printf("%lu\n", __builtin_cheri_length_get(at));
  return 0;
}
