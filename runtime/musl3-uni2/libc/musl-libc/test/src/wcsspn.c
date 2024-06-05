#include <wchar.h>

int do_wcsspn_test(const wchar_t *s, const wchar_t *c, size_t exp) {
  if (wcsspn(s, c) != exp) return 1;
  return 0;
}

int main(int argc, char **argv) {
  switch (argv[1][0]) {
  case '0': return do_wcsspn_test(L"", L"won't find any of these", 0);
  case '1': return do_wcsspn_test(L"blink 182", L"abcdefghijklmn", 5);
  case '2': return do_wcsspn_test(L"no numbers here!", L"0123456789", 0);
  default: return 1;
  }
}
