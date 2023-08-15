#define _GNU_SOURCE
#include <netdb.h>

struct servent *getservbyname(const char *name, const char *prots)
{
printf("%s %d\n", __func__, __LINE__);
	static struct servent se;
	static char *buf[2];
	struct servent *res;
	if (getservbyname_r(name, prots, &se, (void *)buf, sizeof buf, &res))
		return 0;
	return &se;
}
