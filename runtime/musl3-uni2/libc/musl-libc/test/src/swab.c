#include <unistd.h>
#include <string.h>

int main() {
  char src[] = "abcdefghi";
  char dst[sizeof(src)];
  memset(dst, 0, sizeof(dst));
  swab(src, dst, sizeof(src));
  if (strncmp(dst, "badcfehg", 8)) return 1;
  return 0;
}
