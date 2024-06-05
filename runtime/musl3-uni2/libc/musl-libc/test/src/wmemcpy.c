#include <wchar.h>

int main() {
  wchar_t src[] = L"copy this";
  wchar_t dst[sizeof(src)/sizeof(wchar_t)];
  wmemcpy(dst, src, wcslen(src) + 1);
  if (__builtin_cheri_tag_get(dst) != 1) return 1;
  if (__builtin_cheri_length_get(dst) != sizeof(src)) return 2;
  if (wcscmp(src, dst)) return 3;
  return 0;
}
