#include "SSM.h"

char *_which(char *filename)
/* Cherche un exécutable par son nom (ex "ls") dans chaque dossier
   du PATH, et retourne son chemin complet dès qu'il est trouvé
   (ex "/usr/bin/ls"), ou NULL si introuvable nulle part. */
{
    char *chemin_path, *dossier, *chemin_complet;
    /* chemin_path : la valeur brute de PATH (ex "/usr/bin:/bin:...")
       dossier     : un dossier individuel, extrait un par un
       chemin_complet : le chemin candidat construit à chaque tour */

    struct stat st;
    /* Structure utilisée par stat() pour recevoir les infos du
       fichier testé (on ne s'intéresse ici qu'à sa valeur de retour,
       pas au contenu de st lui-même). */

    chemin_path = _getenv("PATH");
    /* Récupère la liste des dossiers à explorer */

    dossier = strtok(chemin_path, ":");
    /* Premier appel à strtok : découpe chemin_path sur ":"
       (le séparateur des dossiers dans PATH), récupère le 1er
       dossier. */

    while (dossier)
    /* Boucle tant qu'il reste des dossiers à tester. */
    {
        chemin_complet = build_path(dossier, filename);
        /* Construit le chemin candidat pour CE dossier précis
           (ex dossier="/usr/bin", filename="ls" -> "/usr/bin/ls"). */

        if (stat(chemin_complet, &st) == 0)
        {
            return (chemin_complet);
        }
        /* stat() retourne 0 si le fichier existe à ce chemin.
           Si oui : on a trouvé la commande, on retourne
           immédiatement ce chemin, sans tester les dossiers
           restants. */

        else
        {
            free(chemin_complet);
            dossier = strtok(NULL, ":");
        }
        /* Sinon : ce chemin ne mène à rien, on libère la mémoire
           qu'on venait d'allouer pour lui (évite une fuite mémoire
           à chaque tentative ratée), puis on passe au dossier
           suivant du PATH (appel à strtok avec NULL, pour continuer
           là où on s'était arrêté). */
    }

    return (NULL);
    /* Si on a parcouru TOUS les dossiers du PATH sans succès, la
       commande n'existe nulle part : on retourne NULL. C'est ce
       NULL que ton shell doit tester avant d'appeler execve. */
}