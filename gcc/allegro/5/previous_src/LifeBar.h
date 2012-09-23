
#ifndef LIFE_BAR_H
#define LIFE_BAR_H

#include "Bitmap.h"
#include "Color.h"
#include "String.h"

struct LifeBar
{
  char           *path;
  long int        x, y,
                  empty_x[2], empty_y[2],
                  content_x[2], content_y[2],
                  resizeW, resizeH,
                  maxLife;
  Bitmap          entireFile,
                  empty, content;
  
  bool open(long int maxLife2,
            long int x2,
            long int y2,
            long int resizeW2,
            long int resizeH2,
            char *path2, 
            ALLEGRO_COLOR col);
  bool print(long int life);
};

#endif
