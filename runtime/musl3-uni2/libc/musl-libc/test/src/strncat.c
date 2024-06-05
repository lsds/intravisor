#include <string.h>

int main() {
  char* words[] = {"the ", "boy ", "stood ", "on ", "the ", "burning ", "deck"};
  size_t lengths[] = {1, 7, 6, 2, 0, 1, 4};
  char str[34];
  memset(str, 0, sizeof(str));

  char* dest = str;
  for (int i = 0; i < 7; i++) strncat(dest, words[i], lengths[i]);

  if (__builtin_cheri_tag_get(dest) != 1) return 1;
  if (__builtin_cheri_length_get(dest) != sizeof(str)) return 2;
  if (strcmp(str, "tboy stood onbdeck")) return 3;

  return 0;
}
