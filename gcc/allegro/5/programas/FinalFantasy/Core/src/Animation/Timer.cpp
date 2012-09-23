


/********************************
           [Timer]
********************************/
struct Animation :: Timer
{
  unsigned long int      ID;
  double                 interval;
  ALLEGRO_TIMER         *timer;
  bool                   SUB_ANIMATION;
  Timer                 *prox, *ante;
  void New(int ID, double interval2);
  
  void start(int ID);
  void startSubAnimation(int ID);
  
  void stop(int ID);
  void stopSubAnimation(int ID);
  
  ALLEGRO_TIMER *getTimer(int ID);
  ALLEGRO_TIMER *getSubAnimationTimer(int ID);
};Animation :: Timer    *timer_ini = NULL,
                        *timer_fim = NULL, 
                        *timer_aux = NULL,
                         animation_timer;

ALLEGRO_TIMER* Animation :: Timer :: getSubAnimationTimer(int ID)
{
  Timer *aux;
  for(aux = timer_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID && aux->SUB_ANIMATION)
      return (aux->timer);
}
/****************************
      [Timer]
      Starta o timer
*****************************/
void Animation :: Timer :: start(int ID)
{
  Timer *aux;
  for(aux = timer_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID)
    {
      al_start_timer(aux->timer);
      break;
    }
}

/****************************
      [Timer]
      Starta o timer de uma
      sub-animacao
*****************************/
void Animation :: Timer :: startSubAnimation(int ID)
{
  Timer *aux;
  for(aux = timer_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID && aux->SUB_ANIMATION)
    {
      al_start_timer(aux->timer);
      break;
    }
}


/****************************
      [Timer]
      Para o timer
*****************************/
void Animation :: Timer :: stop(int ID)
{
  Timer *aux;
  for(aux = timer_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID)
    {
      al_stop_timer(aux->timer);
      break;
    }
}

/****************************
      [Timer]
      Para o timer de uma
      sub-animacao
*****************************/
void Animation :: Timer :: stopSubAnimation(int ID)
{
  Timer *aux;
  for(aux = timer_ini;aux != NULL;aux = aux->prox)
    if(aux->ID == ID && aux->SUB_ANIMATION)
    {
      al_stop_timer(aux->timer);
      break;
    }
}




/****************************
      [Timer]
  Alocar um novo bloco
  criando um novo timer e
  o adicionando a fila de
  eventos 
*****************************/
void Animation :: Timer :: New(int ID, double interval2)
{
  if(timer_ini == NULL)
  {
    timer_ini = (Timer *)malloc(sizeof(struct Timer));
    timer_ini->prox = timer_ini->ante = NULL;
    timer_aux = timer_fim = timer_ini;
  }
  else
  {
    timer_aux = timer_fim;
    timer_fim = (Timer *)malloc(sizeof(struct Timer));
    timer_fim->prox = NULL;
    timer_fim->ante = timer_aux;
    timer_aux->prox = timer_fim;
    timer_aux = timer_fim;
  }
  timer_aux->ID = ID;
  timer_aux->interval = interval2;
  timer_aux->timer = al_create_timer(timer_aux->interval);
  timer_aux->SUB_ANIMATION = false;
  al_register_event_source(eventos_globais, al_get_timer_event_source(timer_aux->timer));
}


/****************************
      [Timer]
  Alocar um novo bloco
*****************************/
ALLEGRO_TIMER* Animation :: Timer :: getTimer(int ID)
{
  Timer *aux;
  volatile int cont = 0;
  for(aux = timer_ini;aux != NULL;aux = aux->prox)
  {
    if(aux->ID == ID)
      return (aux->timer);
  }
  return (NULL);
}
