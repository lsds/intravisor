#ifndef _CMPT_H
#define _CMPT_H
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//NOTE: Experimental, possibly will be subject to significant change
typedef void (cmpt_target_t)(void* secret, void* arg);

typedef struct
{
	void *__opaque[8];
} cmpt_t;


int create_cmpt(cmpt_t* dst, const char* data, const size_t data_size, cmpt_target_t target);
int destroy_cmpt(cmpt_t*);
void call_to_cmpt(const cmpt_t*, void* arg);
bool is_cmpt_valid(const cmpt_t*);
#ifdef __cplusplus
}
#endif
#endif
