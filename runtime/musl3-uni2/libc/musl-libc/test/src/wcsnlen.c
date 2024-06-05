#include <wchar.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

int main(int argc, char **argv) {

  switch(argv[1][0]) {

  case '0':
    {
      wchar_t *a = L"hello";
      if (wcsnlen(a, 20) != 5) return 1;
      if (wcsnlen(a, 3) != 3) return 2;
      return 0;
    }
  case '1':
    {
      wchar_t *b = L"";
      if (wcsnlen(b, 10) != 0) return 1;
      return 0;
    }
  case '2':
    for (int i = 1; i < 17; i++) {
      wchar_t c[i];
      wmemset(c, L'j', i - 1);
      c[i - 1] = 0;
      if (wcsnlen(c, 10) != MIN(10, i - 1)) return 1;
    }
    return 0;

  default:
    return 1;
  }
}
