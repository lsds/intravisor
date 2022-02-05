#include <elf.h>

typedef struct encl_map_info {
    void* base;
    size_t size;
    void* entry_point;
	unsigned long ret_point;
	unsigned long syscall_handler;
} encl_map_info;

void load_elf(char* file_to_map, void *base_addr, encl_map_info* result);

