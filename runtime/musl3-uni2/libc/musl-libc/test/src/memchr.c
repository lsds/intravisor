#include <string.h>

int do_memchr_test(char* src, char c, size_t n, char* exp) {
  void*res = memchr(src, c, n);
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
  char* str = "twas brillig and the slithy toves";
  switch (argv[1][0]) {
  case '0': return do_memchr_test(str, 'b', 35, "brillig and the slithy toves");
  case '1': return do_memchr_test(str, 'm', 34, 0);
  case '2': return do_memchr_test(str, 'v', 15, 0);
  default: return 1;
  }
}
