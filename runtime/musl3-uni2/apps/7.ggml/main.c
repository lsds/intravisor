#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
 
char *argv[] = {"gpt-2", "-m", "/ggml-model.bin", "-p", "Once upon a time", "-t", "4", "-n", "100",  NULL};
int argc = 9;


#define FILENAME	"root.cpio"

#ifdef __cplusplus
extern "C" {
#endif
 
int ggml_main(int argc, char ** argv);

#ifdef __cplusplus
}
#endif


int main(int argc0, char **argv0) {
	printf("app main\n");

	ggml_main(argc, argv);
	exit(0);
}

void __cxa_atexit() {

}

void __cxa_begin_catch() {

}

void __cxa_end_catch() {

}


void __cxa_pure_virtual() {

}

void _Unwind_Resume (void * e) { 
	printf("not implemented %s\n", __func__);
}

__gxx_personality_v0() {
	printf("not implemented %s\n", __func__);
}
