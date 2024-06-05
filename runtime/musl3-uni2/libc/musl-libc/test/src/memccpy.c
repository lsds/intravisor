#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "cheri_test_helpers.h"

int do_memccpy_test(char *buf, char *src, char c, size_t n, char *expected_buf,
                    bool expected_res_tag, size_t bytes_left) {
  size_t buf_length = __builtin_cheri_length_get(buf);
  char *res = memccpy(buf, src, c, n);

  if (__builtin_cheri_tag_get(buf) != 1) return 1;
  if (__builtin_cheri_length_get(buf) != buf_length) return 2;
  if (strcmp(buf, expected_buf)) return 3;

  if (expected_res_tag) {
    if (__builtin_cheri_tag_get(res) != 1) return 4;
    if (CAP_TAIL_LENGTH(res) != bytes_left) return 5;
    if (*(res - 1) != c) return 6;
  } else {
    if (__builtin_cheri_tag_get(res) != 0) return 7;
  }

  return 0;
}

int main(int argc, char **argv) {
  char *src = "Copy up to here: don't copy this bit";
  char buf[40];
  memset(buf, 0, 40);

  switch (argv[1][0]) {
  case '0':
    return do_memccpy_test(buf, src, ':', 40, "Copy up to here:", true, 24);
  case '1':
    return do_memccpy_test(buf, src, ':', 4, "Copy", false, 0);
  case '2':
    return do_memccpy_test(buf, src, 0, 40, "Copy up to here: don't copy this bit", true, 3);
  default:
    return 1;
  }
}
