#include "SSM.h"

char** LeDecoupeur(char *str)
/* Découpe une ligne de commande brute (ex "ls -l /tmp") en un
   tableau de mots séparés (ex {"ls", "-l", "/tmp", NULL}), prêt à
   être passé comme second argument à execve. Basée sur strtok, avec
   un piège important géré en interne (voir plus bas). */
{
    int i = 0, j = 0, k = 0;
    /* i : compte le nombre de mots trouvés (1er passage sur "copie")
       j : index d'écriture dans le tableau "array" final (2e passage)
       k : index utilisé pour recopier caractère par caractère "str"
           dans "copie" */

    char *copie, *mot, **array;
    /* copie : duplicata de str, "sacrifiable" pour le comptage
       mot   : résultat de chaque appel à strtok
       array : le tableau final retourné (char **, comme av) */

    if (!str)
    {
        return (NULL);
    }
    /* Sécurité : si on te passe un pointeur NULL, on ne va pas plus
       loin. Note : ici tu retournes un char**  NULL */

    copie = malloc(strlen(str) + 1);
    while (str[k] != '\0')
    {
        copie[k] = str[k];
        k++;
    }
    copie[k] = str[k];
    /* Duplique manuellement str dans copie (malloc + recopie
       caractère par caractère, en incluant le '\0' final).
       POURQUOI cette copie est indispensable : strtok modifie sa
       chaîne EN PLACE (il remplace chaque espace par '\0'). Si on
       faisait le comptage directement sur str, str serait "détruite"
       avant même d'arriver au second passage (le remplissage) —
       et ce second passage ne retrouverait alors qu'un seul mot. */

    mot = strtok(copie, " ");
    while (mot)
    {
        i++;
        mot = strtok(NULL, " ");
    }
    free(copie);
    /* 1er passage (comptage) : on découpe "copie" (jetable) avec
       strtok, uniquement pour COMPTER combien de mots il y a — on
       ne les stocke pas encore. Une fois copie entièrement
       "consommée" par strtok, on la libère : elle ne sert plus. */

    array = malloc((i + 1) * sizeof(char *));
    if (!array)
    {
        free(array);
        return (NULL);
    }
    /* Alloue le tableau final : i cases pour les mots + 1 case
       supplémentaire pour le NULL final qui marquera la fin du
       tableau (comme av). Vérification classique d'échec de malloc
       (note : free(array) juste après un malloc qui a échoué est
       inoffensif ici puisque array vaut déjà NULL dans ce cas, mais
       c'est redondant). */

    mot = strtok(str, " ");
    while (mot)
    {
        array[j] = mot;
        j++;
        mot = strtok(NULL, " ");
    }
    array[j] = NULL;
    /* 2e passage (remplissage) : cette fois on découpe la VRAIE str
       d'origine (encore intacte, puisque seule "copie" a été
       détruite au 1er passage). Chaque mot trouvé par strtok est
       stocké directement dans array (pas de nouvelle copie mémoire :
       array[j] pointe directement à l'intérieur de str). On termine
       par NULL, exigé par execve pour son argv. */

    return (array);
    /* Retourne le tableau de mots prêt à l'emploi. */
}