#include <string.h>

int do_strchr_test(char* src, char c, char* exp) {
  void*res = strchr(src, c);
  if (exp) {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(src)) return 2;
    if (strcmp(res, exp)) return 3;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 4;
    if (res) return 5;
  }
  return 0;
}

int main(int argc, char** argv) {
  char* str = "on the ning nang nong all the cows go bong";
  switch (argv[1][0]) {
  case '0': return do_strchr_test(str, 'c', "cows go bong");
  case '1': return do_strchr_test(str, 'x', 0);
  default: return 1;
  }
}
