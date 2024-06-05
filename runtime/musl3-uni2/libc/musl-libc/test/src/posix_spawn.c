#include <spawn.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "temp_file_helpers.h"

#define CHECK_LAST_CALL(st, fun, rc) ({ if (st != 0) { perror(fun); return rc; } })

extern char **environ;

int child()
{
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return 21;
    /* Path is set in posix_spawn to be "/" */
    if (strcmp(cwd, "/") != 0)
        return 22;
    /* printf should be redirected to output specified by fileactions.*/
    printf("success\n");

    return 0;
}

int parent(int testCase)
{
    pid_t pid;
    int directoryfd;
    int status;
    short flags = 0;
    pid_t pgroup = 0;

    /* Get absolute path to executable to spawn child */
    char path[4096];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1) {
        perror("readlink");
        return 21;
    }
    path[len] = '\0';
    char *args[3] = {path, "1", 0};

    posix_spawnattr_t spawnattr;
    posix_spawn_file_actions_t fileactions;
    sigset_t mask;

    status = posix_spawnattr_init(&spawnattr);
    CHECK_LAST_CALL(status, "posix_spawnattr_init", 1);

    status = posix_spawn_file_actions_init(&fileactions);
    CHECK_LAST_CALL(status, "posix_spawn_file_actions_init", 2);

    status = posix_spawnattr_setsigmask(&spawnattr, &mask);
    CHECK_LAST_CALL(status, "posix_spawnattr_setsigmask", 3);

    status = posix_spawnattr_getsigmask(&spawnattr, &mask);
    CHECK_LAST_CALL(status, "posix_spawnattr_getsigmask", 4);

    status = posix_spawnattr_setsigdefault(&spawnattr, &mask);
    CHECK_LAST_CALL(status, "posix_spawnattr_setsigdefault", 5);

    status = posix_spawnattr_getsigdefault(&spawnattr, &mask);
    CHECK_LAST_CALL(status, "posix_spawnattr_getsigdefault", 6);

    switch (testCase)
    {
    case 1:
        status = posix_spawn_file_actions_addchdir_np(&fileactions, "/");
        CHECK_LAST_CALL(status, "posix_spawn_file_actions_addchdir_np", 7);
        break;
    case 2:
        directoryfd = open("/", O_RDONLY);
        status = posix_spawn_file_actions_addfchdir_np(&fileactions, directoryfd);
        CHECK_LAST_CALL(status, "posix_spawn_file_actions_addfchdir_np", 7);
        break;
    default:
        perror("Unknown test case.\n");
        return 42;
    }

    char filename_buffer[PATH_MAX];
    if (0 != create_temp_directory("morello-musl-tests-posix/", &filename_buffer[0]))
        return 20;
    char* filename = strncat(&filename_buffer[0], "posix-spawn-test.txt", PATH_MAX);

    int fp = open(filename, O_CREAT, 0666);
    if (fp < 0)
    {
        perror("Failed to create temporary file.");
        return 8;
    }
    close(fp);

    status = posix_spawn_file_actions_addopen(&fileactions, STDOUT_FILENO, filename, O_RDWR, 0666);
    CHECK_LAST_CALL(status, "posix_spawn_file_actions_addopen", 9);

    int fd = 0;
    status = posix_spawn_file_actions_adddup2(&fileactions, STDOUT_FILENO, fd);
    CHECK_LAST_CALL(status, "posix_spawn_file_actions_adddup2", 10);

    status = posix_spawn_file_actions_addclose(&fileactions, fd);
    CHECK_LAST_CALL(status, "posix_spawn_file_actions_addclose", 11);

    status = posix_spawnattr_setflags(&spawnattr, 0);
    CHECK_LAST_CALL(status, "posix_spawnattr_setflags", 12);

    status = posix_spawnattr_getflags(&spawnattr, &flags);
    CHECK_LAST_CALL(status, "posix_spawnattr_getflags", 13);
    if (flags != 0) CHECK_LAST_CALL(flags, "Invalid flags from posix_spawnattr_getflags", 14);

    status = posix_spawnattr_setpgroup(&spawnattr, 350);
    CHECK_LAST_CALL(status, "posix_spawnattr_setpgroup", 15);

    status = posix_spawnattr_getpgroup(&spawnattr, &pgroup);
    CHECK_LAST_CALL(status, "posix_spawnattr_getpgroup", 16);
    if (pgroup != 350)
    {
        perror("Pgroup was not set correctly");
        return 17;
    }

    status = posix_spawn(&pid, args[0], &fileactions, &spawnattr, args, NULL);
    if (status != 0)
    {
        perror(strerror(status));
        return 18;
    }

    waitpid(pid, &status, -1);
    CHECK_LAST_CALL(status, "Child process testcase failed", status);
    killpg(350, SIGKILL);

    status = posix_spawnattr_destroy(&spawnattr);
    CHECK_LAST_CALL(status, "posix_spawnattr_destroy", 19);

    status = posix_spawn_file_actions_destroy(&fileactions);
    CHECK_LAST_CALL(status, "posix_spawn_file_actions_destroy", 20);

    return 0;
}

int main(int argc, char **argv)
{
    switch (argv[1][0])
    {
    case '1': // Child process (not a standalone test due to unecessary path complications)
        return child();
    case '2': // Parent with path
        return parent(1);
    case '3': // Parent with file descriptor
        return parent(2);
    }
}
