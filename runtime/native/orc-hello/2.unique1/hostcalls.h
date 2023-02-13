#ifndef _HOSTCALLS___H_
#define	_HOSTCALLS___H_

#include <arch.h>

void *my_memcpy(void *dst, void *src, unsigned long n);
void *my_memset(void *dst, char c, unsigned long n);


// hostcalls
__intcap_t c_out_7(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_6(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_5(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_4(int, __intcap_t, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_3(int, __intcap_t, __intcap_t, __intcap_t);
__intcap_t c_out_2(int, __intcap_t, __intcap_t);
__intcap_t c_out_1(int, __intcap_t);
__intcap_t c_out_0(int);


int host_get_my_inner(void *ptr);
int host_get_sc_caps(int me, int they, void *ptr);

int host_write_out(char *ptr, int size);

void host_exit();
int host_inv(char *dst, char *src, int size);



#endif