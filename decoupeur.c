#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SSS.h"

char** LeDecoupeur(char *str)
{
    int i = 0, j = 0, k = 0;
    char *copie, *mot, **array;  

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
char *_getenv(const char *name)
{
    int i = 0;
    extern char **environ;

    if (name == NULL)
    {
        return(NULL);
    }

    while (environ[i])
    {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=')
        {
            return (environ[i] + strlen(name) + 1);
        }
        i++;
    }
    return(NULL);
}
char *build_path(char *dossier, char *nom_fichier)
{
    int i = 0, j = 0;
    char *chemin_complet;

    chemin_complet = malloc(strlen(dossier) + strlen(nom_fichier) + 2);
    if(!chemin_complet)
    {
        return (NULL);
    }
    chemin_complet[0] = '\0';
    while(dossier[i] != '\0')
    {
        chemin_complet[i] = dossier[i];
        i++;
    }
    chemin_complet[i] = '/';
    i++;
    while(nom_fichier[j] != '\0')
    {
        chemin_complet[i] = nom_fichier[j];
        i++;
        j++;
    }
    chemin_complet[i] = nom_fichier[j];
    return (chemin_complet);
}
char *_which(char *filename)
{
    char *chemin_path, *dossier, *chemin_complet;
    struct stat st;

    chemin_path = _getenv("PATH");
    dossier = strtok(chemin_path, ":");
    while (dossier)
    {
        chemin_complet = build_path(dossier, filename);
        if (stat(chemin_complet, &st) == 0)
        {
         return(chemin_complet);
        }
        else
        {
            free(chemin_complet);
            dossier = strtok(NULL, ":");
        }
    }
    
    return (NULL);
}
