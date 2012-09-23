

#include <allegro5/allegro.h>
#include "src/String.h"
#include "src/Message.h"
#include "src/Font.h"
#include "src/Keys.h"
#include "src/Color.h"
#include "src/Sound.h"
#include "src/Bitmap.h"
#include "src/Log.h"
#include "src/ERROR.h"


extern ALLEGRO_TIMER       *global_timer;
extern ALLEGRO_EVENT_QUEUE *eventos_globais;
extern ALLEGRO_DISPLAY     *display;
extern Log                  log;
extern unsigned long int    SCREEN_W,
                            SCREEN_H;


int StartGame(
  char *_intro_sprite, 
  char *_intro_snd, 
  char *_csr_sprite, 
  char *_csr_snd, 
  char *_font,
  char  options_list[][50])
{
  volatile int       i = 0;
  long int           csr_x = SCREEN_W,
                     csr_y = 0,
                     option_focus = 0,
                     MAX_OPTIONS = 0;
  char               key_char[50];
  bool               terminou = false,
                     redraw   = true;
  ALLEGRO_EVENT      ev;
  Font               font;
  Message            options[50];
  Sound              csr_snd,
                     bck_music;
  Bitmap             intro,
                     csr;
  
  log.append("Start Game Menu [Open]");
  
  if( !intro.open(_intro_sprite, INVISIBLE) )
  {
    OPEN_ERROR(intro.path, "main.cpp");
    exit(-1);
  }
  
  else if( !bck_music.open(_intro_snd) )
  {
    OPEN_ERROR(bck_music.path, "main.cpp");
    exit(-1);
  }
  
  else if( !csr.open(_csr_sprite, INVISIBLE) )
  {
    OPEN_ERROR(csr_snd.path, "main.cpp");
    exit(-1);
  }
  
  else if( !csr_snd.open(_csr_snd) )
  {
    OPEN_ERROR(csr_snd.path, "main.cpp");
    exit(-1);
  }
  
  
  else if( !font.open(_font, 30, 0, RED) )
  {
    OPEN_ERROR(font.path, "main.cpp");
    exit(-1);
  }
  
  /*************************************
    Determina a localizacao das opcoes
    baseado em sua quantidade
    Tambem determina que o cursor
      devere comecar ao lado da
      primeira opcao
  **************************************/
  for(i = 0;options_list[i][0] != '-';i++){}
    MAX_OPTIONS = i;
  for(i = 0;i < MAX_OPTIONS;i++)
  {
    options[i].start(
      (SCREEN_W/2) - (font.getW(options_list[i])/2),
      (SCREEN_H/2) - (MAX_OPTIONS*font.getH()) + (i * font.getH()),
      options_list[i],
      font);
    if(csr_x > (options[i].x - 16))
      csr_x = options[i].x - 16;
  }
  
  csr_y = options[0].y + 16;
  
  log.append("Font...OK");
  log.append("\t\tLoop principal");
  
  bck_music.play(1.0, 1, true);
  
  al_start_timer(global_timer);
  
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
        
        if( StringCompareNoCase(key_char, "enter") )
          return (option_focus);
        
      break;
      
      /**************************
          Soltou uma tecla
      ***************************/
      case KEY_UP:
        strcpy(key_char, al_keycode_to_name(ev.keyboard.keycode));
        
        if( StringCompareNoCase(key_char, "down") )
        {
          if(option_focus < MAX_OPTIONS-1)
          {
            csr_y = options[++option_focus].y + 16;
            csr_snd.play(1.0, 1.0, false);
          }
        }
        
        else if( StringCompareNoCase(key_char, "up") )
        {
          if(option_focus > 0)
          {
            csr_y = options[--option_focus].y + 16;
            csr_snd.play(1.0, 1.0, false);
          }
        }
        break;
    }
    
    if(redraw && al_is_event_queue_empty(eventos_globais) && !terminou)
    {
      redraw = false;
      
      al_set_target_bitmap(al_get_backbuffer(display));
      intro.printFullScreen(0);
      
      /*Coloco as mensagens na tela*/
      for(i = 0;i < MAX_OPTIONS;i++)
        options[i].print();
      
      csr.printRegion(0, 0, 16, 16, csr_x, csr_y, 0);
      
      al_flip_display();
      al_clear_to_color(BLACK);
    }
  }
  log.append("Start Game Menu [Close]");
}


/*int main()
{
  al_init();
  short int      option;
  char           options_list[][50] =
                 {
                   "Start",
                   "Exit",
                   "Help",
                   "-"
                 };
  
  option = StartGame(
      "Sprites\\intro.bmp", 
      "Snd\\background.wav", 
      "Sprites\\csr.bmp", 
      "Snd\\csr.wav",
      "Font\\impressedMetal.ttf",
      options_list);
}
*/
