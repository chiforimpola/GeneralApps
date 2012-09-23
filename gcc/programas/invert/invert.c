
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
    unsigned short int    i,
                          i2,
                          i3;
    char                 *buffer;

    for (i = 1;i < argc;i++)
    {
        buffer = (char *) malloc (strlen (argv[i])+2);
        i3 = 0;
        for (i2 = strlen(argv[i])-1;i2 > 0;i2--, i3++)
            buffer[i3] = argv[i][i2];
        buffer[i3++] = argv[i][0];
        buffer[i3] = '\0';
        fprintf (stdout, "%s\n", buffer);
        free (buffer);
    }
}

