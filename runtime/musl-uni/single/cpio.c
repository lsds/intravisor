/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cpio.h"
#include <string.h>


#ifndef NULL
#define NULL ((void *)0)
#endif

/* Align 'n' up to the value 'align', which must be a power of two. */
static unsigned long align_up(unsigned long n, unsigned long align)
{
    return (n + align - 1) & (~(align - 1));
}

/* Parse an ASCII hex string into an integer. */
static unsigned long parse_hex_str(char *s, unsigned int max_len)
{
    unsigned long r = 0;
    unsigned long i;

    for (i = 0; i < max_len; i++) {
        r *= 16;
        if (s[i] >= '0' && s[i] <= '9') {
            r += s[i] - '0';
        }  else if (s[i] >= 'a' && s[i] <= 'f') {
            r += s[i] - 'a' + 10;
        }  else if (s[i] >= 'A' && s[i] <= 'F') {
            r += s[i] - 'A' + 10;
        } else {
            return r;
        }
        continue;
    }
    return r;
}

/*
 * Compare up to 'n' characters in a string.
 *
 * We re-implement the wheel to avoid dependencies on 'libc', required for
 * certain environments that are particularly impoverished.
 */
static int cpio_strncmp(const char *a, const char *b, unsigned long n)
{
    unsigned long i;
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return a[i] - b[i];
        }
        if (a[i] == 0) {
            return 0;
        }
    }
    return 0;
}

/**
 * This is an implementation of string copy because, cpi doesn't want to
 * use string.h.
 */
static char* cpio_strcpy(char *to, const char *from) {
    char *save = to;
    while (*from != 0) {
        *to = *from;
        to++;
        from++;
    }
    return save;
}


static unsigned int cpio_strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s) {}
    return (s - str);
}



/*
 * Parse the header of the given CPIO entry.
 *
 * Return -1 if the header is not valid, 1 if it is EOF.
 */
int cpio_parse_header(struct cpio_header *archive,
        const char **filename, unsigned long *_filesize, intptr_t **data,
        struct cpio_header **next)
{
    unsigned long filesize;
    /* Ensure magic header exists. */
    if (cpio_strncmp(archive->c_magic, CPIO_HEADER_MAGIC,
                sizeof(archive->c_magic)) != 0) {
        return -1;
    }
    /* Get filename and file size. */
    filesize = parse_hex_str(archive->c_filesize, sizeof(archive->c_filesize));
    *filename = ((char *)archive) + sizeof(struct cpio_header);

    /* Ensure filename is not the trailer indicating EOF. */
    if (cpio_strncmp(*filename, CPIO_FOOTER_MAGIC, sizeof(CPIO_FOOTER_MAGIC)) == 0)
        return 1;

    /* Find offset to data. */
    unsigned long filename_length = parse_hex_str(archive->c_namesize,
            sizeof(archive->c_namesize));
#ifndef __CHERI_PURE_CAPABILITY__
    *data = (intptr_t *)align_up((unsigned long)(archive)
            + sizeof(struct cpio_header) + filename_length, CPIO_ALIGNMENT);
    *next = (struct cpio_header *)align_up(((unsigned long)*data) + filesize, CPIO_ALIGNMENT);
#else
	unsigned long al = align_up((unsigned long)(archive) + sizeof(struct cpio_header) + filename_length, CPIO_ALIGNMENT) - (unsigned long)archive;
	*data = __builtin_cheri_offset_increment(archive, al);

	unsigned long nl = align_up( __builtin_cheri_address_get( *data) + filesize, CPIO_ALIGNMENT) - (unsigned long) *data;
	*next = __builtin_cheri_offset_increment(*data, nl);
#endif
    if(_filesize){
        *_filesize = filesize;
    }
    return 0;
}

/*
 * Get the location of the data in the n'th entry in the given archive file.
 *
 * We also return a pointer to the name of the file (not NUL terminated).
 *
 * Return NULL if the n'th entry doesn't exist.
 *
 * Runs in O(n) time.
 */
