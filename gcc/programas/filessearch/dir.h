#ifndef _DIR_H
#define _DIR_H

struct Dir
{
    char      *path;
    struct     entities
    {
        char   *path;
        struct entities  *next, *previous;
    };struct entities   *entities_first, *entities_last;
    struct Dir    *next, *previous;
};struct Dir   *dir_first =  NULL, *dir_last = NULL;

void addDir (char *path)
{
    struct Dir   *d;

    d = (struct Dir *) malloc (sizeof (struct Dir));
    d->path = (char *) malloc (strlen(path)+1);
    strcpy (d->path, path);

    if (dir_first == NULL)
    {
        dir_first = d;
        dir_first->next = dir_first->previous = NULL;
        dir_last = d;
    }
    else
    {
        dir_last->next = d;
        d->previous = dir_last;
        dir_last = d;
    }
}
void appendInDir(struct Dir *dir, char *path)
{
   struct entities   *e;
   e = (struct entities *) malloc (sizeof (struct entities));
   e->path = (char *) malloc (strlen (path)+1);
   e->next = NULL;
   strcpy (e->path, path);

   if (dir->entities_first == NULL)
   {
       dir->entities_first = e;
       dir->entities_first->previous = NULL;
       dir->entities_last = dir->entities_first;
   }
   else
   {
       dir->entities_last->next = e;
       e->previous = dir->entities_last;
       dir->entities_last = e;
   }
}
void showEntities()
{
    struct Dir       *d;
    struct entities  *e;

    for (d = dir_first;d != NULL;d = d->next)
    {
        for (e = d->entities_first;e != NULL;e = e->next) printf ("%s->%s\n", d->path, e->path);
    }
}


#endif
