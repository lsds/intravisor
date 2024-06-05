
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

static inline int create_temp_directory(const char *name, char *directory_path)
{
    char tmp_path[PATH_MAX];

    strcpy(tmp_path, "/tmp/");

    if(getenv("USER") == NULL)
    {
        strcat(tmp_path, "morello-tests");
    }
    else
    {
        strcat(tmp_path, getenv("USER"));
    }

    // set up root dir in /tmp -- also inherently tests mkdir()
    if (mkdir(tmp_path, 0777) && errno != EEXIST)
        return -1;

    strcat(tmp_path, "/");
    strcat(tmp_path, name);

    // set up root dir in /tmp -- also inherently tests mkdir()
    if (mkdir(tmp_path, 0777) && errno != EEXIST)
        return -1;

    strncpy(directory_path, tmp_path, strlen(tmp_path) + 1);
    return 0;
}

static inline char *create_temp_file(const char *directory, const char *filename, char *buffer)
{
    strncpy(buffer, directory, PATH_MAX);
    strncat(buffer, filename, PATH_MAX);
    return mktemp(buffer);
}
