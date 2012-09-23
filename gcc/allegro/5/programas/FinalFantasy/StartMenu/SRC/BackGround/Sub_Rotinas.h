
/**************************
    Carregara o som e as
    imagens
**************************/
void BackGround :: load()
{
  char *aux = (char *)malloc(strlen(path) + strlen(name) + 5);
  
  strcpy(aux, path);
  strcat(aux, "\\");
  strcat(aux, name);
  if( !(Bitmap :: open(aux, INVISIBLE)) )
    OPEN_ERROR(aux, "Sub_Rotinas.h");
  free(aux);
  
  aux = (char *)malloc(strlen(path) + strlen(bgmusic) + 5);
  strcpy(aux, path);
  strcat(aux, "\\");
  strcat(aux, bgmusic);
  if( !(Sound :: open(aux)) )
    OPEN_ERROR(aux, "Sub_Rotinas.h");
  free(aux);
}



/*************************************
  Leitura do arquivo de configuracao
*************************************/
void BackGround :: readConfiguration()
{
  char           value[100],
                 c;
  volatile int   i;
  if(conf_file != NULL)
  {
    i = 0;
    while( !feof(conf_file) )
    {
      c = fgetc(conf_file);
      /*****************
          Comentario
      ******************/
      if(c == ';') while( (fgetc(conf_file)) != '\n' ){ }
      /*********************************
          Qual o tipo de configuracao
      **********************************/
      else if(c == '[')
      {
        i = 0;
        do value[i++] = fgetc(conf_file); while(value[i-1] != ']');
        value[i-1] = '\0';
        
        if( strcmp(value, BACK_GROUND_INFO)   == 0 ) readInfo();
        if( strcmp(value, BACK_GROUND_CAMERA) == 0 ) readCamera();
        if( strcmp(value, BACK_GROUND_PLAYER) == 0 ) readPlayer();
        if( strcmp(value, BACK_GROUND_SCREEN) == 0 ) readScreen();
        if( strcmp(value, BACK_GROUND_MUSIC)  == 0 ) readMusic();
      }
    }
  }
}


/**************************
  Sub-Rotina para ler INFO
**************************/
void BackGround :: readInfo()
{
  char           type[100],
                 value[100],
                 c;
  volatile int   i, i2;
  bool           terminou = false;
  name        = NULL;
  displayname = NULL;
  while(!terminou)
  {
    do type[0] = fgetc(conf_file); while(type[0] == ' ' || type[0] == '\n');
    
    i = 1;
    do type[i++] = fgetc(conf_file); while(type[i-1] != ' ' && type[i-1] != '=');
    type[i-1] = '\0';
    
    do value[0] = fgetc(conf_file); while(value[0] == ' ' || value[0] == '=');
    
    i2 = 1;
    do value[i2++] = fgetc(conf_file); while(value[i2-1] != '\n');
    value[i2-1] = '\0';
    
    /********
      name
    ********/
    if( strcmp(type, "name") == 0 )
    {
      name = (char *)malloc(strlen(value) + 1);
      strcpy(name, value);
    }
    /***************
       displayname
    ****************/
    else if( strcmp(type, "displayname") == 0 )
    {
      displayname = (char *)malloc(strlen(value) + 1);
      strcpy(displayname, value);
    }
    /******************************
      Terminou de ler os atributos
    ******************************/
    if(name != NULL && displayname != NULL)
     terminou = true;
  }
}


/**************************
  Sub-Rotina para ler Camera
**************************/
void BackGround :: readCamera()
{
  char           type[100],
                 value[100],
                 c;
  volatile int   i, i2;
  bool           terminou = false;
  
  startx        = -1;
  starty        = -1;
  floortension  = -1;
  tension       = -1;
  
  while(!terminou)
  {
    do type[0] = fgetc(conf_file); while(type[0] == ' ' || type[0] == '\n');
    
    i = 1;
    do type[i++] = fgetc(conf_file); while(type[i-1] != ' ' && type[i-1] != '=');
    type[i-1] = '\0';
    
    do value[0] = fgetc(conf_file); while(value[0] == ' ' || value[0] == '=');
    
    i2 = 1;
    do value[i2++] = fgetc(conf_file); while(value[i2-1] != '\n');
    value[i2-1] = '\0';
    
    /********
      startx
    ********/
    if( strcmp(type, "startx") == 0 )
      startx = atoi(value);

    /********
      starty
    ********/
    else if( strcmp(type, "starty") == 0 )
      starty = atoi(value);
      
    /******************
        tension
    *******************/
    else if( strcmp(type, "tension") == 0 )
      tension = atoi(value);
      
    /******************
        floortension
    *******************/
    else if( strcmp(type, "floortension") == 0 )
      floortension = atoi(value);
    
    /******************************
      Terminou de ler os atributos
    ******************************/
    if(startx != -1 && starty != -1 && floortension != -1 && tension != -1)
     terminou = true;
  }
}



