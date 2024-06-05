#include <string.h>

int main() {
  if (strcasecmp("isithere?", "NO") == 0) return 1;
  if (strcasecmp("blahBLAHblah", "BLAHblahBLAH") != 0) return 2;
}
