#include <sys/prctl.h>
#include <string.h>

int main() {
    const char new_name[16] = "FancyThreadName";
    char current_name[16] = { 0 };
    if (prctl(PR_SET_NAME, &new_name[0])) return 1;
    if (prctl(PR_GET_NAME, &current_name[0])) return 2;
    if (0 != strcmp(&new_name[0], &current_name[0])) return 3;
    return 0;
}
