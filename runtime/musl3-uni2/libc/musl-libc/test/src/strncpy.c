#include <string.h>

int main() {
  char *words[] = {"where", "daffodil", "and", "lily", "wave"};
  size_t ns[] = {1, 4, 2, 4, 4};

  char *exp = "wdaffanlilywave";

  char str[strlen(exp) + 1];
  memset(str, 0, sizeof(str));
  for (int i = 0; i < 5; i++) {
    char* dst = str + strlen(str);
    if (strncpy(dst, words[i], ns[i]) != dst)
      return 1;
  }

  if (__builtin_cheri_tag_get(str) != 1) return 2;
  if (__builtin_cheri_length_get(str) != sizeof(str)) return 3;
  if (strcmp(str, exp)) return 4;

  return 0;
}
