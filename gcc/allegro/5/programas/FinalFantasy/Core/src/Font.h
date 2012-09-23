

#ifndef FONT_H
#define FONT_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "MessageBox.h"


#ifndef ALLEGRO5_INIT_H
  extern bool USING_FONT;
#endif


struct Font
{
  int              modo;
  char            *path;
  ALLEGRO_COLOR    color;
  ALLEGRO_FONT    *font;
  
  int getW(char *msg);
  int getH();
  
  void print(int x, int y, char *msg);
  
  bool open(char *path2, int size, int modo2, ALLEGRO_COLOR color2);
  
  ALLEGRO_FONT*  getFont();
};


#endif
