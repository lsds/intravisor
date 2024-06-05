#include <stdio.h>
#include <sys/types.h>

#define _GNU_SOURCE
#include <pwd.h>
#include <unistd.h>
#include <stddef.h>
#include <grp.h>
#include <errno.h>

static int test_fgetpwent();
static int test_getgrouplist();

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 1;
	}
	switch (argv[1][0]) {
	case '0': return test_fgetpwent();
	case '1': return test_getgrouplist();
	default: return 2;
	}
}

static int test_fgetpwent()
{
	FILE *f = fopen("/etc/passwd", "rt");
	struct passwd *p = fgetpwent(f);
	if (__builtin_cheri_tag_get(p) == 0) {
		fclose(f);
		return 1;
	}
	printf("res = %s\n", p->pw_name);
	if (__builtin_cheri_tag_get(p->pw_name) == 0) {
		fclose(f);
		return 1;
	}
	if (__builtin_cheri_tag_get(p->pw_passwd) == 0) {
		fclose(f);
		return 1;
	}
	if (__builtin_cheri_tag_get(p->pw_gecos) == 0) {
		fclose(f);
		return 1;
	}
	if (__builtin_cheri_tag_get(p->pw_dir) == 0) {
		fclose(f);
		return 1;
	}
	if (__builtin_cheri_tag_get(p->pw_shell) == 0) {
		fclose(f);
		return 1;
	}
	printf("res = %s %s\n", p->pw_dir, p->pw_shell);
	fclose(f);
	return 0;
}

static int test_getgrouplist()
{
	int pz = 3;
	gid_t groups[3] = {1, 2, 3};
	errno = 0;
	int res = getgrouplist("root", 0, groups, &pz);
	if (errno) {
		// todo: rework this when connect is ported
		perror("getgrouplist");
		return 1;
	}
	printf("res = %d\n", res);
	for (int n = 0; n < pz; n++) {
		printf("%u\n", groups[n]);
	}
	return 0;
}
