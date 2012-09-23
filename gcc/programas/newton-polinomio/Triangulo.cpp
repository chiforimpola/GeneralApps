
#ifndef TRIANGULO_PASCAL_CPP
#define TRIANGULO_PASCAL_CPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TrianguloPascal.h"
#include "String.h"

using namespace :: std;

/***************************************
         Atributos e variaveis
****************************************/
_TrianguloPascal    *_t_ini = NULL,
                    *_t_fim = NULL,
                    *_t_aux = NULL,
                     _t;

TrianguloPascal     tPascal;


void _TrianguloPascal :: New(long int i, long int j)
{
  if(_t_ini == NULL)
  {
    _t_ini          = (_TrianguloPascal *)malloc(sizeof(struct _TrianguloPascal));
    _t_ini->prox    = _t_ini->ante = NULL;
    _t_aux = _t_fim = _t_ini;
  }
  else
  {
    _t_aux         = _t_fim;
    _t_fim         = (_TrianguloPascal *)malloc(sizeof(struct _TrianguloPascal));
    _t_fim->prox   = NULL;
    _t_fim->ante   = _t_aux;
    _t_aux->prox   = _t_fim;
  }
  _t_fim->i = i;
  _t_fim->j = j;
}



long int _TrianguloPascal :: getN(long int i, long int j)
{
  for(_t_aux = _t_ini;_t_aux != NULL;_t_aux = _t_aux->prox)
    if(_t_aux->i == i && _t_aux->j == j)
      return (_t_aux->n);
}



void _TrianguloPascal :: setN(long int i, long int j, long int n)
{
  for(_t_aux = _t_ini;_t_aux != NULL;_t_aux = _t_aux->prox)
    if(_t_aux->i == i && _t_aux->j == j)
    {
      _t_aux->n = n;
      break;
    }
}





void TrianguloPascal :: create(long int MAX2)
{
  volatile int     i, j;
  
  MAX = MAX2;
  
  for(i = 0;i < MAX;i++)
    for(j = 0;j < MAX;j++)
    {
      _t.New(i, j);
      if(j == 0 || j == i)
        _t_fim->n = 1;
      else
        _t_fim->n = 0;
    }
  
  for(i = 0;i < MAX;i++)
    for(j = 0;j < MAX;j++)
      if(i > 0 && j > 0)
        _t.setN(i, j, ( _t.getN(i-1, j) + (_t.getN(i-1, j-1)) ) );
}



char* TrianguloPascal :: getRow(long int n)
{
  long int  j,
            i = 0;
  char     *values,
            aux[500],
            aux2[50];
  aux[0] = '\0';
  
  if(n >= MAX)
    return (NULL);
  
  for(j = 0;j < MAX;j++)
  {
    if(_t.getN(n, j) != 0)
    {
      //itoa(_t.getN(n, j), aux2, 10);
      sprintf (aux, "%d", _t.getN(n, j));
      strcat(aux, aux2);
      strcat(aux, " ");
    }
    else
    {
      values = (char *)malloc(StringLengh(aux) + 1);
      strcpy(values, aux);
      return (values);
    }
  }
}


void TrianguloPascal :: Show()
{
  long int     i, j;
  for(i = 0;i < MAX;i++)
  {
    for(j = 0;j < MAX;j++)
      if(_t.getN(i, j) != 0)
        cout<<_t.getN(i, j)<<" ";
    cout<<"\n";
  }
}

#endif
