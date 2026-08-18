#include "SSH.h"

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
