

#ifndef DEFAULT_LIFE_BAR_H
#define DEFAULT_LIFE_BAR_H

extern bool USING_PRIMITIVES_ADDON;

bool printDefaultLifeBar(
  long int          lifeactual, 
  long int          lifemax, 
  long int          bar_x, 
  long int          bar_y,
  long int          WIDTH,
  long int          HEIGHT,
  ALLEGRO_COLOR col,
  int thickness);

#endif
