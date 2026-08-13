#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int main(void)
{
    int status;
    int i = 0;
    pid_t mon_pid;
    extern char **environ;

    char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
    while(i < 5)
    {
        mon_pid = fork();
        if (mon_pid == 0)
        {
            execve(argv[0], argv, environ);
            exit(1);
        }
        else if (mon_pid > 0)
        {
            wait(&status);
            i++;
        }
        else
        {
            perror("Error:");
            i++;
        }
    }
    return(0);
}