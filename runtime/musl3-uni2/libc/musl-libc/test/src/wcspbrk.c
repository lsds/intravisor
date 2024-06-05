#include <wchar.h>

int do_wcspbrk_test(const wchar_t *s, const wchar_t *c, wchar_t *exp) {
  wchar_t* res = wcspbrk(s, c);
  if (exp) {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(s)) return 2;
    if (wcscmp(res, exp)) return 3;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 4;
    if (res) return 5;
  }
  return 0;
}

int main(int argc, char **argv) {
  switch (argv[1][0]) {
  case '0': return do_wcspbrk_test(L"", L"won't find any of these", 0);
  case '1': return do_wcspbrk_test(L"blink 182", L"0123456789", L"182");
  default: return 1;
  }
}
