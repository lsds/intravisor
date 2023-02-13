#include <sys/types.h>
#include "_types.h"
#include <stdarg.h>

#include <string.h>
#include <stdio.h>

#include <netdb.h>
#include <netinet/in.h>
#include <byteswap.h>
#include <string.h>
#include <stdlib.h>

#include <poll.h>

#include "cheri_helpers.h"
#include "hostcalls.h"

#define UCHAR_MAX 255

#define ALIGN (sizeof(size_t))
#define ONES ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) ((x)-ONES & ~(x) & HIGHS)

#define true 1


uint16_t htons(uint16_t n)
{
    union { int i; char c; } u = { 1 };
    return u.c ? bswap_16(n) : n;
}

char *inet_ntoa(struct in_addr in)
{
    static char buf[16];
    unsigned char *a = (void *)&in;
    snprintf(buf, sizeof buf, "%d.%d.%d.%d", a[0], a[1], a[2], a[3]);
    return buf;
}

uint16_t ntohs(uint16_t n)
{
    union { int i; char c; } u = { 1 };
    return u.c ? bswap_16(n) : n;
}

uint32_t ntohl(uint32_t n)
{
    union { int i; char c; } u = { 1 };
    return u.c ? bswap_32(n) : n;
}

uint32_t htonl(uint32_t n)
{
    union { int i; char c; } u = { 1 };
    return u.c ? bswap_32(n) : n;
}

int   isdigit(int);
#define isdigit(a) (0 ? isdigit(a) : ((unsigned)(a)-'0') < 10)

int inet_aton(const char *s0, struct in_addr *dest)
{
    const char *s = s0;
    unsigned char *d = (void *)dest;
    unsigned long a[4] = { 0 };
    char *z;
    int i;

    for (i=0; i<4; i++) {
	a[i] = strtoul(s, &z, 0);
	if (z==s || (*z && *z != '.') || !isdigit(*s))
	    return 0;
	if (!*z) break;
	s=z+1;
    }
    if (i==4) return 0;
    switch (i) {
    case 0:
	a[1] = a[0] & 0xffffff;
	a[0] >>= 24;
    case 1:
	a[2] = a[1] & 0xffff;
	a[1] >>= 16;
    case 2:
	a[3] = a[2] & 0xff;
	a[2] >>= 8;
    }
    for (i=0; i<4; i++) {
	if (a[i] > 255) return 0;
	d[i] = a[i];
    }
    return 1;
}

void *my_malloc(size_t size);
/* Align 'n' up to the value 'align', which must be a power of two. */
static unsigned long align_up(unsigned long n, unsigned long align)
{
    return (n + align - 1) & (~(align - 1));
}


static struct hostent *fake_hostent(const char *hostname, struct in_addr addr,
				    struct hostent *result, char *buf,
				    int bufsize)
{
    int len = strlen(hostname);
    char *name, *addr_ptr;


    /* Copy faked name and address into buffer. */
    strcpy(buf, hostname);
    name = buf;
#ifdef __CHERI_PURE_CAPABILITY__
//    buf = ALIGN(buf + len + 1, addr);
	unsigned long ab1 = align_up((unsigned long)(buf) + len + 1, sizeof(addr)) - (unsigned long)buf;
	buf = __builtin_cheri_offset_increment(buf, ab1);

    *((struct in_addr *) buf) = addr;
    addr_ptr = buf;
//    buf = ALIGN(buf + sizeof(addr), char *);

	unsigned long ab2 = align_up((unsigned long)(buf) + sizeof(addr), sizeof(char *)) - (unsigned long)buf;
	buf = __builtin_cheri_offset_increment(buf, ab2);
#else
	printf("not implemented %s\n", __func__);
#endif


    ((char **) buf)[0] = addr_ptr;
    ((char **) buf)[1] = NULL;
    ((char **) buf)[2] = NULL;

    result->h_name = name;
    result->h_aliases = ((char **) buf) + 2;
    result->h_addrtype = AF_INET;
    result->h_length = sizeof(addr);
    result->h_addr_list = (char **) buf;

    return result;
}

struct hostent *gethostbyname(const char *hostname)
{
    char *buf = my_malloc(1024);
    struct hostent *h = (struct hostent *) buf;
    char *buf1 = &buf[sizeof(struct hostent)];
    
    struct in_addr addr;
    
    inet_aton(hostname, &addr);
    
    return fake_hostent(hostname, addr, h, buf1, 1024 - sizeof(struct hostent));
}

int socket(int domain, int type, int protocol) {
    return host_socket(domain, type, protocol);
}

int setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
    return host_setsockopt(socket, level, option_name, option_value, option_len);
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
    return host_bind(socket, (void *)address, address_len);
}

int listen(int socket, int backlog) {
    return host_listen(socket, backlog);
}

int poll(struct pollfd fds[], nfds_t nfds, int timeout) {
    return host_poll(fds, nfds, timeout);
}

int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
    return host_accept(socket, address, address_len);
}

ssize_t send(int socket, const void *buffer, size_t length, int flags) {
    return host_send(socket, buffer, length, flags);
}

ssize_t recv(int socket, void *buffer, size_t length, int flags) {
    return host_recv(socket, buffer, length, flags);
}

int gethostname(char *name, size_t namelen) {
    memcpy(name, "localhost", 10);
}

int shutdown(int socket, int how) {
	printf("not implemented %s\n", __func__);
}