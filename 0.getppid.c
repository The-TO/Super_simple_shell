#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
    pid_t my_pid;

    my_pid = getppid();
    printf ("%u \n", my_pid);
    return(0);
}
