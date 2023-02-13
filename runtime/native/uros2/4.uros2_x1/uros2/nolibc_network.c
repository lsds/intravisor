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
#include <errno.h>

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

int connect(int socket, const struct sockaddr *address, socklen_t address_len) {
    return host_connect(socket, address, address_len);
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

int accept4(int socket, struct sockaddr *__restrict address, socklen_t *__restrict address_len, int flags) {
    return host_accept4(socket, address, address_len, flags);
}

ssize_t send(int socket, const void *buffer, size_t length, int flags) {
    return host_send(socket, buffer, length, flags);
}

ssize_t recv(int socket, void *buffer, size_t length, int flags) {
    return host_recv(socket, buffer, length, flags);
}

int getaddrinfo(const char *hostname, const char *servname, const struct addrinfo *hints, struct addrinfo **res) {
    return host_getaddrinfo(hostname, servname, hints, res);
}


int gethostname(char *name, size_t namelen) {
    memcpy(name, "localhost", 10);
}

int shutdown(int socket, int how) {
	printf("not implemented %s\n", __func__);
}

const char *inet_ntop(int af, const void *restrict a0, char *restrict s, socklen_t l)
{
    const unsigned char *a = a0;
    int i, j, max, best;
    char buf[100];

    switch (af) {
    case AF_INET:
	if (snprintf(s, l, "%d.%d.%d.%d", a[0],a[1],a[2],a[3]) < l)
	    return s;
	break;
    case AF_INET6:
	if (memcmp(a, "\0\0\0\0\0\0\0\0\0\0\377\377", 12))
	    snprintf(buf, sizeof buf,
		"%x:%x:%x:%x:%x:%x:%x:%x",
		256*a[0]+a[1],256*a[2]+a[3],
		256*a[4]+a[5],256*a[6]+a[7],
		256*a[8]+a[9],256*a[10]+a[11],
		256*a[12]+a[13],256*a[14]+a[15]);
	else
	    snprintf(buf, sizeof buf,
		"%x:%x:%x:%x:%x:%x:%d.%d.%d.%d",
		256*a[0]+a[1],256*a[2]+a[3],
		256*a[4]+a[5],256*a[6]+a[7],
		256*a[8]+a[9],256*a[10]+a[11],
		a[12],a[13],a[14],a[15]);
	/* Replace longest /(^0|:)[:0]{2,}/ with "::" */
	for (i=best=0, max=2; buf[i]; i++) {
	    if (i && buf[i] != ':') continue;
	    j = strspn(buf+i, ":0");
	    if (j>max) best=i, max=j;
	}
	if (max>3) {
	    buf[best] = buf[best+1] = ':';
	    memmove(buf+best+2, buf+best+max, i-best-max+1);
	}
	if (strlen(buf) < l) {
	    strcpy(s, buf);
	    return s;
	}
	break;
    default:
	errno = EAFNOSUPPORT;
	return 0;
    }
    errno = ENOSPC;
    return 0;
}

ssize_t
     sendmsg(int socket, const struct msghdr *message, int flags) {
     printf("not implemented %s\n", __func__);
     }
     
pid_t
     wait3(int *stat_loc, int options, struct rusage *rusage) {
     printf("not implemented %s\n", __func__);
     }


int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout) {
    return host_select(nfds, readfds, writefds, errorfds, timeout);
}


#include <netdb.h>
#include "locale_impl.h"

static const char msgs[] =
    "Invalid flags\0"
    "Name does not resolve\0"
    "Try again\0"
    "Non-recoverable error\0"
    "Unknown error\0"
    "Unrecognized address family or invalid length\0"
    "Unrecognized socket type\0"
    "Unrecognized service\0"
    "Unknown error\0"
    "Out of memory\0"
    "System error\0"
    "Overflow\0"
    "\0Unknown error";

const char *gai_strerror(int ecode)
{
    const char *s;
    for (s=msgs, ecode++; ecode && *s; ecode++, s++) for (; *s; s++);
    if (!*s) s++;
    return LCTRANS_CUR(s);
}

int getpeername(int socket, struct sockaddr *__restrict address, socklen_t *__restrict address_len) {
	host_getpeername(socket, address, address_len);
}

int __inet_aton(const char *s0, struct in_addr *dest)
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


in_addr_t inet_addr(const char *p)
{
	struct in_addr a;
	if (!__inet_aton(p, &a)) return -1;
	return a.s_addr;
}

static int hexval(unsigned c)
{
	if (c-'0'<10) return c-'0';
	c |= 32;
	if (c-'a'<6) return c-'a'+10;
	return -1;
}

int inet_pton(int af, const char *restrict s, void *restrict a0)
{
	uint16_t ip[8];
	unsigned char *a = a0;
	int i, j, v, d, brk=-1, need_v4=0;

	if (af==AF_INET) {
		for (i=0; i<4; i++) {
			for (v=j=0; j<3 && isdigit(s[j]); j++)
				v = 10*v + s[j]-'0';
			if (j==0 || (j>1 && s[0]=='0') || v>255) return 0;
			a[i] = v;
			if (s[j]==0 && i==3) return 1;
			if (s[j]!='.') return 0;
			s += j+1;
		}
		return 0;
	} else if (af!=AF_INET6) {
		errno = EAFNOSUPPORT;
		return -1;
	}

	if (*s==':' && *++s!=':') return 0;

	for (i=0; ; i++) {
		if (s[0]==':' && brk<0) {
			brk=i;
			ip[i&7]=0;
			if (!*++s) break;
			if (i==7) return 0;
			continue;
		}
		for (v=j=0; j<4 && (d=hexval(s[j]))>=0; j++)
			v=16*v+d;
		if (j==0) return 0;
		ip[i&7] = v;
		if (!s[j] && (brk>=0 || i==7)) break;
		if (i==7) return 0;
		if (s[j]!=':') {
			if (s[j]!='.' || (i<6 && brk<0)) return 0;
			need_v4=1;
			i++;
			break;
		}
		s += j+1;
	}
	if (brk>=0) {
		memmove(ip+brk+7-i, ip+brk, 2*(i+1-brk));
		for (j=0; j<7-i; j++) ip[brk+j] = 0;
	}
	for (j=0; j<8; j++) {
		*a++ = ip[j]>>8;
		*a++ = ip[j];
	}
	if (need_v4 && inet_pton(AF_INET, (void *)s, a-4) <= 0) return 0;
	return 1;
}

int net_close(int fildes) {
	host_close(fildes);
}