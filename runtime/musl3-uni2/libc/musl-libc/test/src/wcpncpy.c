#include <wchar.h>

int main() {
  wchar_t *words[] = {L"where", L"daffodil", L"and", L"lily", L"wave"};
  size_t ns[] = {1, 4, 2, 4, 4};

  wchar_t *exp = L"wdaffanlilywave";

  wchar_t str[wcslen(exp) + 1];
  wmemset(str, L'\0', sizeof(str)/sizeof(wchar_t));
  wchar_t* dst = str;
  for (int i = 0; i < 5; i++) {
    dst = wcpncpy(dst, words[i], ns[i]);
    for (int j = (dst - str) + ns[i]; j < wcslen(exp) + 1; j++) {
      if (str[j] != L'\0') return 1;
    }
  }

  if (__builtin_cheri_tag_get(dst) != 1) return 2;
  if (__builtin_cheri_length_get(dst) != (wcslen(exp) + 1) * sizeof(wchar_t)) return 3;
  if (wcscmp(str, exp)) return 4;

  return 0;
}
