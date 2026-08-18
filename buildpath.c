#include "SSM.h"

char *build_path(char *dossier, char *nom_fichier)
/* Construit un chemin complet en collant "dossier" + "/" + "nom_fichier".
   Ex: build_path("/usr/bin", "ls") -> "/usr/bin/ls"
   Écrite à la main (sans strcat, qui est interdite par le sujet). */
{
    int i = 0, j = 0;
    /* i : index utilisé pour ÉCRIRE dans chemin_complet (avance tout
           du long, sur les 3 étapes : dossier, '/', nom_fichier)
       j : index utilisé pour LIRE dans nom_fichier uniquement */

    char *chemin_complet;
    /* Le résultat final, alloué dynamiquement. */

    chemin_complet = malloc(strlen(dossier) + strlen(nom_fichier) + 2);
    /* Taille nécessaire : la longueur du dossier + la longueur du
       nom de fichier + 2 octets supplémentaires :
       - 1 pour le '/' séparateur qu'on va insérer entre les deux
       - 1 pour le '\0' final qui termine la chaîne */

    if (!chemin_complet)
    {
        return (NULL);
    }
    /* Vérification classique : si malloc échoue (mémoire insuffisante),
       on ne continue pas, on signale l'échec en retournant NULL. */

    chemin_complet[0] = '\0';
    /* Initialise la chaîne comme "vide" avant de la remplir.
       Note : cette ligne n'est pas strictement nécessaire ici puisque
       tu remplis chemin_complet caractère par caractère juste après
       (elle serait utile si tu utilisais strcat, qui a besoin d'une
       chaîne déjà valide au départ) — mais elle ne fait pas de mal. */

    while (dossier[i] != '\0')
    {
        chemin_complet[i] = dossier[i];
        i++;
    }
    /* Étape 1 : recopie caractère par caractère le contenu de
       "dossier" (ex: "/usr/bin") dans chemin_complet, tant qu'on n'a
       pas atteint la fin de "dossier" (son '\0'). */

    chemin_complet[i] = '/';
    i++;
    /* Étape 2 : une fois le dossier recopié, on insère le séparateur
       '/' juste après, et on avance i d'une case pour continuer à
       écrire après lui. */

    while (nom_fichier[j] != '\0')
    {
        chemin_complet[i] = nom_fichier[j];
        i++;
        j++;
    }
    /* Étape 3 : recopie caractère par caractère "nom_fichier"
       (ex: "ls") à la suite, dans chemin_complet. i continue
       d'avancer (position d'écriture), j avance en parallèle
       (position de lecture dans nom_fichier). */

    chemin_complet[i] = nom_fichier[j];
    /* Copie le '\0' final. À ce stade, nom_fichier[j] vaut déjà '\0'
       (c'est ce qui a arrêté la boucle juste au-dessus), donc cette
       ligne termine correctement la chaîne chemin_complet. */

    return (chemin_complet);
    /* Renvoie le chemin complet construit, ex "/usr/bin/ls". */
}