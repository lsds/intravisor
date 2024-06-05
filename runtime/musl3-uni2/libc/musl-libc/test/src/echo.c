#include <stdio.h>
#include <string.h>

int main(void) {
  char buf[20];
  fgets(buf, 20, stdin);
  printf("%s\n",buf);
  return 0;
}
