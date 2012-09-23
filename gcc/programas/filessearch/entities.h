
#ifndef _ENTITIES_H
#define _ENTITIES_H

struct Types
{
    char           *extension;
    struct Types   *next, *previous;
};struct Types  *types_first = NULL, *types_last = NULL;

void addType(char *type)
{
    struct Types *t;
    t = (struct Types *) malloc (sizeof (struct Types));
    t->extension = (char *) malloc (strlen(type)+1);
    strcpy (t->extension, type);

    if (types_first == NULL)
    {
        types_first = t;
        types_last = t;
        types_first->next = types_first->previous = NULL;
    }
    else
    {
        types_last->next = t;
        t->previous = types_last;
        types_last = t;
    }
}
void showTypes()
{
    struct Types *aux;
    for (aux = types_first;aux != NULL;aux = aux->next)
    {
        printf ("%s\n", aux->extension);
    }
}
struct Types *getTypesInstance()
{
    return (types_first);
}


#endif

