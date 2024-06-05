#include <ftw.h>

int fn(const char *path, const struct stat * st, int d) {
	if (!__builtin_cheri_tag_get(path)) return 1;
	if (!__builtin_cheri_tag_get(st)) return 2;
	if (__builtin_cheri_length_get(st) != sizeof(struct stat)) return 3;
	return 0;
}

int fn_n(const char *p, const struct stat * st, int d, struct FTW *ftwbuf) {
	return fn(p, st, d);
}

int main() {
	int r;
	if((r=ftw(".", fn, 2))) return r;
	r = nftw(".", fn_n, 2, 0);
	return r;
}
