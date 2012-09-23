
#include <stdio.h>

#define CONFIGURATION_DATA_SIZE  500
#define CONFIGURATION_FILE       "allegro5_config.txt"
#define IMAGE_ADDON              "IMAGE_ADDON"
#define AUDIO_ADDON              "AUDIO_ADDON"
#define FONT_ADDON               "FONT_ADDON"
#define FONT_TTF_ADDON           "FONT_TTF_ADDON"
#define PRIMITIVES_ADDON         "PRIMITIVES_ADDON"
#define INSTALL_MOUSE            "INSTALL_MOUSE"
#define INSTALL_KEYBOARD         "INSTALL_KEYBOARD"
#define DEFAULT_TIMER            "DEFAULT_TIMER"
#define FULLSCREEN               "FULLSCREEN"
#define SCREEN                   "SCREEN"



bool                    USING_PRIMITIVE_ADDON  = false,
                        USING_IMAGE_ADDON      = false,
                        USING_AUDIO_ADDON      = false,
                        USING_FONT_ADDON       = false,
                        USING_TTF_ADDON        = false,
                        USING_MOUSE            = false,
                        USING_KEYBOARD         = false,
                        USING_DISPLAY          = false;
unsigned long int       MAX_SAMPLES            = 0;

void Create_Display(int w, int h)
{
  display = al_create_display(w, h);
  if(!display)
    FATAL_ERROR("failed to initialize display!", "allegro5_init.h");
  al_set_target_bitmap(al_get_backbuffer(display));
  al_register_event_source(eventos_globais, al_get_display_event_source(display));
  USING_DISPLAY = true;
}

