#include "hostcalls.h"

extern long c_out(void *);

int host_write_out(char *ptr, int size) {
#if 0
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) size;

	__asm__ __volatile__("cjr %4" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1), "C"(c_out) : "memory" );
	return (int) a0; 

#else
	return (int) c_out_3(1, (long) ptr, (long) size, 0);
#endif
}

int host_get_sc_caps(int me, int they, void *ptr) {
	return c_out_3(702, me, they, ptr);
}

void ramfs_caps_init() {
	c_out_3(750, 0, 0, 0);
}

void vfs_caps_init() {
	c_out_3(1005, 0, 0, 0);
}

void nolibc_caps_init() {
	c_out_3(752, 0, 0, 0);
}

void sqlite_caps_init() {
	c_out_3(935, 0, 0, 0);
}


///////////////////////

int host_gettimeofday(void *ptr, void *ptr2) {
#if 0
	int tmp = 1;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;
	register long a1 __asm__("a1") = (long) ptr2;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return a0; 

#else
	return c_out_3(800, (long) ptr, (long) ptr2, 0);
#endif


}

int host_lstat(const char *pathname, struct stat *statbuf) {
	return (int) c_out_3(801, pathname, statbuf, 0);
}
int host_stat(const char *pathname, struct stat *statbuf) {
	return c_out_3(806, pathname, statbuf, 0);
}
int host_fstat(int fd, struct stat *statbuf) {
	return c_out_3(807, fd, statbuf, 0);
}

int host_unlink(const char *pathname) {
	return (int) c_out_3(802, pathname, 0, 0);
}

int host_close(int fd) {
	return (int) c_out_3(803, fd, 0, 0);
}
int host_access(const char *pathname, int mode) {
	return (int) c_out_3(804, pathname, mode, 0);
}

int host_truncate(const char *path, size_t length) {
	return c_out_3(808, path, length, 0);
}
__ssize_t host_read(int fd, void *buf, size_t count) {
	return c_out_3(809, fd, buf, count);
}
__ssize_t host_write(int fd, const void *buf, size_t count) {
	return c_out_3(810, fd, buf, count);
}
int host_open(const char *pathname, int flags, mode_t mode) {
	return c_out_3(811, pathname, flags, mode);
}

off_t host_lseek(int fd, off_t offset, int whence) {
	return (off_t) c_out_3(812, fd, offset, whence);
}

int host_get_errno() {
	return c_out_3(813, 0, 0, 0);
}

int host_fcntl(int fd, int cmd, long *ptr ) {
	return c_out_3(814, fd, cmd, ptr);
}

void host_nolibos_init(void) {
	c_out_3(815, 0, 0, 0);
}


////////////////////////

void host_exit() {
#if 0
	int tmp = 13;
	register long a0 __asm__("a0");
	register long t5 __asm__("t5") = tmp;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5) : "memory" );
#else
	c_out_3(13, 0, 0, 0);
#endif
}

int host_cap_prb(char *key, void *location) {
#if 0
	int tmp = 406;
	register long a0 __asm__("a0") = (long) key;
	register long a1 __asm__("a1") = (long) location;
	register long t5 __asm__("t5") = tmp;
	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0), "r"(a1) : "memory" );
	return (int) a0; 
#else
	return c_out_3(406, (long) key, (long) location, 0);
#endif
}


int host_get_my_inner(void *ptr) {
#if 0
	int tmp = 700;
	register long t5 __asm__("t5") = tmp;
	register long a0 __asm__("a0") = (long) ptr;

	__asm__ __volatile__("jal c_out" : "=r"(a0) : "r"(t5), "r"(a0) : "memory" );
	return (int) a0;
#else
	return c_out_3(700, (long) ptr, 0, 0);
#endif
}

int host_syscall_handler_prb(char *name, void *a, void *b, void *c) {
	return c_out_5(701, name, a, b, c, 0);
}

////////////////////////////////