intptr_t *cpio_get_entry(intptr_t *archive, int n, const char **name, unsigned long *size)
{
    int i;
    struct cpio_header *header = (struct cpio_header *) archive;
    intptr_t *result = NULL;

    /* Find n'th entry. */
    for (i = 0; i <= n; i++) {
        struct cpio_header *next;
        int error = cpio_parse_header(header, name, size, &result, &next);
        if (error)
            return NULL;
        header = next;
    }

    return result;
}

/*
 * Find the location and size of the file named "name" in the given 'cpio'
 * archive.
 *
 * Return NULL if the entry doesn't exist.
 *
 * Runs in O(n) time.
 */
intptr_t *cpio_get_file(intptr_t *archive, const char *name, unsigned long *size)
{
    struct cpio_header *header = (struct cpio_header *) archive;

    /* Find n'th entry. */
    while (1) {
        struct cpio_header *next;
        intptr_t *result;
        const char *current_filename;

        int error = cpio_parse_header(header, &current_filename,
                size, &result, &next);
        if (error)
            return NULL;
        if (cpio_strncmp(current_filename, name, -1) == 0)
            return result;

        header = next;
    }
}

int cpio_info(intptr_t *archive, struct cpio_info *info) {
    struct cpio_header *header, *next;
    const char *current_filename;
    intptr_t *result;
    int error;
    unsigned long size, current_path_sz;

    if (info == NULL) return 1;
    info->file_count = 0;
    info->max_path_sz = 0;

    header = (struct cpio_header *) archive;

    while (1) {
        error = cpio_parse_header(header, &current_filename, &size,
                &result, &next);
        if (error == -1) {
            return error;
        } else if (error == 1) {
            /* EOF */
            return 0;
        }
        info->file_count++;
        header = next;

        // Check if this is the maximum file path size.
        current_path_sz = cpio_strlen(current_filename);
        if (current_path_sz > info->max_path_sz) {
            info->max_path_sz = current_path_sz;    
        }
    }

    return 0;
}


void cpio_ls(intptr_t *archive, char **buf, unsigned long buf_len) {
    const char *current_filename;
    struct cpio_header *header, *next;
    intptr_t *result;
    int error;
    unsigned long i, size;

    header = (struct cpio_header *) archive;

    for (i = 0; i < buf_len; i++) {
        error = cpio_parse_header(header, &current_filename, &size,
                &result, &next);
        // Break on an error or nothing left to read.

        if (error) break;
        cpio_strcpy(buf[i],  current_filename);
        header = next;
    }
}

void copy_cpio(intptr_t *archive) {
    const char *current_filename;
    struct cpio_header *header, *next;
    intptr_t *result;
    int error;
    unsigned long i, size;

    header = (struct cpio_header *) archive;
    while(1) {
        error = cpio_parse_header(header, &current_filename, &size,
                &result, &next);
        // Break on an error or nothing left to read.

        if (error) break;
        header = next;

//        cpio_strcpy(buf[i],  current_filename);
	printf("%s, %x (size %d)\n", current_filename, (int) cpio_get_file(archive, current_filename, &size), (int)size);
		if(current_filename[0]=='.' && current_filename[1]=='\0')
//	if(current_filename[0]=='.' )
	    continue;

	char path[1024];
//	sprintf(path,"/%s", current_filename);
	path[0]='/';
	memcpy(&path[1], current_filename, strlen(current_filename) + 1);

	if(size==0) {
	    printf("creating dir '%s', ret = %d\n",path, mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH));
	    continue;
	}

	int fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0644);

	if(fd < 0) {
	    printf("cant open file %s, die (fd = %d)\n", path, fd);
	    while(1);
	}
	intptr_t *ptr = cpio_get_file(archive, current_filename, &size);

//	printf("ptr = %x %x tag = %d base = %x\n", (int) __builtin_cheri_length_get(ptr), (int) ptr, __builtin_cheri_tag_get(ptr), (int) __builtin_cheri_base_get(ptr));
	int wr = write(fd, ptr, size);
	if(wr !=size) {
	    printf("corrupted write %d%d\n", wr,(int)size);
	}

	printf("writing file '%s', ret = %d\n", path, wr);
	close(fd);
    }
}
