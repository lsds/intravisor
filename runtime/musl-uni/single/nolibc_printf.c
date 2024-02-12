#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

#define true 1

unsigned int mini_strlen(const char *s) {
	unsigned int len = 0;
	while(s[len] != '\0')
		len++;
	return len;
}

static unsigned int mini_itoa(int value, unsigned int radix, unsigned int uppercase, unsigned int unsig, char *buffer, unsigned int zero_pad) {
	char *pbuffer = buffer;
	int negative = 0;
	unsigned int i, len;

	/* No support for unusual radixes. */
	if(radix > 16)
		return 0;

	if(value < 0 && !unsig) {
		negative = 1;
		value = -value;
	}

	/* This builds the string back to front ... */
	do {
		int digit = value % radix;
		*(pbuffer++) = (digit < 10 ? '0' + digit : (uppercase ? 'A' : 'a') + digit - 10);
		value /= radix;
	} while(value > 0);

	for(i = (pbuffer - buffer); i < zero_pad; i++)
		*(pbuffer++) = '0';

	if(negative)
		*(pbuffer++) = '-';

	*(pbuffer) = '\0';

	/* ... now we reverse it (could do it recursively but will
	 * conserve the stack space) */
	len = (pbuffer - buffer);
	for(i = 0; i < len / 2; i++) {
		char j = buffer[i];
		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = j;
	}

	return len;
}

struct mini_buff {
	char *buffer, *pbuffer;
	unsigned int buffer_len;
};

static int _putc(int ch, struct mini_buff *b) {
	if((unsigned int) ((b->pbuffer - b->buffer) + 1) >= b->buffer_len)
		return 0;
	*(b->pbuffer++) = (char) ch;
	*(b->pbuffer) = '\0';
	return 1;
}

static int _puts(char *s, unsigned int len, struct mini_buff *b) {
	unsigned int i;

	if(b->buffer_len - (b->pbuffer - b->buffer) - 1 < len)
		len = b->buffer_len - (b->pbuffer - b->buffer) - 1;

	/* Copy to buffer */
	for(i = 0; i < len; i++)
		*(b->pbuffer++) = s[i];
	*(b->pbuffer) = '\0';

	return len;
}

int mini_vsnprintf(char *buffer, unsigned int buffer_len, const char *fmt, va_list va) {
	struct mini_buff b;
	char bf[24];
	char ch;

	b.buffer = buffer;
	b.pbuffer = buffer;
	b.buffer_len = buffer_len;

	while((ch = *(fmt++))) {
		if((unsigned int) ((b.pbuffer - b.buffer) + 1) >= b.buffer_len)
			break;
		if(ch != '%')
			_putc(ch, &b);
		else {
			char zero_pad = 0;
			char *ptr;
			unsigned int len;

			ch = *(fmt++);

			/* Zero padding requested */
			if(ch == '0') {
				ch = *(fmt++);
				if(ch == '\0')
					goto end;
				if(ch >= '0' && ch <= '9')
					zero_pad = ch - '0';
				ch = *(fmt++);
			}

			switch (ch) {
			case 0:
				goto end;
			case 'u':
			case 'd':
				len = mini_itoa(va_arg(va, unsigned int), 10, 0, (ch == 'u'), bf, zero_pad);
				_puts(bf, len, &b);
				break;

			case 'x':
			case 'X':
				len = mini_itoa(va_arg(va, unsigned int), 16, (ch == 'X'), 1, bf, zero_pad);
				_puts(bf, len, &b);
				break;

			case 'c':
				_putc((char) (va_arg(va, int)), &b);
				break;
#if 1
			case 's':
				ptr = va_arg(va, char *);
				_puts(ptr, mini_strlen(ptr), &b);
				break;
#endif
			default:
				_putc(ch, &b);
				break;
			}
		}
	}
      end:
	return b.pbuffer - b.buffer;
}

char pbuf[4096];
char pbuf2[4096];

int mini_printf(const char *fmt, ...) {
	int ret;

	memset(pbuf2, 0, 4096);
	va_list va;
	va_start(va, fmt);
	ret = mini_vsnprintf(pbuf2, 4096, fmt, va);
	va_end(va);

	host_write_out(pbuf2, ret);

	return ret;
}

#if 1

int puts(const char *s) {
	host_write_out((char *) s, strlen(s) + 1);
}

int putchar(int c) {
	char a = (char) c;
	host_write_out(&a, 1);
	return c;
}

#endif
