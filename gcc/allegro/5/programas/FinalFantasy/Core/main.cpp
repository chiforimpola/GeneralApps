

#include "src/allegro5_init.h"

#include "src/LifeBar.h"
#include "src/Color.h"
#include "src/Keys.h"
#include "src/Font.h"
#include "src/Font.cpp"
#include "src/Log.h"
#include "src/Log.cpp"
#include "src/String.h"
#include "src/String.cpp"
#include "src/Bitmap.h"
#include "src/Bitmap.cpp"
#include "src/Sound.h"
#include "src/Sound.cpp"
#include "src/Message.h"
#include "src/Message.cpp"
#include "src/ERROR.h"
#include "src/ERROR.cpp"

#include "src/Externs.h"

int main()
{
  if(!ALLEGRO5_INIT) allegro5_init();
  
  short int      option;
  char           options_list[][50] =
                 {
                   "Start",
                   "Exit",
                   "Help",
                   "-"
                 };
  
  volatile int       i = 0;
  long int           life = 100;
  char               key_char[50];
  bool               terminou = false,
                     redraw   = true;
  LifeBar            lifeBar;
  Font               global_font;
  ALLEGRO_EVENT      ev;
  
  lifeBar.open(200, 0, 0, SCREEN_W/2, 50, "resource\\LifeBars\\001.bmp", INVISIBLE);
  
  global_font.open("resource\\Font\\impressedMetal.ttf", 32, 0, WHITE);
  log.append("Font...OK");
  
  Loading(global_font);
  
  option = StartGame(
    "resource\\StartGame\\Sprites\\intro.bmp", 
    "resource\\StartGame\\Snd\\background.wav", 
    "resource\\StartGame\\Sprites\\csr.bmp", 
    "resource\\StartGame\\Snd\\csr.wav", 
    "resource\\Font\\impressedMetal.ttf", 
    options_list);
  
  log.append("\t\tLoop principal");
    
  al_start_timer(global_timer);
  
  al_clear_to_color(BLACK);
  al_flip_display();
  
  while(!terminou)
  {
    al_wait_for_event(eventos_globais, &ev);
    
    switch(ev.type)
    {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
        terminou = true;
        break;
        
      case ALLEGRO_EVENT_TIMER:
        if(ev.timer.source == global_timer)
          redraw = true;
        break;
        
      case KEY_DOWN:
        strcpy(key_char, al_keycode_to_name(ev.keyboard.keycode));
        
        if( StringCompareNoCase(key_char, "escape") ) terminou = true;
        
        else if( StringCompareNoCase(key_char, "down") ){ }
          
        else if( StringCompareNoCase(key_char, "up") ){ }
        
        else if( StringCompareNoCase(key_char, "right") ){ }
          
        else if( StringCompareNoCase(key_char, "left") ){ }
        
      break;
      
      /**************************
          Soltou uma tecla
      ***************************/
      case KEY_UP:
        strcpy(key_char, al_keycode_to_name(ev.keyboard.keycode));
        break;
    }
    
    if(redraw && al_is_event_queue_empty(eventos_globais) && !terminou)
    {
      redraw = false;

      al_set_target_bitmap(al_get_backbuffer(display));
      
      lifeBar.print(life);
      if(life > 0)life--;
      else
        life = 200;
      global_font.print(0, SCREEN_H/2, "Teste");

      al_flip_display();
      al_clear_to_color(BLACK);
    }
  }
  
  al_stop_samples();
  
  Fim("resource\\Font\\Resident_Evil_Large.ttf");
  
  al_destroy_display(display);
  al_destroy_event_queue(eventos_globais);
  al_destroy_timer(global_timer);
  
  log.append("\t\tLoop principal...OK");
  log.append("[FIM]");
  log.close();
}

