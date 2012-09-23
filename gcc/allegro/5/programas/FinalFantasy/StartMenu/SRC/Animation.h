/*******************************************************
  As informacoes da animacao ficarao armazenadas no
  arquivo ANIMATION_CONF_FILE.
  Informacoes serao:
              - Se havera loop
              - Cor que deve ser mascarada
              - Nome dos bitmaps(frames)
              - Intervalo entre frames
              - etc...
*******************************************************/

#ifndef ANIMATION_H
#define ANIMATION_H

#ifndef BITMAP_H
#include "Bitmap.h"
#endif


#define ANIMATION_MAX_SPRITES       500
#define ANIMATION_CONF_FILE         "animation.dat"
#define ANIMATION_SCRIPT_CHAR_END   '#'
#define ANIMATION_LOOP              "LOOP"
#define ANIMATION_LOCK              "LOCK"
#define ANIMATION_COLOR             "IGNORE_COLOR"
#define ANIMATION_INTERVAL          "INTERVAL"
#define ANIMATION_SOUND             "SOUND"
#define ANIMATION_FRAMES            "FRAMES"
#define ANIMATION_JUMP_TO           "JUMP_TO"
#define ANIMATION_SUB_ANIMATION     "SUB_ANIMATION"
#define ANIMATION_PRINT_SUB_ANIMATION     "PRINT_SUB_ANIMATION"
#define ANIMATION_JUMP_TO_SUB_ANIMATION   "JUMP_TO_SUB_ANIMATION"


struct Animation
{
  char               *path;/*Contera o diretorio da animacao*/
  double              interval;/*marca o intervalo entre os frames*/
  long int            i_sub_animations;
  bool                loop;/*me diz se devera fazer loop na animacao*/
  FILE               *arq;/*abrira o arquivo de configuracao*/
  ALLEGRO_COLOR       masked_color;/*cor a ser mascarada*/
  Animation          *prox, *ante;
  
  void init(char *path2, int ID2);
  void readScript(int ID);
  void play(int ID);
  void stop(int ID);
  void print(long int x, long int y, int flag);
  void print(long int x, long int y, int flag, int ID);
  void printSubAnimation(int x, int y, int flag);/*Printa todas as subanimacoes configuradas caso existam*/
  void New();
  
  int getFrames(int ID2);
/****************************
   [Usados por Timer]
****************************/
  bool ChangeFrame(int ID);
  void ChangeSubAnimationFrame(int ID);
  void TESTE();
  
  ALLEGRO_TIMER *getTimer(int n);
  ALLEGRO_TIMER *getSubAnimationTimer(int n);
  

  /*Estruturas adicionais*/
  struct Frames;
  struct Timer;
  struct Sound;/*Contera todos os sons que serao tocados quando
                 chegar um determinado frame*/
  void startSubAnimation(Frames *aux);
  void stopSubAnimation(Frames *aux);
};

#include "Animation\Timer.h"
#include "Animation\Frames.h"
#include "Animation\Sound.h"
#include "Animation\AnimationCore.h"

#endif
