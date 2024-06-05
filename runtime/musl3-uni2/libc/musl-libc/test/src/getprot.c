#include <netdb.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    /* Protocols are defined in /etc/protocols */
    struct protoent *protocolname = getprotobyname("ip");
    if(protocolname == NULL)
    {
        perror("Error: getprotobyname failed to retrive protocol information.\n");
        return 1;
    }
    printf("%d\n", protocolname->p_proto);

    struct protoent *protocolnumber = getprotobynumber(0);
    if(protocolnumber == 0)
    {
        perror("Error: getprotobynumber failed to retrive protocol information.\n");
        return 2;
    }
    printf("%s\n", protocolnumber->p_name);

    struct protoent *protocolnext = getprotoent();
    if(protocolnext == NULL)
    {
        perror("Error: getprotent failed to retrive protocol information.\n");
        return 3;
    }
    printf("%s\n", protocolnumber->p_name);

    return 0;
}
