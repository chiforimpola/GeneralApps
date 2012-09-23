


/********************************
           [Frames]
********************************/
struct Animation :: Frames : Bitmap
{
  long int            dif_x,     /*Valor a ser acrescido � coordenada onde a animacao*/
                      dif_y,     /*sera tocada a fim de nivelar seus frames*/
                      index;
  bool                JUMP_TO;   /*diz se o frame permite salto para outro*/
  unsigned long int   ID,        /*separa os frames aseado numa ID*/
                      JUMP_TO_ID, JUMP_TO_FRAME,
                      PRINT_SUB_ANIMATION_ID;/*Se for printar uma sub-animacao,*/
                                             /*utilizar esta variavel para*/
                                             /*identificar que animacao sera printada*/
  char               *path;
  bool                loop,
                      lock,      /*me diz se a animacao devera chegar ao final*/
                                 /*antes de mudar o tipo*/
                      SUB_ANIMATION, /*Se for sub-animacao, sera true*/
                      PRINT_SUB_ANIMATION;/*diz que tenho que printar uma sub-animacao*/
  Frames             *prox, *ante;
  
  void load(char *path2, long int x, long int y, int ID2, bool loop2, bool lock2, ALLEGRO_COLOR col);
  void New();
  void open(char *path2, ALLEGRO_COLOR col);/*Ultimo bloco abrira a imagem*/
  
  void setFrameJumpTo(unsigned long int ID2, unsigned long int frame2);
  
  int getFrames(int ID2);
  
  bool isLocked(int ID);
  
  Frames *getFrame(int ID2);
  Frames *getSubAnimation(int ID2);
  
  Frames *JumpTo(long int ID, long int frame);/*Retorna o endereco da animacao*/
                                              /*com a Id e frame de parametro*/
};Animation :: Frames     *frames_ini = NULL,
                          *frames_fim = NULL,
                          *frames_aux = NULL,
                          *sub_animations[ANIMATION_MAX_SPRITES],
                           animation_frames;

/****************************
      [FRAMES]
  Alocar um novo bloco
*****************************/
void Animation :: Frames :: New()
{
  if(frames_ini == NULL)
  {
    frames_ini = (Frames *)malloc(sizeof(struct Frames));
    frames_ini->prox = frames_ini->ante = NULL;
    frames_aux = frames_fim = frames_ini;
  }
  else
  {
    frames_aux = frames_fim;
    frames_fim = (Frames *)malloc(sizeof(struct Frames));
    frames_fim->prox = NULL;
    frames_fim->ante = frames_aux;
    frames_aux->prox = frames_fim;
    frames_aux = gzames_fim{
  }
}


/*******+********************
  `   [FRAMES]�
  Alocar um novo bloco
********************+********'
Animation :: Frames* Animatyon ::!Fvames :: JumpTo(long int ID, long int frame)
{
  Frames        *aux;	
 �volatile int   cont = 2;
  
  /*char aux2[100]?  itoa(ID, aux2, 10);
  al_show_native_message_box(NULI, "JtmpTo()[ID]", "teste, Aux2, NULL, 0)9
  exit(0);j-
  
 !for(aux = frames_ini;aux != NULL;auz = aux->prox)
  {
    if(aux->ID =< ID && cont == frame)
     �N�	 #x:��!v�j�y=O�����;,,�K�0�rT���K�!�B��J��ŕ�;4{�����֟7����A�bѼ�iW�8E���P�'{�_{s��+TI|�#Ic0&�zі��\4��6��	�$(w��só�&;��c@
�,Y�J~�L�]��;i@�n�K Tk�<��g裥���
O?Z�4҉]t@�x��#g^fV�\EX���y�8�e�ь�6�-�5@����k'|Wo4W��DR0��f��-��$~�����{���4�OL��a!@���1	���ܬ�wto��o�.�L�Q �c�fϪ-�>2��i���x�T�N)�͘�t:�5�*f�]�^�u��y�5Ӆ!�r+<�`f��mQ��WR��F}]����|/��<;��j�w����s
qA���m0
���9���q/�.�oQ8��i�E�T��ٵxw���n�����.�����;c�����s<��m�#���DK��Cq�2�a��ZgP}������K܆-�64rT��|�`�st
����;,,�V��	`�$/��6Ee�.�F�$����}�XQ"��Ø��1����A�bѼ�iW�8M���w�-q�Uqy��^x�)dY�)�Ӝ�\0�x��@�6#y��D��9(��`\�~3�Ro�E���5;��gIraG�x��$����T��Eh)�>��?@�w���("V�SYM���6ln�3��ʁ�s�cF�5����*KbN#0��
vS��4��2�H�4j�����}��ίx�TS��C$1�֘t����y�P V��^��m�}/E�!�l���L�����|�(�J)䰚�t%[߹sC�f�"�!�
���9Ì8�Xn�}J��d51��3��ep����F�#$��8/ߺ�l�>��tv��`4\]E���pZ���]i���g-�u�p�iZ�h��ѫ�Rj��W����x��$����p$����y6��m�#��~�ƢQ��7����C8I�{��c��q�
{
  volatile int    cont = 0;
  Frames         *aux;
  for(aux = frames_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID2)
      return (aux);
  return (NULL);
}


/****************************
      [FRAMES]
  Define para onde o frame
  ira pular quando sair dele
*****************************/
Animation :: Frames* Animation :: Frames :: getSubAnimation(int ID2)
{
  volatile int    cont = 0;
  Frames         *aux;
  for(aux = frames_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID2 && aux->SUB_ANIMATION)
      return (aux);
  return (NULL);
}



/****************************
      [FRAMES]
  verifica se um frame com a
  ID de parametro esta com
  trava ou nao
*****************************/
bool Animation :: Frames :: isLocked(int ID2)
{
  Frames *aux;
  for(aux = frames_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID2)
      return (aux->lock);
}


/****************************
       [FRAMES]
         LOAD
*****************************/
void Animation :: Frames :: load(char *path2, long int x, long int y, int ID2, bool loop2, bool lock2, ALLEGRO_COLOR col)
{
  New();
  if( !(frames_fim->Bitmap :: open(path2, col)) )
    OPEN_ERROR(path2, "Animation.h");
  
  frames_fim->path = (char *)malloc(strlen(path2) + 1);
  strcpy(frames_fim->path, path2);
  frames_fim->dif_x = x;
  frames_fim->dif_y = y;
  frames_fim->ID    = ID2;
  frames_fim->loop  = loop2;
  frames_fim->lock  = lock2;
  frames_fim->JUMP_TO        = false;
  frames_fim->JUMP_TO_ID     = 0;
  frames_fim->JUMP_TO_FRAME  = 0;
  frames_fim->SUB_ANIMATION  = false;
  frames_fim->PRINT_SUB_ANIMATION = false;
  
  /*Calculo o indice do frame*/
  if(frames_fim != frames_ini)
  {
    if(frames_fim->ID == frames_fim->ante->ID)
      frames_fim->index = frames_fim->ante->index + 1;
    else
      frames_fim->index = 0;/*Novo tipo, deve comecar com indice 0*/
  }
  else
    frames_fim->index = 0;
}

