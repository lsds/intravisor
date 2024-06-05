#ifdef __CHERI__

#include <sys/auxv.h>
#include <errno.h>
#include "aux_helper.h"
#include "libc.h"

void *__getauxptr(unsigned long item)
{
	// error if asking for a non-pointer from getauxptr()
	switch (item) {
	AUX_PTR_CASES
		{
			auxv_entry *auxv = libc.auxv;
			for (; auxv->a_type; auxv++)
				if (auxv->a_type == item) return auxv->a_un.a_ptr;
		}
	}


	errno = ENOENT;
	return 0;
}

weak_alias(__getauxptr, getauxptr);

#endif
