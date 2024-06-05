#include <wchar.h>

int do_wmemchr_test(wchar_t* src, wchar_t c, size_t n, wchar_t* exp) {
  void*res = wmemchr(src, c, n);
  if (exp) {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(src)) return 2;
    if (wcscmp(res, exp)) return 3;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 4;
    if (res) return 5;
  }
  return 0;
}

int main(int argc, char** argv) {
  wchar_t* str = L"twas brillig and the slithy toves";
  switch (argv[1][0]) {
  case '0': return do_wmemchr_test(str, L'b', 35, L"brillig and the slithy toves");
  case '1': return do_wmemchr_test(str, L'm', 34, 0);
  case '2': return do_wmemchr_test(str, L'v', 15, 0);
  default: return 1;
  }
}
