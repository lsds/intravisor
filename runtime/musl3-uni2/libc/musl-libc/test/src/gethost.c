#include <netdb.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    struct hostent *hostname = gethostbyname("localhost");
    if(hostname == NULL)
    {
        perror("Error: gethostbyname failed to retrive localhost information.\n");
        return 1;
    }
    printf("%s\n", hostname->h_name);

    struct hostent *hostaddr = gethostbyaddr(hostname->h_addr_list[0], hostname->h_length, hostname->h_addrtype);
    if(hostaddr == NULL)
    {
        perror("Error: gethostbyaddr failed to retrive localhost information.\n");
        return 3;
    }
    printf("%s\n", hostaddr->h_name);

    struct hostent *nullhostname = gethostbyname("");
    if(nullhostname != NULL)
    {
        perror("Error: gethostbyname returned unexpected information.\n");
        return 2;
    }

   return 0;
}
