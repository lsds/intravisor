#include <stdio.h>
#include <string.h>

// sscanf eventually calls fscanf where most of the tests are done
// this is just to test the intermediary functions
int main (int argc, char *argv[])
{
    const char* input = "this is 12";
    const char* format = "%s %*s %lld";

    char string[10] = {'\0'};
    long long big_int = 0;

    int return_value = 0;

    if (sscanf(input,format,string,&big_int) != 2) return_value |= 1;
    if (strcmp(string,"this")) return_value |= 2;
    if (big_int != 12) return_value |= 4;

    return return_value;
}
