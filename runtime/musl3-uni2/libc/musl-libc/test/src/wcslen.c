#include <wchar.h>

int main(int argc, char **argv) {

  switch(argv[1][0]) {

  case '0':
    {
      wchar_t *a = L"hello";
      if (wcslen(a) != 5) return 1;
      if (wcslen(a + 2) != 3) return 2;
      return 0;
    }
  case '1':
    {
      wchar_t *b = L"";
      if (wcslen(b) != 0) return 1;
      return 0;
    }
  case '2':
    for (int i = 1; i < 17; i++) {
      wchar_t c[i];
      wmemset(c, L'j', i - 1);
      c[i - 1] = 0;
      if (wcslen(c) != i - 1) return 1;
      if (i > 3 && wcslen(c + 2) != i - 3) return 2;
    }
    return 0;

  default:
    return 1;
  }
}
