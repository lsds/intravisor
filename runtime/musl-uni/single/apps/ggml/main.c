#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
 
extern void copy_cpio(__intcap_t *);
extern long host_get_cpio_size( char *);
extern long host_load_cpio(char *, __intcap_t, long);

char *argv[] = {"gpt-2", "-m", "/ggml-model.bin", "-p", "Once upon a time", "-t", "4", "-n", "100",  NULL};
int argc = 9;


#define FILENAME	"root_ggml.cpio"

int app_main(void) {
	printf("app main\n");


	long size = host_get_cpio_size(FILENAME);

	__intcap_t *cpio = malloc(size);

	long size2 = host_load_cpio(FILENAME, cpio, size);
	printf("size2 = %d, size = %d\n", size2, size);

	copy_cpio((__intcap_t *) cpio);

	free(cpio);
	extern int main(int argc, char **argv);
	main(argc, argv);
}

#if 1
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

#include <stdio.h>
#include <wchar.h>


 catopen(){
	printf("not implemented %s\n", __func__);
}

 catgets(){
 	printf("not implemented %s\n", __func__);
 }

 catclose(){
 	printf("not implemented %s\n", __func__);
 }

 __loc_is_allocated() {
 	printf("not implemented %s\n", __func__);
}

 __libc_free(){
 	printf("not implemented %s\n", __func__);
 }

wint_t fputwc (wchar_t, FILE *) {
	printf("not implemented %s\n", __func__);
}

fwide() {
	printf("not implemented %s\n", __func__);
}


char *realpath (const char *__restrict, char *__restrict) {
	printf("not implemented %s\n", __func__);
}

link() {
	printf("not implemented %s\n", __func__);
}

sendfile() {
	printf("not implemented %s\n", __func__);
}

pathconf() {
	printf("not implemented %s\n", __func__);
}

utimensat() {
	printf("not implemented %s\n", __func__);
}

fchmodat() {
	printf("not implemented %s\n", __func__);
}

statvfs() {
	printf("not implemented %s\n", __func__);
}

#endif