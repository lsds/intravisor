#define _GNU_SOURCE
#include <string.h>

int main() {
  char str[] = "i wandered lonely as a cloud";
  size_t untokenised_len = strlen(str);
  char* words[] = {"i", "wandered", "lonely", "as", "a", "cloud"};

  char* tmp = str;
  char* tok;
  int i = 0;

  while ((tok = strsep(&tmp, " "))) {
    if (__builtin_cheri_tag_get(tok) != 1) return 1;
    if (__builtin_cheri_length_get(tok) != untokenised_len + 1) return 2;
    if (strcmp(words[i++], tok)) return 3;
  }
  return 0;
}
