#include <wchar.h>

int main() {
  if (wcsncmp(L"should match!", L"should match, honest", 12)) return 1;
  if (wcsncmp(L"should be greater", L"", 11) <= 0) return 2;
  if (wcsncmp(L"", L"should be less", 5) >= 0) return 3;
  if (wcsncmp(L"", L"", 1)) return 4;
  if (wcsncmp(L"should be", L"slightly less", 2) >= 0) return 5;
  if (wcsncmp(L"this should be greater", L"than this", 14) <= 0) return 6;
  return 0;
}
