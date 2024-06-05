#include <string.h>

int main() {
  if (strncasecmp("isithere?", "NO", 2) == 0) return 1;
  if (strncasecmp("blahBLAHblah", "BLAHblahBLAH", 12) != 0) return 2;
  if (strncasecmp("what about if n is too small?", "What ABOUT it?", 11) != 0) return 3;
  return 0;
}
