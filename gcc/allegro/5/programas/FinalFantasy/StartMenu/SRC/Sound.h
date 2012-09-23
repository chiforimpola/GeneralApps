
#ifndef SOUND_H
#define SOUND_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


struct Sound
{
  ALLEGRO_SAMPLE        *audio;
  char                  *path;
  bool open(char *path);
  void play(double vol, float speed, bool loop);
};

#endif
