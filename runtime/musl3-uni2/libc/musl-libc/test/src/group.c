#define _GNU_SOURCE
#include <grp.h>
#include <stdio.h>
#include <string.h>

int check_group(struct group *grp){
	char *name, *pass;
	if (!grp) return 1;
	if (!__builtin_cheri_tag_get(grp)) return 2;
	if (__builtin_cheri_length_get(grp) != sizeof(struct group)) return 3;
	if (!(name = grp->gr_name) && __builtin_cheri_length_get(name) != strlen(name)) return 4;
	if (!(pass = grp->gr_passwd) && __builtin_cheri_length_get(pass) != strlen(pass)) return 5;
	return 0;
}

int main(void){
	FILE *f;
	struct group *grp;
	int r;

	f = fopen("/etc/group", "r");
	grp = fgetgrent(f);
	if ((r = check_group(grp))) return r;
	fclose(f);

	while ((grp = getgrent()))
		if ((r = check_group(grp))) return r;

	setgrent();
	grp = getgrnam("disk");
	if (strcmp(grp->gr_name, "disk")) return 7;
	if ((r = check_group(grp))) return r;

	grp = getgrgid(12);
	if (grp->gr_gid != 12) return 8;
	if ((r = check_group(grp))) return r;

	endgrent();
	return 0;
}
