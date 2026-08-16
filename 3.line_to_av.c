#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SSM.h"

char** LeDecoupeur(char *str)
{
    int i = 0, j = 0, k = 0; // compteur pour parcourir des trucs
    char *copie, *mot, **array; // resultat de chaque appel malloc + tableau de chaine 

    if (!str)
    {
     return(0);
    }
    copie = malloc(strlen(str) + 1);
    while (str[k] != '\0')
    {
        copie[k] = str[k];
        k++;
    }
    copie[k] = str[k];

    mot = strtok(copie, " ");
    while (mot)
    {
        i++;
        mot = strtok(NULL, " ");
    }
    free(copie);
    array = malloc((i + 1) * sizeof(char *));
    if (!array)
    {
        free(array);
        return(NULL);
    }
    mot = strtok (str, " ");
    while (mot)
    {
        array[j] = mot;
        j++;
        mot = strtok(NULL, " ");
        
    }
    array[j] = NULL;

    return(array);
}
int main(void)
{
    char str[] = "ls -l /tmp";
    char **result;
    int i = 0;

    result = LeDecoupeur(str);
    while (result[i] != NULL)
    {
        printf("%s\n", result[i]);
        i++;
    }
    free(result);
    return(0);
}