void allegro5_config()
{
  char            c,
                  value[CONFIGURATION_DATA_SIZE],
                  aux_value[CONFIGURATION_DATA_SIZE*2];
  volatile int    i, i2, i3,
                  row;
  int             n1, n2;
  bool            terminou = false;
  FILE           *arq;
  
  arq = fopen(CONFIGURATION_FILE, "r");
  if(arq == NULL)
    OPEN_ERROR(CONFIGURATION_FILE, "allegro5_config");
  row = 1;
  i   = 0;
  while(!feof(arq) && !terminou)
  {
    
    do c = fgetc(arq); while((c == ' ' || c == '\n') && !feof(arq));
    if(feof(arq)) break;
    
    i = 1;
    value[0] = c;
    do value[i++] = fgetc(arq); while(value[i-1] != ';' && !terminou);
    value[i-1] = '\0';
    
    if(strcmp(value, IMAGE_ADDON) == 0)
    {
      if(!al_init_image_addon())
        FATAL_ERROR("failed to initialize image addon!", "allegro5_init.h");
      USING_IMAGE_ADDON = true;
    }
    
    else if(strcmp(value, FONT_ADDON) == 0)
    {
      al_init_font_addon();
      USING_FONT_ADDON = true;
    }
    
    else if(strcmp(value, FONT_TTF_ADDON) == 0)
    {
      if(!al_init_ttf_addon())
       FATAL_ERROR("failed to initialize font addon!", "allegro5_init.h");
      USING_TTF_ADDON = true;
    }
    else if(strcmp(value, INSTALL_MOUSE) == 0)
    {
      if(!al_install_mouse())
        FATAL_ERROR("failed to initialize mouse!", "allegro5_init.h");
      al_register_event_source(eventos_globais, al_get_mouse_event_source());
      USING_MOUSE = true;
    }
    else if(strcmp(value, INSTALL_KEYBOARD) == 0)
    {
      if(!al_install_keyboard())
        FATAL_ERROR("failed to initialize keyboard!", "allegro5_init.h");
      al_register_event_source(eventos_globais, al_get_keyboard_event_source());
      USING_KEYBOARD = true;
    }
    else if(strcmp(value, PRIMITIVES_ADDON) == 0)
    {
      if(!al_init_primitives_addon())
       FATAL_ERROR("\nfalha ao iniciar addon das primitivas", "allegro5_init.h");
      USING_PRIMITIVE_ADDON = true;
    }
    else if(strcmp(value, FULLSCREEN) == 0)
    {
      al_get_monitor_info(0, &monitor_info);
      SCREEN_W = monitor_info.x2 - monitor_info.x1;
      SCREEN_H = monitor_info.y2 - monitor_info.y1;
      Create_Display(SCREEN_W, SCREEN_H);
    }
/******************************
  Se nao for nehuma das palavras
    reservadas, entao é um comando
    com parametro
******************************/
    else
    {
      for(i2 = 0;i2 < strlen(value);i2++)
      {
        aux_value[i2]   = value[i2];
        aux_value[i2+1] = '\0';
        
        /*Comando SCREEN*/
        if(strcmp(aux_value, SCREEN) == 0)
        {
          /*Armazeno o SCREEN_W*/
          i3 = i2;
          while((int)value[i3] < 48 || (int)value[i3] > 58) i3++;
          aux_value[0] = value[i3++];
          i2 = 1;
          do aux_value[i2++] = value[i3++]; while((int)value[i3] >= 48 && (int)value[i3] <= 58);
          aux_value[i2] = '\0';
          SCREEN_W = atoi(aux_value);
          
          /*Armazeno o SCREEN_H*/
          while((int)value[i3] < 48 || (int)value[i3] > 58) i3++;
          aux_value[0] = value[i3++];
          i2 = 1;
          do aux_value[i2++] = value[i3++]; while((int)value[i3] >= 48 && (int)value[i3] <= 58);
          aux_value[i2] = '\0';
          SCREEN_H = atoi(aux_value);
          /*Crio o Display*/
          Create_Display(SCREEN_W, SCREEN_H);
          break;
        }
        /*******************************************
          Caso o valor seja relativo ao timer geral
        ********************************************/
        else if(strcmp(aux_value, DEFAULT_TIMER) == 0)
        {
          i3 = i2;
          while((int)value[i3] < 48 || (int)value[i3] > 58)
          {
            /**********************************************
              Caso nao encontre parametro, o valor para o
                timer sera valor padrao(1)
            ***********************************************/
            if(i3 == strlen(value)) break;
            i3++;
          }
          /*Encontrou algum valor*/
          if(i3 < strlen(value))
          {
            aux_value[0] = value[i3++];
            i2 = 1;
            /*Leio os dois parametros*/
            for(int i = 0;i < 2;i++)
            {
              while(((int)value[i3] >= 48 && (int)value[i3] <= 58) || value[i3] == '.')
                aux_value[i2++] = value[i3++];
              aux_value[i2] = '\0';
              if(i == 0)
                GLOBAL_TIMER = atof(aux_value);
              else
                FPS = atoi(aux_value);
              i2 = 0;
              while((int)value[i3] < 48 || (int)value[i3] > 58) i3++;
            }
          }
          /*Se nao houver parametro, reseto para valores padrao*/
          else
          {
            GLOBAL_TIMER = 1.0;
            FPS = 60;
          }
          break;
        }
        
        /********************************************
          Valor para iniciar o addon de audio
        ********************************************/
        else if(strcmp(aux_value, AUDIO_ADDON) == 0)
        {
          i3 = i2;
          while((int)value[i3] < 48 || (int)value[i3] > 58)
          {
            /**********************************************
            Nao encontrou valor para resevar os samples,
              entao o valor sera o padrao(10)
            ***********************************************/
            if(i3 == strlen(value)) break;
            i3++;
          }
          /*Encontrou algum valor*/
          if(i3 < strlen(value))
          {
            aux_value[0] = value[i3++];
            i2 = 1;
            do aux_value[i2++] = value[i3++]; while((int)value[i3] >= 48 && (int)value[i3] <= 58);
            aux_value[i2] = '\0';
            MAX_SAMPLES = atoi(aux_value);
          }
          /*Caso contrario, sera o valor padrao*/
          else
          {
            MAX_SAMPLES = 10;
            al_show_native_message_box(
              NULL, 
              "Erro de script", "ERROR", "MAX_SAMPLES = 10", NULL, 0);
          }
          
          if(!al_install_audio() || !al_init_acodec_addon())
            FATAL_ERROR("nao pode iniciar 'audio addon'", "allegro5_config.h");
          al_reserve_samples(MAX_SAMPLES);
          USING_AUDIO_ADDON = true;
          break;
        }
        /********************************************
        Script desconhecido: mostro oque foi lido
          juntamente com a linha onde o erro foi
          encontrado
        *********************************************/
        else if(i2 == strlen(value) - 1)
        {
          strcpy(aux_value, "Script desconhecido: \"");
          strcat(aux_value, value);
          strcat(aux_value, "\"");
          itoa(row, value, 10);
          strcat(aux_value, "\nLinha: ");
          strcat(aux_value, value);
          al_show_native_message_box(
            NULL, 
            "Erro de script", "ERROR", aux_value, NULL, 0);
          break;
        }
      }
    }
    row++;
  }
}