//SQLITE_API sqlite3_vfs *sqlite3_vfs_find(const char *zVfsName);
void *sqlite3_vfs_find(const char *name) {
	return c_out_3(900, name, 0, 0);
}

//SQLITE_API int sqlite3_libversion_number(void);
int sqlite3_libversion_number(void) {
	return c_out_3(901, 0, 0, 0);
}

//SQLITE_API int sqlite3_reset(sqlite3_stmt *pStmt);
int sqlite3_reset(void *pStmt) {
	return c_out_3(902, pStmt, 0, 0);
}

//SQLITE_API const char *sqlite3_sql(sqlite3_stmt *pStmt);
const char *sqlite3_sql(void *pStmt) {
	return c_out_3(903, pStmt, 0, 0);
}

//SQLITE_API int sqlite3_step(sqlite3_stmt*);
int sqlite3_step(void *stmt) {
	return c_out_3(904, stmt, 0, 0);
}

//SQLITE_API int sqlite3_exec(
//  sqlite3*,                                  /* An open database */
//  const char *sql,                           /* SQL to be evaluated */
//  int (*callback)(void*,int,char**,char**),  /* Callback function */
//  void *,                                    /* 1st argument to callback */
//  char **errmsg                              /* Error msg written here */
//);

int sqlite3_exec(void *db, const char *sql, __intcap_t cb, __intcap_t a0, char **errmsg) {
	return c_out_5(905, db, sql, cb, a0, errmsg);
}

//SQLITE_API void sqlite3_free(void*);
void sqlite3_free(void *ptr) {
	c_out_3(906, ptr, 0, 0);
}

//SQLITE_API int sqlite3_finalize(sqlite3_stmt *pStmt);
int sqlite3_finalize(void *pStmt) {
	return c_out_3(907, pStmt, 0, 0);
}

//SQLITE_API int sqlite3_column_count(sqlite3_stmt *pStmt);
int sqlite3_column_count(void *pStmt) {
	return c_out_3(908, pStmt, 0, 0);
}

//SQLITE_API int sqlite3_db_release_memory(sqlite3*);
int sqlite3_db_release_memory(void *db) {
	return c_out_3(909, db, 0, 0);
}

//SQLITE_API int sqlite3_close(sqlite3*);
int sqlite3_close(void *db) {
	return c_out_3(910, db, 0, 0);
}

//SQLITE_API const char *sqlite3_errmsg(sqlite3*);
const char *sqlite3_errmsg(void *db) {
	return c_out_3(911, db, 0, 0);
}

//SQLITE_API int sqlite3_strglob(const char *zGlob, const char *zStr);
int sqlite3_strglob(const char *zGlob, const char *zStr) {
	return c_out_3(912, zGlob, zStr, 0);
}

//SQLITE_API const char *sqlite3_libversion(void);
const char *sqlite3_libversion(void) {
	return c_out_3(913, 0, 0, 0);
}

//SQLITE_API int sqlite3_stricmp(const char *, const char *);
int sqlite3_stricmp(const char *a, const char *b) {
	return c_out_3(914, a, b, 0);
}

//SQLITE_API const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
const unsigned char *sqlite3_column_text(void *a, int iCol) {
	return c_out_3(915, a, iCol, 0);
}

//SQLITE_API int sqlite3_initialize(void);
int sqlite3_initialize(void) {
	return c_out_3(916, 0, 0, 0);
}

//SQLITE_API const char *sqlite3_sourceid(void);
const char *sqlite3_sourceid(void) {
	const char *ret = c_out_3(917, 0, 0, 0);
	return ret;
}

//SQLITE_API void sqlite3_result_int64(sqlite3_context*, sqlite3_int64);
void sqlite3_result_int64(void *ctx, long a) {
	c_out_3(918, ctx, a, 0);
}

