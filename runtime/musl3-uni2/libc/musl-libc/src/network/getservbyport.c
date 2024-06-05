#define _GNU_SOURCE
#include <netdb.h>

struct servent *getservbyport(int port, const char *prots)
{
	static struct servent se;
	static uintptr_t buf[64/sizeof(uintptr_t)];
	struct servent *res;
	if (getservbyport_r(port, prots, &se, (void *)buf, sizeof buf, &res))
		return 0;
	return &se;
}
