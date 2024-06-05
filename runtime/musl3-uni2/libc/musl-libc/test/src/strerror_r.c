#include <errno.h>
#include <string.h>

int main() {
  errno = ENOSTR;
  char s[15];
  int d = strerror_r(errno, s, 15);
  if (strcmp(strerror(d), "Result not representable")) {
    return 1;
  }
  if (strcmp(s, "Device not a s")) {
    return 2;
  }
  if (__builtin_cheri_tag_get(s) != 1) {
    return 3;
  }
  return 0;
}
