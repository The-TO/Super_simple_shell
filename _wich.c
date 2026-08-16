#include"SSM.h"

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