#include <string.h>

int main() {
  if (strcmp("should match", "should match")) return 1;
  if (strcmp("should be greater", "") <= 0) return 2;
  if (strcmp("", "should be less") >= 0) return 3;
  if (strcmp("", "")) return 4;
  if (strcmp("should be", "slightly less") >= 0) return 5;
  if (strcmp("this should be greater", "than this") <= 0) return 6;
  return 0;
}
