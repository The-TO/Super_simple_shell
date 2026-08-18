#include "SSM.h"

int main (void)
{
    int status;
    /* Reçoit le statut de fin de l'enfant, rempli par wait(). */

    pid_t le_pid;
    /* Stocke le retour de fork() : 0 (enfant), PID (parent), -1 (erreur). */

    char *line = NULL, **cmd_argv, *chemin_trouve;
    /* line         : la ligne brute tapée par l'utilisateur (via getline)
       cmd_argv     : le tableau de mots découpés (via LeDecoupeur)
       chemin_trouve : le chemin complet trouvé par _which, ou NULL */

    size_t len = 0;
    /* Taille du buffer alloué par getline pour "line". */

    extern char **environ;
    /* Accès à l'environnement du processus, transmis ensuite à execve. */

    while (1)
    /* Boucle infinie : c'est le cœur du shell, un tour = un cycle
       prompt -> lecture -> exécution. */
    {
        printf("#cisfun$ ");
        /* Affiche le prompt. */

        if (getline(&line, &len, stdin) == -1)
        {
            free(line);
            return (-1);
        }
        /* Lit une ligne. Si getline renvoie -1 (EOF, ex Ctrl+D, ou
           erreur), on libère la mémoire et on quitte proprement. */
        line[strlen(line) - 1] = '\0';
        cmd_argv = LeDecoupeur(line);
        /* Découpe la ligne en mots (voir fichier précédent).
           ATTENTION : line contient encore son '\n' final à ce
           stade — ce n'est pas retiré ici. cmd_argv[0] va donc
           contenir "ls\n" au lieu de "ls" pour le dernier mot
           d'une commande sans arguments, ou pire, si la commande
           ne fait qu'un mot, cmd_argv[0] lui-même aura le '\n'
           collé. C'est le bug qu'on avait rencontré ensemble dans
           le tuto — il va faire échouer stat()/execve() même sur
           des chemins par ailleurs valides. */

        le_pid = fork();
        /* PROBLÈME PAR RAPPORT À LA CONSIGNE 0.3 :
           le sujet demande explicitement "fork must not be called
           if the command doesn't exist". Or ici, fork() est appelé
           AVANT même de savoir si la commande existe (_which n'est
           appelée qu'après, dans l'enfant). Il faudrait inverser
           l'ordre : appeler _which AVANT le fork(), et ne faire le
           fork() QUE si un chemin a été trouvé. */

        if (le_pid == 0)
        /* Branche exécutée uniquement par l'ENFANT. */
        {
            chemin_trouve = _which(cmd_argv[0]);
            /* Cherche le chemin complet de la commande dans le PATH. */

            if (!chemin_trouve)
            {
                exit(1);
            }
            /* Si introuvable : l'enfant s'arrête. Note : pas de
               message d'erreur affiché ici (le sujet attend un
               message précis type "commande: not found", à ajouter
               plus tard). */

            execve(chemin_trouve, cmd_argv, environ);
            perror("Error");
            exit(1);
            /* Tente d'exécuter la commande trouvée. Si execve
               échoue malgré tout (cas rare puisque _which a déjà
               vérifié l'existence via stat), on affiche l'erreur
               système et on arrête l'enfant. */
        }
        else if (le_pid > 0)
        {
            wait(&status);
        }
        /* Branche du PARENT : attend que l'enfant se termine avant
           de reboucler et d'afficher un nouveau prompt. */

        else
        {
            perror("Error:");
        }
        /* fork() a échoué (-1) : affiche l'erreur système. */
    }
    return (0);
}