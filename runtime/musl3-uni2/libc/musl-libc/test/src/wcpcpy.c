#include <wchar.h>

int main() {

  wchar_t* words[] = {L"i ", L"wandered ", L"lonely ", L"as ", L"a ", L"cloud"};
  wchar_t str[29];
  wmemset(str, L'\0', sizeof(str)/sizeof(wchar_t));

  wchar_t* dst = str;
  for (int i = 0; i < 6; i++) dst = wcpcpy(dst, words[i]);

  if (__builtin_cheri_tag_get(dst) != 1) return 1;
  if (__builtin_cheri_length_get(dst) != sizeof(str)) return 2;
  if (wcscmp(str, L"i wandered lonely as a cloud")) return 3;

  return 0;
}
