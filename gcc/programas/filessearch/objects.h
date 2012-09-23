
#ifndef _OBJECTS_H
#define _OBJECTS_H

struct Objects
{
    char             *path;
    char             *parent;
    struct Objects   *next, *previous;
};struct Objects   *objects_first = NULL, *objects_last = NULL;

int addObject (char *parent, char *path)
{
    struct Objects   *aux = (struct Objects *) malloc (sizeof (struct Objects));
    aux->parent = (char *) malloc (strlen (parent)+1);
    aux->path = (char *) malloc (strlen (path)+1);

    strcpy (aux->parent, parent);
    strcpy (aux->path, path);

    aux->next = NULL;

    if (objects_first == NULL)
    {
        objects_first = aux;
        objects_last = objects_first;
        objects_first->next = objects_first->previous = NULL;
    }
    else
    {
        objects_last->next = aux;
        aux->previous = objects_last;
        objects_last = aux;
    }
}

int showObjects()
{
    struct Objects *aux;
    for (aux = objects_first;aux != NULL;aux = aux->next)
    {
        printf("[%s]\t%s\n", aux->parent, aux->path);
    }
}

#endif

