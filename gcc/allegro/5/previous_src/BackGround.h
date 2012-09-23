

#ifndef BACKGROUND_H
#define BACKGROUND_H

#ifndef BITMAP_H
#include "Bitmap.h"
#endif

struct BackGround : Bitmap
{
  long int               x, y;
  bool init(char *path, ALLEGRO_COLOR col);
  void print();
};


/*Inicia o cenario*/
bool BackGround :: init(char *path, ALLEGRO_COLOR col)
{
  bool     retorno;
  retorno = Bitmap :: open(path, col);
  if(retorno)
  {
    x = y = 0;
    return (true);
  }
  else
    return (false);
}

/**************************
  Coloca a imagem na tela
    baseado nas dimensoes
    da tela
***************************/
void BackGround :: print()
{
  Bitmap :: printFullScreen(x, y, 1);
}

#endif
