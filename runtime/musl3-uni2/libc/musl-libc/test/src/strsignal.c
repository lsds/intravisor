#include <string.h>
#include <signal.h>

int main() {
  char *res = strsignal(SIGILL);
  char exp[] = "Illegal instruction";
  if (__builtin_cheri_tag_get(res) != 1) return 1;
  if (__builtin_cheri_length_get(res) != strlen(exp) + 1) return 2;
  if (strcmp(res, exp)) return 3;
  return 0;
}
