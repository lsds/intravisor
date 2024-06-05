#include <string.h>

int main(int argc, char **argv) {

  switch(argv[1][0]) {

  case '0':
    {
      char *a = "hello";
      if (strlen(a) != 5) return 1;
      if (strlen(a + 2) != 3) return 2;
      return 0;
    }
  case '1':
    {
      char *b = "";
      if (strlen(b) != 0) return 1;
      return 0;
    }
  case '2':
    for (int i = 1; i < 17; i++) {
      char c[i];
      memset(c, 'j', i - 1);
      c[i - 1] = 0;
      if (strlen(c) != i - 1) return 1;
      if (i > 3 && strlen(c + 2) != i - 3) return 2;
    }
    return 0;

  default:
    return 1;
  }
}
