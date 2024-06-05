#include <string.h>

int main() {
  if (strncmp("should match!", "should match, honest", 12)) return 1;
  if (strncmp("should be greater", "", 11) <= 0) return 2;
  if (strncmp("", "should be less", 5) >= 0) return 3;
  if (strncmp("", "", 1)) return 4;
  if (strncmp("should be", "slightly less", 2) >= 0) return 5;
  if (strncmp("this should be greater", "than this", 14) <= 0) return 6;
  return 0;
}
