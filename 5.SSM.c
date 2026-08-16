#include "SSM.h"

int main (void)
{
    int status;
    pid_t le_pid;
    char *line = NULL, **cmd_argv, *chemin_trouve;
    size_t len = 0;
    extern char **environ;

    while (1)
    {
        printf("#cisfun$ ");
        if (getline(&line, &len, stdin) == -1)
        {
            free(line);
            return(-1);
        }
        else
        {
            printf("%s", line);
            line[strlen(line) - 1] = '\0'; // enleve le \n du getline
        }
        cmd_argv = LeDecoupeur(line);
        le_pid = fork();
        if (le_pid == 0)
        {
            chemin_trouve = _which(cmd_argv[0]);
            if (!chemin_trouve)
            {
                exit(1);
            }
            execve(chemin_trouve, cmd_argv, environ);
            perror("Error");
            exit(1);
        }
        else if (le_pid > 0)
        {
            wait(&status);
        }
        else
        {
            perror("Error:");
        }
    }
    return(0);
}