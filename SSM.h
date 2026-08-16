#ifndef SSS_H
#define SSS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

char** LeDecoupeur(char *str);
char *_getenv(const char *name);
char *build_path(char *dossier, char *nom_fichier);
char *_which(char *filename);
#endif