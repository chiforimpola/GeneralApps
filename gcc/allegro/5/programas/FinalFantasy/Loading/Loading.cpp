
#include <allegro5/allegro.h>
#include "src/Font.h"

extern unsigned long int SCREEN_W, 
                         SCREEN_H;
extern ALLEGRO_DISPLAY  *display;


void Loading(Font global_font)
{ 
  al_set_target_bitmap(al_get_backbuffer(display));
  
  global_font.print(
    SCREEN_W - (global_font.getW("Loading")), 
    SCREEN_H - global_font.getH(), 
    "Loading");
  al_flip_display();
}


/*
int main()
{
  al_init();
  Loading();
}
*/

