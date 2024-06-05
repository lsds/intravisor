#include <wchar.h>
#include <stdint.h>

#define N 100
static wchar_t buf[N];
static wchar_t buf2[N];

static wchar_t *aligned(void *p) {
	return (wchar_t*)(((uintptr_t)p + 63) & -64);
}

int test_align(int align, int len) {
	wchar_t *s = aligned(buf+16) + align;
	wchar_t *want = aligned(buf2+16) + align;
	wchar_t *p;
	int i;

	if (len + 16 > buf + N - s || len + 16 > buf2 + N - want)
		return 4;
	for (i = 0; i < N; i++)
		buf[i] = buf2[i] = L'x';
	for (i = 0; i < len; i++)
		want[i] = L'a';
	p = wmemset(s, L'a', len);
	if (p != s)
		return 5;
	for (i = -16; i < len+16; i++)
		if (s[i] != want[i])
			return 6;
	return 0;
}

int main() {
	int i,j,k;
	wchar_t a[30];

	for (i = 0; i < 16; i++)
		for (j = 0; j < 16; j++) {
			k = test_align(i, j);
			if (k) return k;
		}
	wmemset(a, L'a', sizeof(a) / sizeof(wchar_t) - 1);
	a[sizeof(a) / sizeof(wchar_t) - 1] = 0;
	if (__builtin_cheri_tag_get(a) != 1) return 1;
	if (__builtin_cheri_length_get(a) != sizeof(a)) return 2;
	if (wcscmp(a, L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaa")) return 3;

	return 0;
}
