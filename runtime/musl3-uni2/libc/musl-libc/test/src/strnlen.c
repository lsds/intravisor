#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

int main(int argc, char **argv) {

  switch(argv[1][0]) {

  case '0':
    {
      char *a = "hello";
      if (strnlen(a, 20) != 5) return 1;
      if (strnlen(a, 3) != 3) return 2;
      return 0;
    }
  case '1':
    {
      char *b = "";
      if (strnlen(b, 10) != 0) return 1;
      return 0;
    }
  case '2':
    for (int i = 1; i < 17; i++) {
      char c[i];
      memset(c, 'j', i - 1);
      c[i - 1] = 0;
      if (strnlen(c, 10) != MIN(10, i - 1)) return 1;
    }
    return 0;

  default:
    return 1;
  }
}
