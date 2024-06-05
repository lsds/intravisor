#ifndef TLS_LIB
#define TLS_LIB

#include <threads.h>
extern thread_local int foo;
extern thread_local double bar;
extern thread_local const long baz;

#endif
