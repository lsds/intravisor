#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    struct addrinfo *result;
    int err = getaddrinfo("localhost", NULL, NULL, &result);

    if(err != 0)
    {
        printf("Failed addrinfo did not retrive address information.");
        return 1;
    }

    return 0;
}
