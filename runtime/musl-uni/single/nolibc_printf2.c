#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#include "stdio_impl.h"
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
#include <inttypes.h>
#include <math.h>
#include <float.h>

static char send_buf[1024];

int printf(const char *restrict fmt, ...) {
	int ret;
	va_list ap;
	va_start(ap, fmt);
//    ret = vfprintf(stdout, fmt, ap);
	ret = vsnprintf(send_buf, 1024, fmt, ap);
	va_end(ap);

	host_write_out(send_buf, ret);

	return ret;
}

size_t __stdout_write(FILE * f, const unsigned char *buf, size_t len) {
	host_write_out(buf, len);
	return len;
}
