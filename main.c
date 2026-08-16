#include "SSM.h"

int main(void)
{
    char *result;

    result = _which("ls");
    if (result)
        printf("%s\n", result);
    else
        printf("not found\n");
    return (0);
}