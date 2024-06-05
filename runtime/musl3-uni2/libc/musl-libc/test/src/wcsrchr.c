#define _GNU_SOURCE

#include <wchar.h>

int do_wcsrchr_test(wchar_t* src, wchar_t c, wchar_t* exp) {
  void*res = wcsrchr(src, c);
  if (exp) {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(src)) return 2;
    if (wcscmp(res, exp)) return 3;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 4;
    if (res != NULL) return 5;
  }
  return 0;
}

int main(int argc, char** argv) {
  wchar_t* str = L"twas brillig and the slithy toves";
  switch (argv[1][0]) {
  case '0': return do_wcsrchr_test(str, L't', L"toves");
  case '1': return do_wcsrchr_test(str, L'm', 0);
  default: return 1;
  }
}
