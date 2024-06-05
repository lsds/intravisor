#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <aio.h>
#include "temp_file_helpers.h"

char DIR_PATH[4096];

int main(int argc, char **argv)
{
    struct aiocb **list;
    struct aiocb readcb;
    struct aiocb writecb;
    char filename_buffer[PATH_MAX];
    char readbuf[4096];
    char writebuf[4096];
    int fd, ret;

    list = malloc(10 * sizeof(struct aiocb *));

    if (create_temp_directory("morello-musl-tests-aio/", DIR_PATH) != 0)
    {
        fprintf(stderr, "Failed to create temporary directory.\n");
        return -1;
    }

    char *filename = create_temp_file(DIR_PATH, "aioXXXXXX", filename_buffer);
    if(strcmp(filename, "") == 0)
    {
        fprintf(stderr, "Failed to create temporary file.\n");
        return -2;
    }

    fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd < 0)
    {
        perror("Failed to create temporary file. Error:");
        return 1;
    }

    memset(&writecb, 0, sizeof(struct aiocb));
    memset(&readcb, 0, sizeof(struct aiocb));

    memset(readbuf, 0, 4096);
    memset(writebuf, 0, 4096);

    writecb.aio_fildes = fd;
    writecb.aio_buf = &writebuf;
    writecb.aio_nbytes = 4096;
    writecb.aio_offset = 0;
    writecb.aio_sigevent.sigev_notify = SIGEV_NONE;

    readcb.aio_fildes = fd;
    readcb.aio_buf = &readbuf;
    readcb.aio_nbytes = 4096;
    readcb.aio_offset = 0;
    readcb.aio_sigevent.sigev_notify = SIGEV_NONE;

    strcpy(writebuf, "Hello World");

    ret = aio_write(&writecb);
    if(ret < 0)
    {
        perror("Failed to submit asynchronous request to read from temporary file. Error:");
        return 2;
    }

    while(aio_error(&writecb) == EINPROGRESS);

    if((ret = aio_return(&writecb)) == -1)
    {
        perror("Failed to read from temporary file. Error:");
        return 3;
    }

    list[0] = &writecb;
    if((ret = lio_listio(LIO_WRITE, list, 1, NULL)) != 0)
    {
        perror("Failed to submit asynchronous request to read from temporary file. Error:");
        return 4;
    }
    if((ret = aio_cancel(fd, &writecb)) == -1)
    {
        perror("Failed to cancel asynchronous request. Error:");
        return 5;
    }

    // Reuse writecb as we only need it for file descriptor.
    ret = aio_fsync(O_SYNC, &writecb);
    if(ret != 0)
    {
        perror("Failed to force asynchronous request completion. Error:");
        return 6;
    }

    ret = aio_read(&readcb);
    if(ret < 0)
    {
        perror("Failed to submit asynchronous request to read from temporary file. Error:");
        return 7;
    }

    while(aio_error(&readcb) == EINPROGRESS);

    if((ret = aio_return(&readcb)) == -1)
    {
        perror("Failed to read from temporary file. Error:");
        return 8;
    }

    const struct aiocb * rcblist[1] = { &readcb };

    if((ret = aio_suspend(rcblist, 1, NULL)) != 0)
    {
        perror("Failed to suspend for asynchoronous request completion. Error:");
        return 9;
    }

    printf("%s\n", readbuf);
    close(fd);
    free(list);

    return 0;
}
