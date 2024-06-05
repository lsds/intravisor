#include <string.h>

int main() {

  const char* words[] = {
    "i ",
    "wandered ",
    "lonely ",
    "as ",
    "a ",
    "cloud",
    "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium"
  };
  char str[80];
  memset(str, 0, sizeof(str));

  char* dst = str;
  for (int i = 0; i < 7; i++) {
    dst = strcpy(dst, words[i]);
    if (__builtin_cheri_tag_get(dst) != 1) return 1;
    if (__builtin_cheri_length_get(dst) != sizeof(str)) return 2;
    if (strcmp(dst, words[i])) return 3;
  }

  return 0;
}
