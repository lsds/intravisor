#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

int main() {
  char* val = secure_getenv("HELLO");
  printf("%s\n", val);
  printf("%lu\n", __builtin_cheri_length_get(val));
  return 0;
}
