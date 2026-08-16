#include "SSM.h"

int main(void)
{
    char *chemin_path, *directory;

    chemin_path = _getenv("PATH");
    directory = strtok(chemin_path, ":");
    while (directory)
    {
        printf("%s\n", directory);
        directory = strtok(NULL, ":");
    }
    return(0);
}