#include <net/if.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    struct if_nameindex *interfaces = if_nameindex();
    if(interfaces == NULL)
    {
        perror("Error: if_nameindex failed to retrive network interfaces.\n");
        return 1;
    }

    int i = 0;
    while(interfaces[i].if_name != NULL)
    {
        i++;
    }

    if_freenameindex(interfaces);
    return 0;
}
