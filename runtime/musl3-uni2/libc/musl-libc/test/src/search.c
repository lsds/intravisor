#define _GNU_SOURCE
#include <search.h>
#include <string.h>

#define W 80
#define L 100

struct t_node {
	void *key;
	void *a[2];
	int h;
};

struct t_data {
	char *name;
	int val;
};

static void *root;
static struct t_data tdata[L];
static char ldata[L][W];
static size_t n;

char* keys[] = {"", "a", "b", "aaa", "abc", "zzzzzzzzzzzz"};

int checkl(char * ret, char * exp) {
	if (__builtin_cheri_tag_get(ret) != 1) return 1;
	if (__builtin_cheri_subset_test(ret, ldata) != 1) return 2;
	if (strcmp(ret, exp)) return 3;
	return 0;
}

int setl(char * key){
	char *ret = lsearch(key, ldata, &n, W, (int(*)(const void*,const void*))strcmp);
	return checkl(ret, key);
}

int getl(char * key){
	char *ret = lfind(key, ldata, &n, W, (int(*)(const void*,const void*))strcmp);
	return checkl(ret, key);
}

int cmpt(const void *a, const void *b){
	return strcmp(((struct t_data*)a)->name, ((struct t_data*)b)->name);
}

int checkt(void * p){
	if (!p) return 1;
	if (__builtin_cheri_length_get(p) != sizeof(struct t_node)) return 2;
	if (!__builtin_cheri_subset_test(((struct t_node*)p)->key, tdata)) return 3;
	return 0;
}

int sett(char * key, int val){
	void *p;
	tdata[val].name = key;
	tdata[val].val = val;
	p = tsearch(&tdata[val], &root, cmpt);
	return checkt(p);
}

int gett(char * key, int exp_val){
	void *p, *pd;
	struct t_data tmp = {.name = key};
	p = tfind(&tmp, &root, cmpt);
	pd = ((struct t_node*)p)->key;
	if (!(((struct t_data*)pd)->val == exp_val)) return 4;
	return checkt(p);
}

void delt(void * data){
	((struct t_data*)data)->val = 0;
}

int test_lsearch(void){
	int i, r, nset;
	int lim = sizeof(keys) / sizeof(char*);
	for (i=0;i<lim;i++){
		if ((r=setl(keys[i]))) return r;
	}
	nset = n;
	if (n != lim) return 4;

	for (i=0;i<lim;i++){
		if ((r=getl(keys[i]))) return r+4;
	}
	if ((r=setl("a"))) return r;
	if (n != nset) return 8;

	// Additional check with offset capability
	if ((r=setl(keys[lim-1]+2))) return r;
	return 0;
}

int test_tsearch(void){
	int i, r;
	int lim = sizeof(keys)/sizeof(char*);
	void *ptr;
	for (i=0;i<lim;i++)
		if ((r=sett(keys[i], i))) return r;
	for (i=0;i<lim;i++)
		if ((r=gett(keys[i], i))) return r+3;
	if (!(ptr=tdelete(&tdata[2], &root, cmpt))) return 8;
	if ((ptr=tfind(&tdata[2], &root, cmpt))) return 9;
	tdestroy(root, delt);
	for (i=0;i<lim;i++)
		if (i != 2 && tdata[i].val) return 10;
	return 0;
}


int main(int argc, char *argv[]){
	if (argc < 2) return -1;
	switch (argv[1][0]){
	case '0':
		return test_lsearch();
	case '1':
		return test_tsearch();
	default:
		return -2;
	}
}

