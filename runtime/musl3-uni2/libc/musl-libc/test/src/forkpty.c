#include <pty.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int m;
    char name[64];
    int res = 0;

    if (argc > 1)
    {
        printf("this is child process\n");
        return 0;
    }

    pid_t pid = forkpty(&m, name, NULL, NULL);
    char *args[] = { argv[0], "child", NULL };

    switch (pid)
    {
        case 0: // child
            execvp(argv[0], args);
            perror("execvp");
            break;
        case -1: // error
            perror("forkpty");
            res = 1;
            break;
        default: { // parent
            printf("parent: created child process %d\n", pid);
            printf("parent: name = %s\n", name);
            int status;
            waitpid(pid, &status, 0);
            res = WEXITSTATUS(status);
            printf("parent: child exited with status %d\n", res);
            char buffer[64];
            memset(buffer, 0, sizeof(buffer));
            size_t n = read(m, buffer, sizeof(buffer));
            printf("parent: read %zu bytes from %d\n", n, m);
            printf("parent: output = %s", buffer);

            if(strcmp(buffer, "this is child process") == 0)
            {
                res = 0;
            }

            close(m);
            break;
        }
    }
    return res;
}
