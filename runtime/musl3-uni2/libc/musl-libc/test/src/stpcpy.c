#include <string.h>

int main() {

  char* words[] = {"i ", "wandered ", "lonely ", "as ", "a ", "cloud"};
  char str[29];
  memset(str, 0, sizeof(str));

  char* dst = str;
  for (int i = 0; i < 6; i++) dst = stpcpy(dst, words[i]);

  if (__builtin_cheri_tag_get(dst) != 1) return 1;
  if (__builtin_cheri_length_get(dst) != sizeof(str)) return 2;
  if (strcmp(str, "i wandered lonely as a cloud")) return 3;

  return 0;
}
