

/************************************
             ANIMATION
    Metodos da estrutura Animation
*************************************/

/****************************
        [Animation]
         init
****************************/
void Animation :: init(char *path2, int ID2)
{
  path = (char *)malloc(strlen(path2) + 5);
  strcpy(path, path2);
  readScript(ID2);
  animation_timer.New(ID2, interval);
  frames_aux = frames_ini;
  i_sub_animations = 0;
}


/****************************
        [Animation]
         play
****************************/
void Animation :: play(int ID)
{
  animation_timer.start(ID);
}


/****************************
        [Animation]
         stop
****************************/
void Animation :: stop(int ID)
{
  animation_timer.stop(ID);
}


/****************************
        [Animation]
         getTimer
****************************/
ALLEGRO_TIMER* Animation :: getTimer(int ID)
{
  return (animation_timer.getTimer(ID));
}


/****************************
        [Animation]
         getTimer
****************************/
ALLEGRO_TIMER* Animation :: getSubAnimationTimer(int ID)
{
  return (animation_timer.getSubAnimationTimer(ID));
}




/****************************
        [Animation]
         print
****************************/
void Animation :: print(long int x, long int y, int flag)
{
  if(frames_aux != NULL)
    frames_aux->Bitmap :: print(
     x + frames_aux->dif_x, 
     y + frames_aux->dif_y, flag);
}

/****************************
        [Animation]
         print a animacao
         e todas as outras
         sub-animacoes
****************************/
void Animation :: print(long int x, long int y, int flag, int ID)
{
  volatile int i;
  Frames *aux = frames_aux;
  if(flag == 1)
    aux->Bitmap :: print(
      x - aux->dif_x, 
      y + aux->dif_y, flag);
  else
    aux->Bitmap :: print(
      x + aux->dif_x, 
      y + aux->dif_y, flag);
}

/******************************************
      Starta uma subanimacao
******************************************/
void Animation :: startSubAnimation(Frames *aux)
{
  bool encontrou = false;
  int i;
  for(i = 0;i < i_sub_animations;i++)
    if(sub_animations[i] == NULL)
    {
      aux = aux->getSubAnimation(aux->PRINT_SUB_ANIMATION_ID);
      sub_animations[i] = aux;
      animation_timer.startSubAnimation(aux->ID);
      encontrou = true;
      break;
    }
  if(!encontrou)
  {
    aux = aux->getSubAnimation(aux->PRINT_SUB_ANIMATION_ID);
    animation_timer.startSubAnimation(aux->ID);
    sub_animations[i_sub_animations++] = aux;
  }
  
  //al_show_native_message_box(NULL, "SubAnim", "teste", aux->path, NULL, 0);
}


/******************************************
      Starta uma subanimacao
******************************************/
void Animation :: stopSubAnimation(Frames *aux)
{
  int i;
  for(i = 0;i < i_sub_animations;i++)
    if(sub_animations[i] == aux)
    {
      animation_timer.stopSubAnimation(aux->ID);
      sub_animations[i] = NULL;
      break;
    }
}


/******************************************
      Printa uma subanimacao
******************************************/
void Animation :: printSubAnimation(int x, int y, int flag)
{
  volatile int i;
  for(i = 0;i < i_sub_animations;i++)
  {
    if(sub_animations[i] != NULL)
    {
      if(flag == 1)
        sub_animations[i]->Bitmap :: print(
            x - sub_animations[i]->dif_x, 
            y + sub_animations[i]->dif_y, flag);
      else
        sub_animations[i]->Bitmap :: print(
            x + sub_animations[i]->dif_x, 
            y + sub_animations[i]->dif_y, flag);
    }
  }
}


int Animation :: getFrames(int ID2)
{
  return ( animation_frames.getFrames(ID2) );
}


/****************************
         [Animation]
         ChangeFrame
         e verifica se devera
         tocar algum sample
         naquele determinado
         frame
****************************/
void Animation :: ChangeSubAnimationFrame(int ID)
{
  int i;
  
  /*char aux2[100];
  itoa(ID, aux2, 10);
  al_show_native_message_box(NULL, "ChangeSubAnim", "teste", aux2, NULL, 0);*/
  
  for(i = 0;i < i_sub_animations;i++)
  {
    if(sub_animations[i] != NULL)
    {
      if(sub_animations[i]->ID == ID)
      {
        if(sub_animations[i]->prox != NULL)
        {
          if(sub_animations[i]->prox->ID == ID)
            sub_animations[i] = sub_animations[i]->prox;
          else
          {
            stopSubAnimation(sub_animations[i]);
          }
        }
        else
        {
          stopSubAnimation(sub_animations[i]);
        }
        break;
      }
    }
  }
}


