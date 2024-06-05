#include <string.h>
#include <libintl.h>

int main(int argc, char **argv)
{
    const char *domain = "morello-project.org";

    if(strcmp(domain, textdomain(domain)) != 0) return 1;
    if(strcmp(domain, textdomain(NULL)) != 0) return 2;

    return 0;
}
