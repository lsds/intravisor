#include <string.h>

int main() {

  char* words[] = {"i ", "wandered ", "lonely ", "as ", "a ", "cloud"};
  size_t lengths[] = {3, 7, 13, 4, 4, 0};
  size_t exp_ret[] = {2, 9, 7, 3, 2, 5};
  char str[29];
  memset(str, 0, sizeof(str));

  char* dst = str;
  for (int i = 0; i < 6; i++) {
    size_t ret = strlcpy(dst + strlen(dst), words[i], lengths[i]);
    if (ret != exp_ret[i]) return 1;
  }

  if (__builtin_cheri_tag_get(str) != 1) return 2;
  if (__builtin_cheri_length_get(str) != sizeof(str)) return 3;
  if (strcmp(str, "i wanderlonely as a ")) return 4;

  return 0;
}
