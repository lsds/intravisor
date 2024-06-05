#ifndef __UK_ALLOC_H__
#define __UK_ALLOC_H__

#include <uk/arch/types.h>
#include <uk/config.h>
#include <uk/assert.h>
#include <uk/essentials.h>

#ifdef __cplusplus
extern "C" {
#endif

void *uk_malloc(void *a, __sz size);
void uk_free(void *a, void *ptr);


#ifdef __cplusplus
}
#endif

#endif /* __UK_ALLOC_H__ */
