#include <string.h>

int do_strpbrk_test(const char *s, const char *c, char *exp) {
  char* res = strpbrk(s, c);
  if (exp) {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(s)) return 2;
    if (strcmp(res, exp)) return 3;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 4;
    if (res) return 5;
  }
  return 0;
}

int main(int argc, char **argv) {
  switch (argv[1][0]) {
  case '0': return do_strpbrk_test("", "won't find any of these", 0);
  case '1': return do_strpbrk_test("blink 182", "0123456789", "182");
  default: return 1;
  }
}