/**************************
  Sub-Rotina para ler Player
**************************/
void BackGround :: readPlayer()
{
  char           type[100],
                 value[100],
                 c;
  volatile int   i, i2;
  short int      operador;/*
                           -1 = Nao ha operador
                            0 = +
                            1 = -
                            2 = *
                            3 = /
                          */
  bool           terminou = false;
  
  pstartx        = -1;
  pstarty        = -1;
  pfacing        = -1;
  
  while(!terminou)
  {
    do type[0] = fgetc(conf_file); while(type[0] == ' ' || type[0] == '\n');
    
    i = 1;
    do type[i++] = fgetc(conf_file); while(type[i-1] != ' ' && type[i-1] != '=');
    type[i-1] = '\0';
    
    do value[0] = fgetc(conf_file); while(value[0] == ' ' || value[0] == '=');
    
    i2 = 1;
    do value[i2++] = fgetc(conf_file); while(value[i2-1] != '\n');
    value[i2-1] = '\0';
    
    if( strcmp(type, "pstartx") == 0 )
        pstartx = atoi(value);

    else if( strcmp(type, "pstarty") == 0 )
      pstarty = atoi(value);
      
    
    else if( strcmp(type, "pfacing") == 0 )
      pfacing = atoi(value);
    
    
    /******************************
      Terminou de ler os atributos
    ******************************/
    if(pstartx != -1 && pstarty != -1 && pfacing != -1)
     terminou = true;
  }
}


/**************************
  Sub-Rotina para ler Screen
**************************/
void BackGround :: readScreen()
{
  char           type[100],
                 value[100],
                 c;
  volatile int   i, i2;
  bool           terminou = false;
  
  screenleft        = -1;
  screenright       = -1;
  zoffset           = -1;
  
  while(!terminou)
  {
    do type[0] = fgetc(conf_file); while(type[0] == ' ' || type[0] == '\n');
    
    i = 1;
    do type[i++] = fgetc(conf_file); while(type[i-1] != ' ' && type[i-1] != '=');
    type[i-1] = '\0';
    
    do value[0] = fgetc(conf_file); while(value[0] == ' ' || value[0] == '=');
    
    i2 = 1;
    do value[i2++] = fgetc(conf_file); while(value[i2-1] != '\n');
    value[i2-1] = '\0';
    
    
    if( strcmp(type, "screenleft") == 0 )
      screenleft = atoi(value);

    
    else if( strcmp(type, "screenright") == 0 )
      screenright = atoi(value);
      
    
    else if( strcmp(type, "zoffset") == 0 )
      zoffset = atoi(value);
    
    /******************************
      Terminou de ler os atributos
    ******************************/
    if(screenleft != -1 && screenright != -1 && zoffset != -1)
     terminou = true;
  }
}



/**************************
  Sub-Rotina para ler Music
**************************/
void BackGround :: readMusic()
{
  char           type[100],
                 value[100],
                 c;
  volatile int   i, i2;
  bool           terminou = false;
  
  bgmusic  = NULL;
  bgvolume = 0;
  
  while(!terminou)
  {
    do type[0] = fgetc(conf_file); while(type[0] == ' ' || type[0] == '\n');
    
    i = 1;
    do type[i++] = fgetc(conf_file); while(type[i-1] != ' ' && type[i-1] != '=');
    type[i-1] = '\0';
    
    do value[0] = fgetc(conf_file); while(value[0] == ' ' || value[0] == '=');
    
    i2 = 1;
    do value[i2++] = fgetc(conf_file); while(value[i2-1] != '\n');
    value[i2-1] = '\0';
    
    
    if( strcmp(type, "bgmusic") == 0 )
    {
      bgmusic = (char *)malloc(strlen(value) + 1);
      strcpy(bgmusic, value);
    }

    else if( strcmp(type, "bgvolume") == 0 )
      bgvolume = atof(value);
    
    /******************************
      Terminou de ler os atributos
    ******************************/
    if(bgmusic != NULL && bgvolume != 0.0)
     terminou = true;
  }
}
