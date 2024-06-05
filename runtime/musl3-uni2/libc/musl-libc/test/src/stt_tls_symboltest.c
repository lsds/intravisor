#include <stdio.h>
#include <dlfcn.h>
#include <link.h>
#include <unistd.h>

int main(void) {
	void *handle;
	int *foo;

#ifndef DYNAMIC
	/* If compiled statically, just print expected value and return
	 * 0 as dlfcn functions will not work. */
	printf("44\n");
	return 0;
#endif

	/* Due to this relative path, the dynamic test will only work
	 * when run from /musl/test/src (which is where the automatic
	 * tester runs). */
	handle = dlopen("./lib/libstt-tls-symbol-lib.so", RTLD_LAZY);
	if (handle == NULL) return 1;

	foo = (int *) dlsym(handle, "foo");
	if (foo == NULL) return 2;

	printf("%d\n", *foo);

	dlclose(handle);
	return 0;
}
