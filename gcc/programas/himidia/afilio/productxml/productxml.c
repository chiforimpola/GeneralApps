
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[])
{
    unsigned short int i = 0,
                       indexproduct = 2,
                       show = 1;
    unsigned long int anomaly = 0, cont = 0,
                      maxtags = 0,
                      maxproducts = 0;
    int               found = 1;

    if (argc < 3)
    {
        printf ("\033[93m\n<arquivoA>\n<tag_produtoA>\n<arquivoB>\n<tag_produtoB>\n...\n\033[0m");
        return (1);
    }

    for (i = indexproduct;i < argc;i += 2)
    {
        indexproduct = i;
        FILE *f = fopen (argv[i-1], "r");
        if (f == NULL)
        {
            printf("\n\033[93mFalha ao abrir arquivo!\t\t%s\n\033[0m", argv[i-1]);
            return(-1);
        }
        cont = 0;
        found = 0;
        maxtags = 0;
        maxproducts = 0;
        show = 1;
        printf ("\033[36m");
        printf ("\nProcessando arquivo\t\t%s", argv[i-1]);
        while (!feof (f))
        {
            char c = fgetc (f);
            if (c == '<')
            {
                char tagvalue[1000];
                volatile short int i = 0, i2 = 0;
                c = ' ';
                tagvalue[0] = fgetc (f);
                if (tagvalue[0] == '!')
                {
                    while (fgetc(f) != '<'){ }
                    tagvalue[0] = '\0';
                    i = 0;
                }
                else i = 1;
                for (;tagvalue[i-1] != '>' && tagvalue[i-1] != ' ';i++)
                    tagvalue[i] = fgetc (f);
                if (tagvalue[i-1] == ' ')
                {
                    while (fgetc (f) != '>') { }
                }
                tagvalue[i-1] = '\0';
                if (tagvalue[0] == '/')
                {
                    char aux[strlen(tagvalue)+1];
                    for (i = 1;i < strlen(tagvalue);i++)
                        aux[i-1] = tagvalue[i];
                    aux[i] = '\0';
                    if (strcmp (aux, argv[indexproduct]) == 0)
                    {
                        show = 0;
                    }
                    if (show) maxtags++;
                }
                else if (strcmp(tagvalue, argv[indexproduct]) == 0)
                {
                    found = 1;
                    maxproducts++;
                }
                
                if (found && tagvalue[0] != '/' && show && strlen(tagvalue) > 0) printf ("\n%s", tagvalue);
            }
        }
        printf ("\nMaxTags: \t\t%d\nMax Products: \t\t%d\n", maxtags, maxproducts);
        printf ("\033[0m");
        fclose (f);
    }
}


