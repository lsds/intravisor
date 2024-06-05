#include <wchar.h>

int main() {
  if (wmemcmp(L"should match", L"should match", 13)) return 1;
  if (wmemcmp(L"should be greater", L"", 1) <= 0) return 2;
  if (wmemcmp(L"", L"should be less", 1) >= 0) return 3;
  if (wmemcmp(L"", L"", 1)) return 4;
  if (wmemcmp(L"should be", L"slightly less", 10) >= 0) return 5;
  if (wmemcmp(L"this should be greater", L"than this", 9) <= 0) return 6;
  return 0;
}
