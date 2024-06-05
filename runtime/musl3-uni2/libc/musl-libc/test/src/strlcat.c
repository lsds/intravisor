#include <string.h>

int do_strlcat_test(char *d, const char *s, size_t n, const char *exp_str, size_t exp_n) {
  size_t ret = strlcat(d, s, n);
  if (ret != exp_n) return 1;
  if (strcmp(d, exp_str)) return 2;
  if (__builtin_cheri_tag_get(d) != 1) return 3;
  return 0;
}

int main(int argc, char **argv) {
  char str[50];
  strcpy(str, "can we ");
  switch (argv[1][0]) {
  case '0':
    return do_strlcat_test(str, "copy a string shorter than n? yes!", 100,
                           "can we copy a string shorter than n? yes!", 41);
  case '1':
    return do_strlcat_test(str, "copy a string longer than n? no we can't", 39,
                           "can we copy a string longer than n? no", 47);
  default: return 1;
  }
}
