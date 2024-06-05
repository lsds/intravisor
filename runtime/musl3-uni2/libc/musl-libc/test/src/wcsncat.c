#include <wchar.h>

int main() {
  wchar_t* words[] = {L"the ", L"boy ", L"stood ", L"on ", L"the ", L"burning ", L"deck"};
  size_t lengths[] = {1, 7, 6, 2, 0, 1, 4};
  wchar_t str[34];
  wmemset(str, L'\0', sizeof(str)/sizeof(wchar_t));

  wchar_t* dest = str;
  for (int i = 0; i < 7; i++) wcsncat(dest, words[i], lengths[i]);

  if (__builtin_cheri_tag_get(dest) != 1) return 1;
  if (__builtin_cheri_length_get(dest) != sizeof(str)) return 2;
  if (wcscmp(str, L"tboy stood onbdeck")) return 3;

  return 0;
}
