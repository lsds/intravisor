#include <dirent.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int test_scandir();
int test_alphasort();
int test_opendir_closedir();
int test_fdopendir_dirfd();
int test_readdir_readdir_r();
int test_rewinddir_seekdir_telldir();

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    //umask(0);

    // set up root dir in /tmp
    //if (mkdir(TMP_DIR, 0777) && errno != EEXIST) return -2;

    switch(argv[1][0]) {
        case '0':
            return test_scandir();
        case '1':
            return test_opendir_closedir();
        case '2':
            return test_fdopendir_dirfd();
        case '3':
            return test_readdir_readdir_r();
        case '4':
            return test_rewinddir_seekdir_telldir();
    }

    return -1;
}

int filter(const struct dirent *dirent) {
    return strlen(dirent->d_name) > 0;
}

int test_scandir() {
    struct dirent **namelist;

    int n = scandir("/proc/self", &namelist, filter, alphasort);
    
    if (n <= 0) return 1;

    return 0;
}

int test_opendir_closedir() {
    DIR *d = opendir("/proc/self/");
    if (!d) return 1;

    if (closedir(d)) return 2;

    return 0;
}

int test_fdopendir_dirfd() {
    int fd = open("/tmp", O_RDONLY);
    if (fd < 0) return 1;

    DIR *d = fdopendir(fd);
    if (!d) return 2;

    int fd2 = dirfd(d);
    if (fd != fd2) return 3;
    
    if (close(fd)) return 4;

    return 0;
}

int test_readdir_readdir_r() {
    DIR *d = opendir("/proc/self/");
    if (!d) return 1;

    // readdir
    if (!readdir(d)) return 2;

    // readdir_r
    struct dirent dirent = (struct dirent) {};
    struct dirent *result;
    readdir_r(d, &dirent, &result);
    if (&dirent != result) return 3;

    return 0;
}

int test_rewinddir_seekdir_telldir() {
    DIR *d = opendir("/proc/self/");
    if (telldir(d) != 0) return 1;

    seekdir(d, 2);
    if (telldir(d) != 2) return 2;

    rewinddir(d);
    if (telldir(d) != 0) return 3;

    return 0;
}
