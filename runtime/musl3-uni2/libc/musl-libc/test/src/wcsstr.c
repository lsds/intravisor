#include <wchar.h>

int replace_first(wchar_t *str, wchar_t *subs, wchar_t *repl) {
  wchar_t *dst = wcsstr(str, subs);
  if (__builtin_cheri_tag_get(dst) != 1) return 1;
  if (__builtin_cheri_length_get(dst) != __builtin_cheri_length_get(str)) return 2;
  if (wcsncmp(dst, subs, wcslen(subs))) return 3;
  wmemcpy(dst, repl, wcslen(repl));
  return 0;
}

int main() {

  wchar_t str[] = L"on the ning nang nong all the cows go bong!";

  wchar_t *replacements[] = {L"nong", L"nang",
                             L"nang", L"ning",
                             L"ning", L"nong",
                             L"cows", L"mice",
                             L"bong", L"clang"};
  for (int i = 0; i < 10; i += 2) {
    int res = replace_first(str, replacements[i], replacements[i + 1]);
    if (res != 0) return res;
  }

  if (__builtin_cheri_tag_get(str) != 1) return 4;
  if (__builtin_cheri_length_get(str) != (wcslen(str) + 1) * sizeof(wchar_t)) return 5;
  if (wcscmp(str, L"on the nong ning nang all the mice go clang")) return 6;

  return 0;
}