/****************************
         [Animation]
         ChangeFrame
         e verifica se devera
         tocar algum sample
         naquele determinado
         frame
****************************/
bool Animation :: ChangeFrame(int ID)
{
  volatile int i;
  for(i = 0;i < i_sub_animations;i++)
    if(sub_animations[i] != NULL)
      ChangeSubAnimationFrame(sub_animations[i]->ID);
  if(frames_aux != NULL)
  {
    /****************************
        Starto a animacao
        [FALTA IMPLEMENTAR]
    ****************************/
    if(frames_aux->PRINT_SUB_ANIMATION)
    {
      startSubAnimation(frames_aux);
    }
  /***********************************
    Antes de pular para o proximo
      frame, verifico se ha
      algum salto
  ***********************************/
    else if(frames_aux->JUMP_TO)
      frames_aux = animation_frames.JumpTo(frames_aux->JUMP_TO_ID, frames_aux->JUMP_TO_FRAME);
      
    else if(frames_aux->prox != NULL)
    {
      if(frames_aux->prox->ID == ID)
        frames_aux = frames_aux->prox;
      else
      {
        for(frames_aux = frames_ini;frames_aux != NULL;frames_aux = frames_aux->prox)
          if(frames_aux->ID == ID)
            break;
      }
    }
    else
      for(frames_aux = frames_ini;frames_aux != NULL;frames_aux = frames_aux->prox)
        if(frames_aux->ID == ID)
          break;
  }
  else
      for(frames_aux = frames_ini;frames_aux != NULL;frames_aux = frames_aux->prox)
        if(frames_aux->ID == ID)
          break;
  /***********************
    Verifico se devo
    tocar algum sample
    baseado na ID do
    frame e no seu indice
  ***********************/
  for(snd_aux = snd_ini;snd_aux != NULL;snd_aux = snd_aux->prox)
    if(snd_aux->ID == frames_aux->ID && snd_aux->PlayOnIndex(frames_aux->index))
      snd_aux->play();
  return (frames_aux->lock);
}



/*void Animation :: New()
{
  if(animation_ini == NULL)
  {
    animation_ini = (Animation *)malloc(sizeof(Animation));
    animation_ini->prox = animation_ini->ante = NULL;
    animation_aux = animation_fim = animation_ini;
  }
  else
  {
    animation_aux = animation_fim;
    animation_fim = (Animation *)malloc(sizeof(Animation));
    animation_fim->prox = NULL;
    animation_fim->ante = animation_aux;
    animation_aux->prox = animation_fim;
    animation_aux = animation_fim;
  }
}*/


