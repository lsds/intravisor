#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intravisor.h"

void bail(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void *bail_alloc(size_t size) {
	void *p = calloc(1, size);
	if(!p) {
		bail("out of memory");
	}

	return p;
}

char *bail_strdup(const char *s) {
	char *c = strdup(s ? s : "");
	if(!c) {
		bail("out of memory");
	}

	return c;
}

void add_cvm(struct cvm **cvms, char *name, char *disk, char *runtime, char *net, char *args, long base, long size, long begin, long end, char *cb_out, char *cb_in, int wait, int cr, int lv) {
	struct cvm *f = bail_alloc(sizeof(*f));
	memset(f, 0, sizeof(struct cvm));
	if(name)
		f->name = bail_strdup(name);
	if(disk)
		f->disk = bail_strdup(disk);
	if(runtime)
		f->runtime = bail_strdup(runtime);
	if(net)
		f->net = bail_strdup(net);
	if(args)
		f->args = bail_strdup(args);
	if(cb_in)
		f->cb_in = bail_strdup(cb_in);
	if(cb_out)
		f->cb_out = bail_strdup(cb_out);

	f->isol.base = base;
	f->isol.size = size;
	f->isol.begin = begin;
	f->isol.end = end;
	f->wait = wait;
	f->cr = cr;
	f->lv = lv;

	if(!*cvms) {
		*cvms = f;
	} else {
		struct cvm *tail = *cvms;
		while(tail->next) {
			tail = tail->next;
		}
		tail->next = f;
	}
}

void destroy_cvms(struct cvm **cvms) {
	for(struct cvm * f = *cvms; f; f = *cvms) {
		*cvms = f->next;
		free(f->name);
		free(f->disk);
		free(f->runtime);
		free(f->net);
		free(f->cb_in);
		free(f->cb_out);
		free(f->args);
		free(f);
	}
}

void add_capfile(struct capfile **capfiles, char *name, char *data, long size, long addr) {
	struct capfile *f = bail_alloc(sizeof(*f));
	f->name = bail_strdup(name);
	f->data = bail_strdup(data);
	f->size = size;
	f->addr = addr;

	if(!*capfiles) {
		*capfiles = f;
	} else {
		struct capfile *tail = *capfiles;
		while(tail->next) {
			tail = tail->next;
		}
		tail->next = f;
	}
}

void destroy_capfiles(struct capfile **capfiles) {
	for(struct capfile * f = *capfiles; f; f = *capfiles) {
		*capfiles = f->next;
		free(f->name);
		free(f->data);
		free(f);
	}
}
