#define _GNU_SOURCE

#include <string.h>

int main() {
  char str[21];
  strcpy(str, "overwrite up to here");
  char* res = mempcpy(str, "nothing to see  ", 16);

  if (__builtin_cheri_tag_get(res) != 1) return 1;
  if (__builtin_cheri_length_get(res) != strlen(str) + 1) return 2;
  if (strcmp(res, "here")) return 3;

  if (__builtin_cheri_tag_get(str) != 1) return 4;
  if (__builtin_cheri_length_get(str) != strlen(str) + 1) return 5;
  if (strcmp(str, "nothing to see  here")) return 6;

  return 0;
}
