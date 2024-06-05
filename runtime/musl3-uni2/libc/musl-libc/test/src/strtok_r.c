#include <string.h>

int main() {
  char str[] = "i wandered   lonely  as a ? cloud";
  size_t untokenised_len = strlen(str) + 1;
  char *words[] = {"i", "wandered", "lonely", "as", "a", "cloud"};
  char *buf;
  int i = 0;

  char *tok = strtok_r(str, " ?", &buf);

  do {
    if (__builtin_cheri_tag_get(tok) != 1) return 1;
    if (__builtin_cheri_length_get(tok) != untokenised_len) return 2;
    if (strcmp(words[i++], tok)) return 3;
  } while ((tok = strtok_r(0, " ? ", &buf)));

  if (__builtin_cheri_tag_get(tok) != 0) return 4;
  if (tok != NULL) return 5;

  return 0;
}
