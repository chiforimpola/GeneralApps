

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned long int getFileSize (FILE *f)
{
    unsigned long int previouslocation = ftell(f),
                      size;
    fseek (f, 0, SEEK_END);
    size = ftell (f);
    fseek (f, previouslocation, SEEK_SET);

    return (size);
}


/*Para apresentacao do hex da linha*/
char *incrementHex(char *hex);


int main(int argc, char *argv[])
{
    unsigned long int i;
    FILE             *f;

    for (i = 1;i < argc;i++)
    {
        f = fopen (argv[i], "r");
        if (f != NULL)
        {
            unsigned long int   size = getFileSize(f),
                                i2, count = 0;
            char               *buffer = (char *) malloc (size+1);
            fread (buffer, size, 1, f);
            for (i2 = 0;i2 < size;i2++)
            {
                printf ("%x", buffer[i2]);
                count++;
                if (count == 4)
                {
                    printf ("\n");
                    count = 0;
                }
            }
        }
    }
}

