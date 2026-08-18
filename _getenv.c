#include "SSM.h"

char *_getenv(const char *name)
/* Retourne un pointeur vers la VALEUR d'une variable
   d'environnement (ex. name="PATH" -> retourne "/usr/bin:/bin:...")*/
{
    int i = 0;
    /* Compteur pour parcourir le tableau environ élément par élément. */

    extern char **environ;
    /* variable globale du système, qui contient déjà
       tout l'environnement (PATH, HOME, USER...) sous forme d'un
       tableau de chaînes "NOM=valeur", terminé par NULL.
       Le mot-clé extern dit : "cette variable existe déjà ailleurs,
       je veux juste pouvoir m'en servir ici". Nécessaire en
       compilation stricte (-std=gnu89 -pedantic) sinon gcc refuse
       de la reconnaître automatiquement. */

    if (name == NULL)
    {
        return (NULL);
    }
    while (environ[i])
    /* On parcourt environ tant qu'on n'a pas atteint la fin du
       tableau (rappel : NULL-terminé, comme av dans main). */
    {
        if (strncmp(environ[i], name, strlen(name)) == 0
            && environ[i][strlen(name)] == '=')
        /* Cette condition vérifie DEUX choses à la fois :
           1) strncmp(...) == 0 : les strlen(name) premiers
              caractères de environ[i] correspondent exactement à name
              (ex: si name="PATH", on vérifie que ça commence par "PATH")
           2) environ[i][strlen(name)] == '=' : le caractère JUSTE
              APRÈS ces lettres est bien un '='.
           Pourquoi le point 2 est indispensable : sans lui, une
           variable comme "PATHOLOGY=xyz" matcherait aussi la
           recherche de "PATH", ce qui serait un faux positif. */
        {
            return (environ[i] + strlen(name) + 1);
            /* On a trouvé la bonne variable. On retourne un pointeur
               qui saute par-dessus "PATH=" (donc name + le '=')
               pour ne renvoyer QUE la valeur, ex "/usr/bin:/bin:...".
               C'est de l'arithmétique de pointeur : on avance le
               pointeur environ[i] de (strlen(name) + 1) cases. */
        }
        i++;
        /* Si ce n'était pas la bonne variable, on passe à la
           suivante dans le tableau environ. */
    }
    return (NULL);
}