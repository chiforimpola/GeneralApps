
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <strings.h>
#include <dirent.h>
#include "dir.h"
#include "entities.h"
#include "objects.h"

int init (struct Types*, char*, int);

int main (int argc, char *argv[])
{
    struct stat    st;
    short int      i = 0;

    for (i = 1;i < argc-1;i++) addType (argv[i]);

    init (getTypesInstance(), argv[argc-1], 2);

    return (1);
}


int init (struct Types *types, char *path, int maxdepth)
{
    DIR *dir = opendir(path);
    struct dirent *direntry;
    struct stat s;
    unsigned char isFolder = 0x4;
    char          actual_dir[] = ".",
                  last_dir[] = "..";

    if (maxdepth == 0) return (0);

    if (dir == NULL)
    {
        fprintf (stderr, "Erro ao ler diretorio: %s", path);
        return (-1);
    }
    else
    {
        int count  = 0;
        while (direntry=readdir(dir))
        {
            if (direntry->d_type == isFolder && strcmp (direntry->d_name, actual_dir) != 0 && strcmp (direntry->d_name, last_dir) != 0)
            {
                char  *aux = (char *) malloc (strlen (path) + strlen (direntry->d_name) + 4);
                strcpy (aux, path);
                strcat (aux, "/");
                strcat (aux, direntry->d_name);
                init (types, aux, maxdepth-1);
                free (aux);
            }
            else
            {
                addObject(path, direntry->d_name);
            }
        }
    }

    showObjects();

    return (1);

    if (stat(path, &s) == 0)
    {
        if (s.st_mode & S_IFDIR)//dir
        {
        }
        else if (s.st_mode & S_IFREG)//file
        {
        }
        else//something else
        {
        }
        
    }
    else
    {
        fprintf(stderr, "Erro ao ler caminho!\n");
        return (-1);
    }
}


