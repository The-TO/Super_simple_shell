#include <stdio.h>

int main(int ac, char **av, char **env)
{
    extern char **environ;
    
    (void)ac;
    (void)av;
    printf("env = %p\n", (void*)env);
    printf("environ = %p\n", (void*)environ);
    return (0);
}