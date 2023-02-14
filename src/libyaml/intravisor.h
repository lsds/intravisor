/*
 * Example application data structures.
 */

#include <stdbool.h>

struct isol_s {
    long base;
    long size;
    long begin;
    long end;
};

struct cvm {
    struct cvm *next;
    char *name;
    char *disk;
    char *runtime;
    char *net;
    char *args;
    char *cb_in;
    char *cb_out;
	struct isol_s isol;
	int wait;
};

struct capfile {
    struct capfile *next;
    char *name;
    char *data;
    long size;
	long addr;
};

/* yaml_* functions return 1 on success and 0 on failure. */
enum status {
    SUCCESS = 1,
    FAILURE = 0
};

/* Our example parser states. */
enum state {
    STATE_START,    /* start state */
    STATE_STREAM,   /* start/end stream */
    STATE_DOCUMENT, /* start/end document */
    STATE_SECTION,  /* top level */

    STATE_FLIST,    /* cvm list */
    STATE_FVALUES,  /* cvm key-value pairs */
    STATE_FKEY,     /* cvm key */
    STATE_FNAME,    /* cvm name value */
    STATE_FDISK,    /* cvm disk value */
    STATE_FRUNTIME,    /* cvm runtime value */
    STATE_FNET,    /* cvm net value */
    STATE_FARGS,    /* cvm args value */
    STATE_FCALLBACK_IN,   /* cvm end value */
    STATE_FCALLBACK_OUT,   /* cvm end value */
    STATE_FWAIT,    /* cvm net value */
///
    STATE_ILIST,    /* cvm list */
    STATE_IVALUES,  /* cvm key-value pairs */
    STATE_IKEY,     /* cvm key */
    STATE_IBASE,   /* cvm base value */
    STATE_ISIZE,   /* cvm size value */
    STATE_IBEGIN,   /* cvm begin value */
    STATE_IEND,   /* cvm end value */
////

    STATE_CLIST,    /* capfiles list */
    STATE_CVALUES,  /* capfiles key-value pairs */
    STATE_CKEY,     /* capfile key */
    STATE_CNAME,    /* capfile name value */
    STATE_CDATA,    /* capfile data value */
    STATE_CSIZE,   /* capfile size value */
    STATE_CADDR,   /* capfile addr value */

    STATE_STOP      /* end state */
};


/* Our application parser state data. */
struct parser_state {
    enum state state;      /* The current parse state */
    struct cvm f;        /* cvm data elements. */
    struct cvm *flist;   /* List of 'cvm' objects. */

    struct capfile c;        /* Capfile data elements. */
    struct capfile *clist;   /* List of 'cvm' objects. */
};


void bail(const char *msg);
void *bail_alloc(size_t size);
char *bail_strdup(const char *s);

void add_cvm(struct cvm **cvms, char *name, char *disk, char *runtime, char *net, char *args, long base, long size, long begin, long end, char *cb_out, char *cb_in, int wait);
void add_capfile(struct capfile **capfiles, char *name, char *data, long size, long addr);

void destroy_cvms(struct cvm **cvms);
void destroy_capfiless(struct capfile **capfiles);
