#include <stdio.h>

void ctor() __attribute__((constructor));
void ctor2() __attribute__((constructor));

void ctor() {
	printf("ctor call ");
}

void ctor2() {
	fprintf(stderr, "ctor call2 ");
}
void dtor() __attribute__((destructor));
void dtor2() __attribute__((destructor));

void dtor() {
	printf("dtor call\n");
}

void dtor2() {
	fprintf(stderr,"dtor call2\n");
}

int main(int argc, char *argv[]) {
	return 0;
}