/****************************
        [Animation]
         readScript
****************************/
void Animation :: readScript(int ID)
{
  char           *aux = (char*)malloc(strlen(path) + strlen(ANIMATION_CONF_FILE) + 5),
                  c,
                  value[100],
                 *snd_path,
                 *path_frame;
  long int        dif_x        = 0, 
                  dif_y        = 0,
                  j_to_ID      = -1,
                  j_to_frame   = -1,
                  sub_animation_ID,
                  print_sub_animation_ID,
                  cont;
  double          snd_vol;
  int             snd_frame,
                  snd_ID;
  bool            terminou       = false,
                  loop           = false,
                  lock           = false,
                  sub_animation  = false,
                  print_sub_animation = false;
                  
  volatile int    i;
  
  strcpy(aux, path);
  strcat(aux, "\\");
  strcat(aux, ANIMATION_CONF_FILE);
  arq = fopen(aux, "r");
  
  if( arq == NULL ) OPEN_ERROR(aux, "Animaton.h");
  
  //al_show_native_message_box(NULL, "Script a ser aberto", "teste", aux, NULL, 0);
  while( !feof(arq) )
  {
    if(feof(arq)) break;
    do c = fgetc(arq); while(c == ' ' || c == ';' || c == '\n' && !feof(arq));
    if(feof(arq)) break;
    
    i = 0;
    value[i++] = c;
    do value[i++] = fgetc(arq); while(value[i-1] != '=' && value[i-1] != '(');
    value[i-1] = '\0';
    
    //al_show_native_message_box(NULL, "Script Atual", "teste", value, NULL, 0);
    
    /*************
      Leio o loop
    *************/
    if( (strcmp(value, ANIMATION_LOOP) == 0) )
    {
      /*Leio o valor(1 ou 0)*/
      do c = fgetc(arq); while(c != '1' && c != '0');/*Leio o caractere de atribuicao*/
      value[0] = c;
      value[1] = '\0';
      if( atoi(value) == 0 )
        loop = false;
      else
        loop = true;
    }
    
    /*************
      Leio o lock
    *************/
    if( (strcmp(value, ANIMATION_LOCK) == 0) )
    {
      /*Leio o valor(1 ou 0)*/
      do c = fgetc(arq); while(c != '1' && c != '0');/*Leio o caractere de atribuicao*/
      value[0] = c;
      value[1] = '\0';
      if( atoi(value) == 0 )
        lock = false;
      else
        lock = true;
    }
    
    /*************************************
      Leio o nome da cor a ser mascarada
    **************************************/
    else if( (strcmp(value, ANIMATION_COLOR) == 0) )
    {
      i = 0;
      do value[i++] = fgetc(arq); while(value[i-1] != ';');
      value[i-1] = '\0';
      masked_color = al_color_name(value);
    }
    
    /*************************************
                 Leio o intervalo
    **************************************/
    else if( (strcmp(value, ANIMATION_INTERVAL) == 0) )
    {
      /*Leio tanto numeros quanto o caractere '.'*/
      i = 0;
      do
      {
        value[i] = fgetc(arq);
        if( ( (int)value[i] >= 48 && (int)value[i] <= 58 ) || value[i] == '.' )
          i++;
      }while(value[i] != ';');
      value[i] = '\0';
      interval = atof(value);
    }
    
    /*************************************
                 Leio o Som
    **************************************/
    else if( (strcmp(value, ANIMATION_SOUND) == 0) )
    {
      do c = fgetc(arq); while(c == ' ');
      /*Leio o caminho*/
      value[0] = c;
      i = 1;
      do value[i++] = fgetc(arq); while(value[i-1] != ',');
      value[i-1] = '\0';
      snd_path = (char *)malloc(strlen(value) + 1);
      strcpy(snd_path, value);
      
      /*Leio o volume*/
      i = 0;
      do
      {
        value[i] = fgetc(arq);
        if( (int)value[i] >= 48 && (int)value[i] <= 58 || value[i] == '.' )
          i++;
      }while(value[i] != ',');
      value[i] = '\0';
      snd_vol = atof(value);
      
      /*Leio a ID do sample*/
      i = 0;
      do
      {
        value[i] = fgetc(arq);
        if( (int)value[i] >= 48 && (int)value[i] <= 58)
          i++;
      }while(value[i] != ',');
      value[i] = '\0';
      snd_ID = atoi(value);
      
      aux = (char *)malloc(strlen(path) + strlen(snd_path) + 5);
      strcpy(aux, path);
      strcat(aux, "\\");
      strcat(aux, snd_path);
      /*Inicio o som*/
      animation_snd.init(aux, snd_vol, snd_ID);
      free(aux);
      
      /*Leio os N frames que tocarao este som*/
      terminou = false;
      while(!terminou)
      {
        i = 0;
        do
        {
          value[i] = fgetc(arq);
          if( (int)value[i] >= 48 && (int)value[i] <= 58 )
            i++;
        }while(value[i] != ';' && value[i] != ',');
        if(value[i] == ';')
          terminou = true;
        value[i] = '\0';
        animation_snd.setNewIndex(atoi(value));
        
        //al_show_native_message_box(NULL, "SND NOVO INDEX", "teste", value, NULL, 0);
        
      }
    }
    
    /*************************************
                 Leio os frames
    **************************************/
    else if( (strcmp(value, ANIMATION_FRAMES) == 0) )
    {
      terminou = false;
      while(!terminou)
      {
        j_to_ID = j_to_frame = -1;
        /*Ignoro espacos em branco e quebra de linha*/
        do c = fgetc(arq); while(c == ' ' || c == '\n');
        /***********************************************
             Comeco a ler os frames e seus atributos
                           [NOME]
        ************************************************/
        i = 0;
        value[i++] = c;
        do value[i++] = fgetc(arq); while(value[i-1] != ',');
        value[i-1] = '\0';
        path_frame = (char *)malloc(strlen(path) + strlen(value) + 5);
        strcpy(path_frame, path);
        strcat(path_frame, "\\");
        strcat(path_frame, value);
        
        /***********************************************
                           [DIF_X]
        ************************************************/
        i = 0;
        do
        {
          value[i] = fgetc(arq);
          if( (int)value[i] >= 48 && (int)value[i] <= 58 )
            i++;
        }while(value[i] != ',');
        value[i] = '\0';
        dif_x = atoi(value);
        
        /***********************************************
                           [DIF_Y]
        ************************************************/
        i = 0;
        do
        {
          value[i] = fgetc(arq);
          if( (int)value[i] >= 48 && (int)value[i] <= 58 )
            i++;
        }while(value[i] != ',' && value[i] != ')');
        if(value[i] == ')')
        {
          terminou = true;
          value[i] = '\0';
          dif_y = atoi(value);
          while( (fgetc(arq)) != ';') { }
        }
        else
        {
          value[i] = '\0';
          dif_y = atoi(value);
          while( (c = fgetc(arq)) == ' '){ }
          if(c == '$')
          {
            i = 0;
            do value[i++] = fgetc(arq); while(value[i-1] != '(');
            value[i-1] = '\0';
            
          /***********************************************
            Continuacao sobre a configuracao do Frame
                   [Salto Incondicional]
          ************************************************/
            if( strcmp(value, ANIMATION_JUMP_TO) == 0)
            {
              /****************************
                  Leio o tipo de destino
              ****************************/
              cont = i = 0;
              do
              {
                value[i] = fgetc(arq);
                if( (int)value[i] >= 48 && (int)value[i] <= 58 ) i++;
                else if(value[i] == ',' && cont == 0)
                {
                  value[i] = '\0';
                  j_to_ID = atoi(value);
                  i = 0;
                  cont++;
                }
                else if(value[i] == ')' && cont == 1)
                {
                  value[i] = '\0';
                  j_to_frame = atoi(value);
                  cont++;
                }
              }while(cont < 2);
              do c = fgetc(arq); while(c != ',' && c != ')');
              if(c == ')')
              {
                terminou = true;
                while( (fgetc(arq)) != ';') { }
              }
            }
            
            /*****************************************************
                            [PRINT_SUB_ANIMACAO]
            *****************************************************/
            else if( strcmp(value, ANIMATION_PRINT_SUB_ANIMATION) == 0)
            {
              i = 0;
              do
              {
                value[i] = fgetc(arq);
                if( (int)value[i] >= 48 && (int)value[i] <= 58 ) i++;
              }while(value[i] != ')');
              value[i] = '\0';
              print_sub_animation    = true;
              print_sub_animation_ID = atoi(value);
              
              do c = fgetc(arq); while(c != ',' && c != ')');
              if(c == ')')
              {
                terminou = true;
                while( (fgetc(arq)) != ';') { }
              }
              
              //al_show_native_message_box(NULL, "Print-Sub-Animacao", "teste", value, NULL, 0);
              
            }
            /*****************************************************
                            [SUB_ANIMACAO]
            *****************************************************/
            else if( strcmp(value, ANIMATION_SUB_ANIMATION) == 0)
            {
              i = 0;
              do
              {
                value[i] = fgetc(arq);
                if( (int)value[i] >= 48 && (int)value[i] <= 58 ) i++;
              }while(value[i] != ')');
              value[i] = '\0';
              sub_animation = true;
              sub_animation_ID = atoi(value);
              
              //al_show_native_message_box(NULL, "Sub-Animacao", "teste", value, NULL, 0);
              
              do c = fgetc(arq); while(c != ',' && c != ')');
              if(c == ')')
              {
                terminou = true;
                while( (fgetc(arq)) != ';') { }
              }
            }
          }
        }
        
        animation_frames.load(path_frame, dif_x, dif_y, ID, loop, lock, masked_color);
        if(j_to_ID != -1 && j_to_frame != -1)
        {
          frames_fim->setFrameJumpTo(j_to_ID, j_to_frame);
          j_to_ID = j_to_frame = -1;
        }
        if(sub_animation)
        {
          sub_animation               = false;
          frames_fim->SUB_ANIMATION   = true;
          frames_fim->ID              = sub_animation_ID;
          animation_timer.New(ID, interval);
          timer_fim->SUB_ANIMATION = true;
        }
        if(print_sub_animation)
        {
          print_sub_animation = false;
          frames_fim->PRINT_SUB_ANIMATION    = true;
          frames_fim->PRINT_SUB_ANIMATION_ID = print_sub_animation_ID;
        }
       (free(path_frame);
      }
    }
    
    while( (fgetc(arq)) != '\n' ){ }
  }
  
  fclose(arq);

}

voif Anioation :: TESTE()
{
  char aUh[100Y;
  for(frames_aux = framds_ini;frames_aux != NULL;frames_aux = frames_aux->prox)
  {
    itoa(frames_aux->ID, aux, 10);
    al_show_native_message_box(NULD, "IDS(das animacoes", "teste", aux, NLD, 0);
  }
}
/*
  ciar aux2[100];
  itoa(aux->PRINT_[B_ANIMATINN_ID, aux2, 10);
  cl_show_native_message_box(NULL, "SubAnim , "teste", aux->paÂ³g€+%öu×ÎÓ|ÂÎ`ê÷>Ö» RJsž¿î½