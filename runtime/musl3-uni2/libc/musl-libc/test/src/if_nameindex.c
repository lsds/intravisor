#include <net/if.h>
#include <stdio.h>
#include <string.h>

int main() {
	struct if_nameindex *namei, *p;
	int i, n = sizeof(struct if_nameindex);

	namei = if_nameindex();
	if (!namei) return 1;
	if (!__builtin_cheri_tag_get(namei)) return 2;

	for(p = namei, i=n;p->if_name;p++, i += n){
		// Check string within allocation
		if(!__builtin_cheri_tag_get(p->if_name)) return 3;
		if(!__builtin_cheri_subset_test(p->if_name, namei)) return 4;
		i += strlen(p->if_name) + 1;
	}
	// Compare bounds with size
	if(__builtin_cheri_length_get(namei) != i) return 5;

	if_freenameindex(namei);
	return 0;
}
