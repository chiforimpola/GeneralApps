
#ifndef BITMAP_H
#define BITMAP_H

struct Bitmap
{
  bool                  init;/*diz se executou a funcao init*/
  char                 *path;
  ALLEGRO_BITMAP       *sprite;
  
  /*gets, sets*/
  int getH();
  int getW();
  
  bool open(char *path, ALLEGRO_COLOR col);
  void print(int x, int y, int flag);
  void resize(long int resizeW, long int resizeH);
  ALLEGRO_BITMAP* getImageResized(long int resizeW, long int resizeH);
  void printRegion(int x_ini, int y_ini, int x2, int y2, int x, int y, int flag);
  void printFullScreen(int x, int y, int flag);
  void printFullScreen(int flag);
};

#endif
