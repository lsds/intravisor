#include <wchar.h>

int do_wmemmove_test(void *dest, void *src, size_t n, void *expected,
                    size_t expected_length) {
  void *res = wmemmove(dest, src, n);
  if (__builtin_cheri_tag_get(res) != 1) return 1;
  if (__builtin_cheri_length_get(res) != expected_length) return 2;
  if (wcscmp(res, expected)) return 3;
  if (!__builtin_cheri_subset_test(res, dest)) return 4;
  return 0;
}

int main(int argc, char **argv) {
  wchar_t src[26];
  wmemset(src, 0, 26);
  wcscpy(src + 5, L"lisdoonvarna");
  switch (argv[1][0]) {
  case '0':
    return do_wmemmove_test(src, src + 5, 12, L"lisdoonvarnavarna", sizeof(src));
  case '1':
    return do_wmemmove_test(src + 12, src + 5, 12, L"lisdoonvarna", sizeof(src));
  default:
    return 1;
  }
}
