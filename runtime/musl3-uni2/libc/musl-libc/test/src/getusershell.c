#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *shell;
    char *buffer = malloc(4096);
    FILE *shellFile = fopen("/etc/shells", "r");

    if(shellFile)
    {
        while(fgets(buffer, 4096, shellFile) != NULL)
        {
            /* Remove trailing new line character from fgets. */
            buffer[strcspn(buffer, "\n")] = 0;

            shell = getusershell();

            if(shell == NULL) return 1;

            /* getusershell returned something not found in /etc/shells. */
            if(strcmp(buffer, shell) != 0)
            {
                fprintf(stderr, "getusershell returned an unexpected result.\n");
                return 2;
            }
        }

        fclose(shellFile);
    }
    else
    {
        shell = getusershell();
        if(strcmp(shell, "/bin/sh") != 0) return 3;

        shell = getusershell();
        if(strcmp(shell, "/bin/csh") != 0) return 4;
    }

    free(buffer);

    return 0;
}
