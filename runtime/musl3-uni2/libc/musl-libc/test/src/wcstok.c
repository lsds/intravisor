#include <wchar.h>

int main() {
  wchar_t str[] = L"i wandered   lonely  as a ? cloud";
  size_t untokenised_len = (wcslen(str) + 1) * sizeof(wchar_t);
  wchar_t *words[] = {L"i", L"wandered", L"lonely", L"as", L"a", L"cloud"};
  wchar_t *buf;
  int i = 0;

  wchar_t *tok = wcstok(str, L" ?", &buf);

  do {
    if (__builtin_cheri_tag_get(tok) != 1) return 1;
    if (__builtin_cheri_length_get(tok) != untokenised_len) return 2;
    if (wcscmp(words[i++], tok)) return 3;
  } while ((tok = wcstok(0, L" ? ", &buf)));

  if (__builtin_cheri_tag_get(tok) != 0) return 4;
  if (tok != NULL) return 5;

  return 0;
}