//SQLITE_API int sqlite3_status(int op, int *pCurrent, int *pHighwater, int resetFlag);
int sqlite3_status(int op, int *pCurrent, int *pHighwater, int resetFlag) {
	return c_out_5(919, op, pCurrent, pHighwater, resetFlag, 0);
}

//SQLITE_API int sqlite3_db_status(sqlite3*, int op, int *pCur, int *pHiwtr, int resetFlg);
int sqlite3_db_status(void *db, int op, int *pCur, int *pHiwtr, int resetFlg) {
	return c_out_5(920, db, op, pCur, pHiwtr, resetFlg);
}

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
int sqlite3_create_function(void *db, char *name, int n, int e, void *pApp, void *sF, void *xS, void *xFi) {
	return c_out_7(921, db, name, n, pApp, sF, xS, xFi);
}


//SQLITE_API int sqlite3_prepare_v2(
//  sqlite3 *db,            /* Database handle */
//  const char *zSql,       /* SQL statement, UTF-8 encoded */
//  int nByte,              /* Maximum length of zSql in bytes. */
//  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
//  const char **pzTail     /* OUT: Pointer to unused portion of zSql */
//);

int sqlite3_prepare_v2(void *db, char *zSql, int nByte, void **ppStmt, char **pzTail) {
	return c_out_5(922, db, zSql, nByte, ppStmt, pzTail);
}


//SQLITE_API int sqlite3_open(
//  const char *filename,   /* Database filename (UTF-8) */
//  sqlite3 **ppDb          /* OUT: SQLite db handle */
//);

int sqlite3_open(const char *fn, void **ppDb) {
	return c_out_3(923, fn, ppDb, 0);
}

//SQLITE_API int sqlite3_config(int);
int sqlite3_config(int a) {
	return c_out_3(924, a, 0, 0);
}

//SQLITE_API int sqlite3_config2(int, int);
int sqlite3_config2(int a, int b) {
	return c_out_3(925, a, b, 0);
}


//SQLITE_API int sqlite3_config(int, ...);
int sqlite3_config3(int a, int b, int c) {
	return c_out_3(926, a, b, c);
}


//SQLITE_API int sqlite3_config4(int, void *pHeap, int nHeap, int mnHeap);
int sqlite3_config4(int a, void *pHeap, int nHeap, int mnHeap) {
	return c_out_5(927, a, pHeap, nHeap, mnHeap, 0);
}


//SQLITE_API int sqlite3_db_config(sqlite3*, int op, ...);
//    rc = sqlite3_db_config(g.db, SQLITE_DBCONFIG_LOOKASIDE, pLook, szLook,nLook);
int sqlite3_db_config(void *db, int op, void *plook, int szlook, int nlook) {
	return c_out_5(928, db, op, plook, szlook, nlook);
}

//SQLITE_API int sqlite3_bind_text(sqlite3_stmt*,int,const char*,int,void(*)(void*));
int sqlite3_bind_text(void *stmt,int a,const char *b,int c, void *d) {
	return c_out_5(929, stmt, a, b, c, d);
}

//SQLITE_API int sqlite3_bind_int(sqlite3_stmt*, int, int);
int sqlite3_bind_int(void *stmt, int a, int b) {
	return c_out_3(930, stmt, a, b);
}

//SQLITE_API int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
int sqlite3_bind_int64(void *stmt, int a, long b) {
	return c_out_3(931, stmt, a, b);
}

//SQLITE_API char *sqlite3_vmprintf(const char*, va_list);
char *sqlite3_vmprintf(const char *str, va_list va) {
	return c_out_3(932, str, va, 0);
}

//SQLITE_API char *sqlite3_snprintf(int,char*,const char*, ...);
char *sqlite3_snprintf(int a, char *b, const char *c) {
	return c_out_3(933, a, b, c);
}

//SQLITE_API char *sqlite3_snprintf(int,char*,const char*, ...);
char *sqlite3_snprintf4(int a, char *b, const char *c, const char *d) {
	return c_out_5(934, a, b, c, d, 0);
}



