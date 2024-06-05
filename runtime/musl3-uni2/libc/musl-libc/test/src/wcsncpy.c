#include <wchar.h>

int main() {
  wchar_t *words[] = {L"where", L"daffodil", L"and", L"lily", L"wave"};
  size_t ns[] = {1, 4, 2, 4, 4};

  wchar_t *exp = L"wdaffanlilywave";

  wchar_t str[wcslen(exp) + 1];
  wmemset(str, 0, sizeof(str)/sizeof(wchar_t));
  for (int i = 0; i < 5; i++) {
    wchar_t* dst = str + wcslen(str);
    if (wcsncpy(dst, words[i], ns[i]) != dst)
      return 1;
  }

  if (__builtin_cheri_tag_get(str) != 1) return 2;
  if (__builtin_cheri_length_get(str) != sizeof(str)) return 3;
  if (wcscmp(str, exp)) return 4;

  return 0;
}
