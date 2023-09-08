#include "sqlite3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#ifndef _WIN32
# include <unistd.h>
#else
# include <io.h>
#endif
#define ISSPACE(X) isspace((unsigned char)(X))
#define ISDIGIT(X) isdigit((unsigned char)(X))

#if SQLITE_VERSION_NUMBER<3005000
# define sqlite3_int64 sqlite_int64
#endif



__intcap_t sqlite_syscalls(long t5, void *a0, void *a1, void *a2, void  *a3, void *a4, void *a5, void *a6) {
	__intcap_t ret = 0; 

	switch(t5) {
		case 900:
			return sqlite3_vfs_find(a0);
		case 901:
			return sqlite3_libversion_number();
		case 902:
			return sqlite3_reset(a0);
		case 903:
			return sqlite3_sql(a0);
		case 904:
			return sqlite3_step(a0);
		case 905:
			return sqlite3_exec(a0, a1, a2, a3, a4);
		case 906:
			sqlite3_free(a0);
			return 0;
		case 907:
			return sqlite3_finalize(a0);
		case 908:
			return sqlite3_column_count(a0);
		case 909:
			return sqlite3_db_release_memory(a0);
		case 910:
			return sqlite3_close(a0);
		case 911:
			return sqlite3_errmsg(a0);
		case 912:
			return sqlite3_strglob(a0, a1);
		case 913:
		//SQLITE_API const char *sqlite3_libversion(void);
			return sqlite3_libversion();
		case 914:
			return sqlite3_stricmp(a0, a1);
		case 915:
		//SQLITE_API const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
			return sqlite3_column_text(a0, a1);
		case 916:
			return sqlite3_initialize();
		case 917:
		//SQLITE_API const char *sqlite3_sourceid(void);
			ret = sqlite3_sourceid();
			return ret;
		case 918:
			sqlite3_result_int64(a0, a1);
			return 0;
		case 919:
			return sqlite3_status(a0, a1, a2, a3);
		case 920:
			return sqlite3_db_status(a0, a1, a2, a3, a4);

		case 921:
//SQLITE_API int sqlite3_create_function(
//  sqlite3 *db,
//  const char *zFunctionName,
//  int nArg,
//  int eTextRep,
//  void *pApp,
//  void (*xFunc)(sqlite3_context*,int,sqlite3_value**),
//  void (*xStep)(sqlite3_context*,int,sqlite3_value**),
//  void (*xFinal)(sqlite3_context*)
//);

//NB: eTextRep is SQLITE_UTF8 will be forced on the other side
			return sqlite3_create_function(a0, a1, a2, SQLITE_UTF8, a3, a4, a5, a6);

		case 922:
			return sqlite3_prepare_v2(a0, a1, a2, a3, a4);
		case 923:
			return (int) sqlite3_open(a0, a1);
		case 924:
			return (int) sqlite3_config(a0);
		case 925:
			return (int) sqlite3_config(a0, a1);
		case 926:
			return (int) sqlite3_config(a0, a1, a2);
		case 927:
			return (int) sqlite3_config(a0, a1, a2, a3);
		case 928:
			return (int) sqlite3_db_config(a0, a1, a2, a3, a4);
		case 929: 
			return (int) sqlite3_bind_text(a0, a1, a2, a3, a4);
		case 930:
			return (int) sqlite3_bind_int(a0, a1, a2);
		case 931:
			return (int) sqlite3_bind_int64(a0, a1, a2);
		case 932:
			return (char *)sqlite3_vmprintf(a0, a1);
		case 933:
			return (char *)sqlite3_snprintf(a0, a1, a2);
		case 934:
			return (char *)sqlite3_snprintf(a0, a1, a2, a3);
		default:
			printf("SQLite/Speedtest how? %d\n", (int) t5);
			while(1);
	}
}