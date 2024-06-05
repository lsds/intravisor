#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = posix_openpt(O_RDWR | O_NOCTTY);
    if(fd < 0) return 1;
    if(unlockpt(fd)) return 2;
    if(!ptsname(fd)) return 3;

    return 0;
}
