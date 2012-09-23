

#ifndef PONTOS_H
#define PONTOS_H

struct Pontos
{
  double            x, y;
  Pontos           *prox, 
                   *ante;
  
  void setX(double x);
  void setY(double y);
  void ShowAll();
  void New();
};Pontos           *p_ini = NULL,
                   *p_fim = NULL,
                   *p_aux = NULL;

void Pontos :: New()
{
  if(p_ini == NULL)
  {
    p_ini = (Pontos *)malloc(sizeof(struct Pontos));
    p_ini->prox = p_ini->ante = NULL;
    p_fim = p_aux = p_ini;
  }
  else
  {
    p_aux = p_fim;
    p_fim = (Pontos *)malloc(sizeof(struct Pontos));
    p_fim->prox = NULL;
    p_fim->ante = p_aux;
    p_aux->prox = p_fim;
  }
}


void Pontos :: setX(double x){ p_fim->x = x; }

void Pontos :: setY(double y){ p_fim->y = y; }

void Pontos :: ShowAll()
{
  long int    i = 0;
  for(p_aux = p_ini;p_aux != NULL;p_aux = p_aux->prox)
  {
    cout<<"\nX("<<i<<"): "<<p_aux->x;
    cout<<"\nY("<<i++<<"): "<<p_aux->y;
  }
}

#endif
