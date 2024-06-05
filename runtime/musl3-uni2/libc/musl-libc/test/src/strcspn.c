#include <string.h>

int do_strcspn_test(const char *s, const char *c, size_t exp) {
  if (strcspn(s, c) != exp) return 1;
  return 0;
}

int main(int argc, char **argv) {
  switch (argv[1][0]) {
  case '0': return do_strcspn_test("", "won't find any of these", 0);
  case '1': return do_strcspn_test("blink 182", "0123456789", 6);
  case '2': return do_strcspn_test("no numbers here!", "0123456789", 16);
  default: return 1;
  }
}
