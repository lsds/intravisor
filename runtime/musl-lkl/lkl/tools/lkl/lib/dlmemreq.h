#include <lkl_host.h>

void *dl_malloc(unsigned long size);
void *dl_calloc(int num, int size);
void dl_free(void *ptr);
char* get_memory(unsigned num_bytes);

