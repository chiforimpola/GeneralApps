
#ifndef _FILE_HANDLER_CPP
#define _FILE_HANDLER_CPP

#include <stdio.h>
#include <string.h>
#include "filehandler.h"

FileHandler :: FileHandler(char *path, char *mode2)
{
    abspath = (char *) malloc (strlen (path)+1);
    strcpy (abspath, path);

    mode = mode2;
    file = NULL;
}

void FileHandler :: open ()
{
    file = fopen (abspath, mode);
}

char *FileHandler :: read ()
{
    unsigned int       buffer_length = 1024;
    char               aux[buffer_length],
                      *aux2,
                      *buffer = NULL;

    if (file == NULL)
        return (NULL);

    do
    {
        if (fgets (aux, buffer_length-1, file) != NULL)
        {
            if (buffer == NULL)
            {
                buffer = (char *) malloc (strlen (aux)+1);
                strcpy (buffer, aux);
            }
            else
            {
                aux2 = (char *) malloc (strlen (buffer)+1);
                strcpy (aux2, buffer);
                free (buffer);
                buffer = (char *) malloc (strlen (aux2) + strlen (aux)+2);
                strcpy (buffer, aux2);
                strcat (buffer, aux);
            }
        }
        else break;
        
    } while (true);

    return (buffer);
}

#endif

