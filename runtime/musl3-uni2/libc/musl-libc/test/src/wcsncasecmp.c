#include <wchar.h>

int main() {
  if (wcsncasecmp(L"isithere?", L"NO", 2) == 0) return 1;
  if (wcsncasecmp(L"blahBLAHblah", L"BLAHblahBLAH", 12) != 0) return 2;
  if (wcsncasecmp(L"what about if n is too small?", L"What ABOUT it?", 11) != 0) return 3;
  return 0;
}
