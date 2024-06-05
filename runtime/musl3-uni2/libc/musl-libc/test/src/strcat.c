#include <string.h>

int main() {
  char* words[] = {"the ", "boy ", "stood ", "on ", "the ", "burning ", "deck"};
  char str[34];
  memset(str, 0, sizeof(str));

  char* dest = str;
  for (int i = 0; i < 7; i++) strcat(dest, words[i]);

  if (__builtin_cheri_tag_get(dest) != 1) return 1;
  if (__builtin_cheri_length_get(dest) != sizeof(str)) return 2;
  if (strcmp(str, "the boy stood on the burning deck")) return 3;

  return 0;
}
