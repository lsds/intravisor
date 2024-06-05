#include <wchar.h>

int main() {
  if (wcscmp(L"should match", L"should match")) return 1;
  if (wcscmp(L"should be greater", L"") <= 0) return 2;
  if (wcscmp(L"", L"should be less") >= 0) return 3;
  if (wcscmp(L"", L"")) return 4;
  if (wcscmp(L"should be", L"slightly less") >= 0) return 5;
  if (wcscmp(L"this should be greater", L"than this") <= 0) return 6;
  return 0;
}
