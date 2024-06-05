#include <langinfo.h>
#include <locale.h>
#include <stdio.h>

int main() {
  char* li = nl_langinfo(CODESET);
  printf("%s\n", li);
  printf("%lu\n", __builtin_cheri_length_get(li));

  li = nl_langinfo(D_FMT);
  printf("%s\n", li);
  printf("%lu\n", __builtin_cheri_length_get(li));
  return 0;
}
