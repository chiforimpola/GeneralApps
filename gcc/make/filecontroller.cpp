
#include "filecontroller.h"
#include <string.h>

FileController :: FileController()
{
    filepath = mode = NULL;
    file_handle = NULL;
}

int FileController::open(char *filepath2, char *mode2)
{
    file_handle = fopen (filepath2, mode2);
    if (file_handle != NULL)
    {
        filepath = (char *) malloc (strlen (filepath2)+1);
        strcpy (filepath, filepath2);
        mode = mode2;
        return (1);
    }

    return (-1);
}

char* FileController :: read ()
{
    int       buffer_len = 1024,
              first = 1;
    char     *buffer,
             *aux2,
              aux[buffer_len];

    if (file_handle == NULL) return (NULL);

    do
    {
        if (fgets(aux, buffer_len, file_handle))
        {
            if (first == 1)
            {
                buffer = (char *) malloc (strlen(aux)+1);
                strcpy (buffer, aux);
                first = 0;
            }
            else
            {
                aux2 = (char *) malloc (strlen(aux)+strlen(buffer)+2);
                strcpy (aux2, buffer);
                strcat (aux2, aux);
                free (buffer);
                buffer = (char *) malloc (strlen (aux2)+1);
                strcpy (buffer, aux2);
                free (aux2);
            }
        }
        else break;
    } while (true);

    return (buffer);
}

char * FileController :: getFilepath()
{
    return (filepath);
}

char * FileController :: getMode()
{
    return (mode);
}

