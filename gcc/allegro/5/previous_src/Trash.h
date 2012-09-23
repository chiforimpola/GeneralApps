
#ifndef TRASH_H
#define TRASH_H

struct Trash
{
  void         *obj;
  Trash        *prox, *ante;
  
  void  add(void *obj2);
  void *get();
  void  Destroy();
  int   Size();
  Trash *New(void *obj2);

};Trash trash,
       *trash_ini = NULL,
       *trash_fim = NULL,
       *trash_aux = NULL;

void Trash :: add(void *obj2)
{
  trash_aux = New(obj2);
  trash_aux->obj = &obj2;
}

void* Trash :: get()
{
  return (trash_ini->obj);
}

Trash* Trash :: New(void *obj2)
{
  if(trash_ini == NULL)
  {
    trash_ini = (Trash *)malloc(sizeof(struct Trash) + sizeof(obj2));
    trash_ini->prox = trash_ini->ante = NULL;
    trash_fim = trash_aux = trash_ini;
  }
  else
  {
    trash_aux = trash_fim;
    trash_fim = (Trash *)malloc(sizeof(struct Trash) + sizeof(obj2));
    trash_fim->ante = trash_aux;
    trash_fim->prox = NULL;
    trash_aux->prox = trash_fim;
    trash_aux = trash_fim;
  }
  return (trash_fim);
}

void Trash :: Destroy()
{
  if(trash_ini != NULL)
    for(trash_aux = trash_ini;trash_aux != NULL;trash_aux = trash_aux->prox)
      if(trash_aux->ante != NULL)
      {
        free(trash_aux->ante);
        trash_aux->ante = NULL;
      }
  free(&trash_fim);
  trash_fim = trash_ini = NULL;
}

int Trash :: Size()
{
  unsigned long int n = 0;
  if(trash_ini != NULL)
    for(trash_aux = trash_ini;trash_aux != NULL;trash_aux = trash_aux->prox)
      n++;
  return (n);
}

#endif
