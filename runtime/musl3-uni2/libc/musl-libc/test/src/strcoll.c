#include <string.h>
#include <locale.h>

int main(int argc, char **argv) {
    setlocale(LC_ALL, "C.UTF-8");

    char* empty_string = "";
    char* low_string = "big";
    char* high_string =   "bigger";

    // The input parameters are const so there is no corruption of
    // capabilities possible. We only test to see if it runs.
    if ( strcoll(empty_string,low_string) >= 0) return 1;
    if ( strcoll(high_string,low_string) <= 0) return 2;
    if ( strcoll(low_string,low_string) != 0) return 3;

    return 0;
}
