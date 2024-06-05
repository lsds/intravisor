#include <hostcalls.h>

int ukplat_coutd(const char *str, unsigned int len) {
	host_write_out(str, len);
	return (int) len;
}

int ukplat_coutk(const char *str, unsigned int len) {

	host_write_out(str, len);
	return (int) len;
}

int ukplat_cink(char *buf, unsigned int maxlen)
{
	return 0;
}
