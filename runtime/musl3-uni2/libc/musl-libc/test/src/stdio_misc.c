#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int test_perror();
int test_ctermid();
int test_fopencookie();
int test_setvbuf();
int test_setvbuf_stdout(int);
int test_getdelim();
int test_freopen();
int test_fmemopen();

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    switch(argv[1][0]) {
        case '0': // perror
            return test_perror();
        case '1': // ctermid
            return test_ctermid();
        case '2': // fopencookie
            return test_fopencookie();
        case '3': // setvbuf
            return test_setvbuf();
        case '4': // setvbuf, full buffered
            return test_setvbuf_stdout(_IOFBF);
        case '5': // setvbuf, line buffered
            return test_setvbuf_stdout(_IOLBF);
        case '6': // getdelim
            return test_getdelim();
        case '7': // freopen
            return test_freopen();
        case '8': // fmemopen, open_memstream
            return test_fmemopen();
    }

    return -1;
}

int test_fmemopen() {
    FILE *out, *in;
    const char sentence[] = "longer sentence to check buffer resizes to hold";
    char inbuf[100] = "initial data";
    char *outbuf;
    char rec;
    size_t sz;

    in = fmemopen(inbuf, 100, "r+");
    if (in == NULL) return 1;
    out = open_memstream(&outbuf, &sz);
    if (out == NULL) return 2;

    for (;;) {
        if (fscanf(in, "%c", &rec) <= 0) break;
        if (fprintf(out, "%c", rec) == -1) return 3;
    }
    if (fseek(in, 0, SEEK_SET)) return 4;
    if (fseek(out, 0, SEEK_SET)) return 4;
    if(strcmp(outbuf, "initial data")) return 5;
    // Check fmemopen writes and buffer sized correctly
    fprintf(in, "%s", sentence);
    if (fseek(in, 0, SEEK_SET)) return 4;
    for (;;) {
        if (fscanf(in, "%c", &rec) <= 0) break;
        if (fprintf(out, "%c", rec) == -1) return 3;
    }
    fclose(in);
    fclose(out);
    if (__builtin_cheri_length_get(outbuf) < sz) return 6;
    if (strcmp(outbuf, sentence)) return 7;
    free(outbuf);
    return 0;
}


int file_fgetpos(FILE *fp) {
    const char *ln0 = "hello world\n";
    const char *ln1 = "and goodbye\n";
    char *s;
    size_t len;
    fpos_t pos;

    printf("%s", ln0);
    // Store position before line
    if (fgetpos(fp, &pos)) return 2;
    printf("%s", ln1);
    // Restore position before line
    if (fsetpos(fp, &pos)) return 3;
    s = fgetln(fp, &len);
    if (strncmp(s, ln1, 12)) return 4;
    return 0;
}

int test_freopen() {
    FILE *fp = stdout;
    const char *filename = tmpnam(NULL);
    int r = 0;

    if ((fp=freopen(filename, "w+", fp)) == NULL)
        return 1;
    unlink(filename);
    r = file_fgetpos(fp);
    fclose(fp);
    return r;
}

int test_getdelim() {
    FILE* fp = tmpfile();
    if(!fp) return 1;

    if (fprintf(fp, "test|delimited|string") != 21) return 2;
    rewind(fp);

    char *str1 = NULL;
    size_t n = 0;
    if (getdelim(&str1, &n, '|', fp) != 5) return 3;
    if (strcmp("test|", str1)) return 4;

    char *str2 = malloc(16);
    n = 16;
    if (getdelim((char **) &str2, &n, '|', fp) != 10) return 5;
    if (strcmp("delimited|", str2)) return 6;

    return 0;
}

int test_setvbuf_stdout(int buf_type){
    int i;
    char buf[52] = "check iobuf";

    if ((setvbuf(stdout, buf+12, buf_type, 40))) return 1;
    fputs("abc", stdout);
    for (i=12;i<52;i++) {
        if(buf[i] == 'a') break;
    }
    if (strncmp(buf+i, "abc", 3)) return 2;
    puts("def");
    if (strncmp(buf+i, "abcdef", 6)) return 3;
    // Flush buffer
    puts("\n");
    if (buf_type == _IOFBF)
        fflush(stdout);

    if (!__builtin_cheri_tag_get(buf)) return 4;
    if (__builtin_cheri_length_get(buf) != 52) return 5;
    // Check preserved out of vbuf
    if (strncmp(buf, "check iobuf", 11)) return 6;
    return 0;
}

int test_setvbuf() {
    FILE* fp = tmpfile();
    if(!fp) return 1;

    if (setvbuf(fp, NULL, _IOFBF, 64)) return 2;
    while(fgetc(fp) != EOF); // read whole file

    if (fclose(fp)) return 3;

    return 0;
}

int test_perror() {
    char template[] = "testXXXXXX";
    char *filename = mktemp(template);

    // file should not exist and should throw error
    FILE *f = fopen(filename, "r");
    if (f) return 1;

    perror("Error");

    return 0;
}

int test_ctermid() {
    char termid[64];
    ctermid(termid);

    if (strncmp("/dev/tty", termid, strlen("/dev/tty"))) return 1;

    return 0;
}

int test_fopencookie() {
    // very simplified test, may need more in depth testing in future if issues arise

    cookie_io_functions_t io_funcs = (cookie_io_functions_t) {
        NULL, NULL,NULL, NULL
    };
    int testcookie = 4;

    FILE *f = fopencookie((void *) &testcookie, "r", io_funcs);
    if (!f) return 1;

    return 0;
}
