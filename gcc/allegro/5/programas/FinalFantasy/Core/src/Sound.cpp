#ifndef SOUND_CPP
#define SOUND_CPP

#ifndef STRING_H
#include "String.h"
#endif

#ifndef ALLEGRO5_INIT_H
  extern unsigned long int SCREEN_W,
                           SCREEN_H,
                           MAX_SAMPLES;
#endif


bool Sound :: open(char *path2)
{
  if( !al_is_audio_installed() )
  {
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(MAX_SAMPLES);
  }
  path = (char *)malloc(StringLengh(path2) + 1);
  strcpy(path, path2);
  
  audio = al_load_sample(path);
  if(audio == NULL)
    return (false);
  return (true);
}



void Sound :: play(double vol, float speed, bool loop)
{
  if(!loop)
    al_play_sample(audio, vol, 0.0, speed, ALLEGRO_PLAYMODE_ONCE, NULL);
  else
    al_play_sample(audio, vol, 0.0, speed, ALLEGRO_PLAYMODE_LOOP, NULL);
}

#endif
