#include <errno.h>
#include <string.h>

int main() {
  char *str = strerror(EAFNOSUPPORT);
  if (strcmp(str, "Address family not supported by protocol")) {
    return 1;
  }
  if (__builtin_cheri_tag_get(str) != 1) {
    return 2;
  }
  size_t len = __builtin_cheri_length_get(str);
  if (len != strlen(str) + 1) {
    return len ? len : 3;
  }
  return 0;
}
