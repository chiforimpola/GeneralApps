
#include <allegro5/allegro.h>
#include "src/Message.h"
#include "src/Font.h"
#include "src/Keys.h"
#include "src/Color.h"
#include "src/Sound.h"
#include "src/Bitmap.h"
#include "src/Log.h"
#include "src/ERROR.h"

extern unsigned long int SCREEN_W, 
                         SCREEN_H;


int Fim(char *path)
{
  Font               font;
  font.open(path, 30, 0, RED);
  
  al_clear_to_color(BLACK);
  font.print(
    SCREEN_W/2 - (font.getW("Fim de Jogo")/2), 
    SCREEN_H/2, 
    "Fim de Jogo");
  al_flip_display();
  al_rest(4);
}

