

#ifndef ALLEGRO5_INIT_H
#define ALLEGRO5_INIT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



unsigned long int     SCREEN_W           = 640,
                      SCREEN_H           = 480,
                      FONT_PREFERED_SIZE = 0,/*Tamanho da fonte sera proporcional a tela*/
                      FPS                = 60,
                      MAX_SAMPLES        = 1;

float                 GLOBAL_TIMER       = 1.0;

bool                  ALLEGRO5_INIT            = false,
                      IS_IMAGE_ADDON_INSTALLED = false,
                      LOG_FIRST_TIME_OPEN      = true,
                      USING_FONT               = false;
   
ALLEGRO_DISPLAY        *display         = NULL;
ALLEGRO_EVENT_QUEUE    *eventos_globais = NULL;
ALLEGRO_TIMER          *global_timer    = NULL;


#include "String.h"
#include "MessageBox.h"
#include "ERROR.h"
#include "Log.h"
#include "Font.h"
#include "Bitmap.h"
#include "Keys.h"
#include "Color.h"
#include "Allegro5_Init\ConfigurationFile.h"

Log log;

inline void allegro5_init()
{
  if(!al_init())
    FATAL_ERROR("failed to initialize allegro!", "allegro5_init.h");
  
   eventos_globais = al_create_event_queue();
   if(!eventos_globais)
     FATAL_ERROR("failed to initialize eventos globais!", "allegro5_init.h");
 
   
   ConfigurationFile();
   
   al_install_mouse();
   al_install_keyboard();
   
   /*Instancio os objetos*/
   display        = al_create_display(SCREEN_W, SCREEN_H);
   global_timer   = al_create_timer(1.0 / FPS);
   
   /*Fontes de Eventos*/
   al_register_event_source(eventos_globais, al_get_display_event_source(display));
   al_register_event_source(eventos_globais, al_get_timer_event_source(global_timer));
   if( al_is_keyboard_installed() )
     al_register_event_source(eventos_globais, al_get_keyboard_event_source());
   if( al_is_mouse_installed() )
     al_register_event_source(eventos_globais, al_get_mouse_event_source());
   
   
   al_set_target_bitmap(al_get_backbuffer(display));
   
   FONT_PREFERED_SIZE = (SCREEN_W/10 + SCREEN_H/10) / 5;
   ALLEGRO5_INIT = true;
   log.append("allegro5_init...OK");
}

#endif

