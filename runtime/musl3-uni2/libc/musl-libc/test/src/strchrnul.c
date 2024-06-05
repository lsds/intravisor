#define _GNU_SOURCE

#include <string.h>

int do_strchrnul_test(char* src, char c, char* exp) {
  void*res = strchrnul(src, c);
  if (exp[0] != '\0') {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(src)) return 2;
    if (strcmp(res, exp)) return 3;
  } else {
    if (__builtin_cheri_tag_get(res) != 1) return 4;
    if (*(char*)res != '\0') return 5;
  }
  return 0;
}

int main(int argc, char** argv) {
  char* str = "far and few are the lands where the jumblies live";
  switch (argv[1][0]) {
  case '0': return do_strchrnul_test(str, 'j', "jumblies live");
  case '1': return do_strchrnul_test(str, 'x', "");
  default: return 1;
  }
}
