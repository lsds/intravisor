#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    // make sure the env variable used are not already set
    if(getenv("DUMMY_NAME1") || getenv("DUMMY_NAME2") || getenv("DUMMY_NAME3")) return 1;

    setenv("DUMMY_NAME1", "dummy1", 0);
    setenv("DUMMY_NAME2", "dummy2", 1);
    setenv("DUMMY_NAME3", "dummy3", 0);

    // make sure that the var are set properly
    char* tmp = getenv("DUMMY_NAME1");
    if (!tmp || strcmp(tmp,"dummy1")) return 2;
    tmp = getenv("DUMMY_NAME2");
    if (!tmp || strcmp(tmp,"dummy2")) return 2;
    tmp = getenv("DUMMY_NAME3");
    if (!tmp || strcmp(tmp,"dummy3")) return 2;

    clearenv();

    // check that the var have been deleted
    if(getenv("DUMMY_NAME1") || getenv("DUMMY_NAME2") || getenv("DUMMY_NAME3")) return 3;

    return 0;
}
