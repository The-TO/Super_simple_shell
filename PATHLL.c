#include "SSM.h"

typedef struct path_node
{
    char *dir;
    struct path_node *next;
} path_node_t;


int main(void)
{
    char *chemin_path, *directory;
    path_node_t *head, *tail, *nouv, *courant;
    
    head = NULL;
    tail = NULL;
    
    chemin_path = _getenv("PATH");
    directory = strtok(chemin_path, ":");
    while (directory)
    {
        nouv = malloc(sizeof(path_node_t));
        nouv->dir = directory;
        nouv->next = NULL;
        if (!head)
        {
            head = nouv;
        }
        else
        {
            tail->next = nouv;
        }
        tail = nouv;
        directory = strtok(NULL, ":");
    }
    courant = head;
    while (courant != NULL)
    {
        printf ("%s\n", courant->dir);
        courant = courant->next;
    }
    return(0);
}

