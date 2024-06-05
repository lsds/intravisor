#include <string.h>

int do_memmove_test(void *dest, void *src, size_t n, void *expected,
                    size_t expected_length) {
  void *res = memmove(dest, src, n);
  if (__builtin_cheri_tag_get(res) != 1) return 1;
  if (__builtin_cheri_length_get(res) != expected_length) return 2;
  if (strcmp(res, expected)) return 3;
  if (!__builtin_cheri_subset_test(res, dest)) return 4;
  return 0;
}

int main(int argc, char **argv) {
  char src[26];
  memset(src, 0, 26);
  strcpy(src + 5, "lisdoonvarna");
  switch (argv[1][0]) {
  case '0':
    return do_memmove_test(src, src + 5, 12, "lisdoonvarnavarna", 26);
  case '1':
    return do_memmove_test(src + 12, src + 5, 12, "lisdoonvarna", 26);
  default:
    return 1;
  }
}
