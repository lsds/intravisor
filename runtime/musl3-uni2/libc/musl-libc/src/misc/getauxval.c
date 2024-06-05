#include <sys/auxv.h>
#include <errno.h>
#include "aux_helper.h"
#include "libc.h"

unsigned long __getauxval(unsigned long item)
{
#ifdef __CHERI__
	// error if asking for a pointer from getauxval()
	switch (item) {
	AUX_NONVAL_CASES
		goto error;
	}
#endif

	auxv_entry *auxv = libc.auxv;
	if (item == AT_SECURE) return libc.secure;
	for (; auxv->a_type; auxv++)
		if (auxv->a_type == item) return auxv->a_un.a_val;

error:
	errno = ENOENT;
	return 0;
}

weak_alias(__getauxval, getauxval);
