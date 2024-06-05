#define _GNU_SOURCE

#include <string.h>

int do_strcasestr_test(const char *h, const char *n, char *expected, size_t expected_offset) {
  char* res = strcasestr(h, n);

  if (expected) {
    if (__builtin_cheri_tag_get(res) != 1) return 1;
    if (__builtin_cheri_length_get(res) != __builtin_cheri_length_get(h)) return 2;
    if (res - h != expected_offset) return 3;
    if (strcmp(res, expected)) return 4;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 1;
    if (res) return 2;
  }

  return 0;
}

int main(int argc, char** argv) {
  switch(argv[1][0]) {
  case '0': return do_strcasestr_test("whereISit?", "is", "ISit?", 5);
  case '1': return do_strcasestr_test("whereISit?", "nowhere", 0, -1);
  case '2': return do_strcasestr_test("", "nowhere", 0, -1);
  default: return 1;
  }
}
