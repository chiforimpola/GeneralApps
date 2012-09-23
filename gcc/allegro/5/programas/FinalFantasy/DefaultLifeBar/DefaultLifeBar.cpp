
#ifndef DEFAULT_LIFE_BAR_CPP
#define DEFAULT_LIFE_BAR_CPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


#include "src/Color.h"
#include "src/String.h"
#include "src/ERROR.h"


bool USING_PRIMITIVES_ADDON = false;

bool printDefaultLifeBar(
  long int          lifeactual, 
  long int          lifemax, 
  long int          bar_x, 
  long int          bar_y,
  long int          WIDTH,
  long int          HEIGHT,
  ALLEGRO_COLOR     col,
  int               thickness)
{
  volatile long     x = bar_x, 
                    y = bar_y,
                    cont_bars = 0;
  float             
                    /*Porcentagem referente à [lifeactual] e [lifemax]*/
                    percent   = (lifeactual*100) / lifemax;
  unsigned long     
                    /*Espacamento entre as barras menores*/
                    spacement = thickness,
                    
                    /*Total de barras que preenche completamente o retangulo*/
                    max_bars  = (WIDTH / (spacement + thickness)),
                    
                    /*Numero de barras que preenche o retangulo ate [percent]*/
                    actual_max_bars = (percent * max_bars) / 100;
  
  if(lifeactual < 0 || WIDTH <= 0 || HEIGHT <= 0 ||
     lifeactual > lifemax || thickness <= 0)
    return (false);
  
  if(!USING_PRIMITIVES_ADDON)
  {
    al_init_primitives_addon();
    USING_PRIMITIVES_ADDON = true;
  }
  
  al_draw_rectangle(
   bar_x, bar_y, 
  bar_x + WIDTH, bar_y + HEIGHT,
  col, thickness);
  
  for(cont_bars = 0;cont_bars < actual_max_bars;cont_bars++)
  {
    al_draw_line(
      x, y, 
      x, y + HEIGHT,
      col, thickness);
    x += thickness + spacement;
  }
  
  return (true);
}

#endif
