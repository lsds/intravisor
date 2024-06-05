#include <wchar.h>

int do_wcscspn_test(const wchar_t *s, const wchar_t *c, size_t exp) {
  if (wcscspn(s, c) != exp) return 1;
  return 0;
}

int main(int argc, char **argv) {
  switch (argv[1][0]) {
  case '0': return do_wcscspn_test(L"", L"won't find any of these", 0);
  case '1': return do_wcscspn_test(L"blink 182", L"0123456789", 6);
  case '2': return do_wcscspn_test(L"no numbers here!", L"0123456789", 16);
  default: return 1;
  }
}
