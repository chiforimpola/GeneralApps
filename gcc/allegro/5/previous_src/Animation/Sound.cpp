

struct Animation :: Sound
{
  unsigned long int   ID,
                      i_index,
                      index[ANIMATION_MAX_SPRITES];/*lista de indices que devera tocar*/
  double              vol;
  char               *path;
  ALLEGRO_SAMPLE     *snd;
  Sound              *prox, *ante;
  
  void New();
  void init(char *path2, double vol2, unsigned long int ID2);
  void play();
  bool PlayOnIndex(unsigned long int index2);
  
  void setNewIndex(int n);
};Animation :: Sound    *snd_ini = NULL,
                        *snd_fim = NULL,
                        *snd_aux = NULL,
                         animation_snd;


/************************
  Toca um determinado
  sample baseado em sua
  ID
************************/
void Animation :: Sound :: setNewIndex(int n)
{
  snd_fim->index[snd_fim->i_index++] = n;
}



/************************
  Toca um determinado
  e diz que aquele index
  esta tocando. Isto
  servira para evitar
  que o mesmo frame
  toque o audio varias
  vezes
************************/
void Animation :: Sound :: play()
{
  al_play_sample(snd, vol, 0.0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}


/************************
  Retorna true se o sample
  devera tocar no indice
  de parametro, caso
  contrario retorna false
************************/
bool Animation :: Sound :: PlayOnIndex(unsigned long int index2)
{
  volatile int i;
  char aux[100];
  
  /*for(i = 0;i < i_index;i++)
  {
      if(ID == 1)
      {
        itoa(index2, aux, 10);
        al_show_native_message_box(NULL, "SND PLAYONINDEX", "teste", aux, NULL, 0);
      }
  }
  exit(0);*/
  
  for(i = 0;i < i_index;i++)
    if(index[i] == index2)
      return (true);
  return (false);
}


/************************
    Instancia a struct
************************/
void Animation :: Sound :: New()
{
  if(snd_ini == NULL)
  {
    snd_ini = (Sound *) malloc(sizeof(struct Sound));
    snd_ini->prox = snd_ini->ante = NULL;
    snd_aux = snd_fim = snd_ini;
  }
  else
  {
    snd_aux = snd_fim;
    snd_fim = (Sound *) malloc(sizeof(struct Sound));
    snd_aux->prox = snd_fim;
    snd_fim->prox = NULL;
    snd_fim->ante = snd_aux;
    snd_aux = snd_fim;
  }
}




/************************
    Vai instanciar a
    struct e abrir o
    sample
************************/
void Animation :: Sound :: init(char *path2, double vol2, unsigned long int ID2)
{
  New();
  snd_fim->snd = al_load_sample(path2);
  if(snd_fim->snd == NULL) OPEN_ERROR(path2, "Animation :: Sound");
  
  snd_fim->path = (char *)malloc(strlen(path2) + 1);
  snd_fim->ID   = ID2;
  snd_fim->vol  = vol2;
  snd_fim->i_index = 0;
}


