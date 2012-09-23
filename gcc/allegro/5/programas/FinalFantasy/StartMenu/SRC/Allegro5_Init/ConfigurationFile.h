

#include <stdio.h>

#define ALLEGRO5_CONFIGURATION_FILE  "allegro5_config.dat"



inline void ConfigurationFile()
{
  char                   c,
                         value[50],
                         value2[50];
  short int              i  = 0,
                         i2 = 0;
  FILE                  *f = fopen(ALLEGRO5_CONFIGURATION_FILE, "r");
  ALLEGRO_MONITOR_INFO   info;
  
  if(f == NULL)
    OPEN_ERROR(ALLEGRO5_CONFIGURATION_FILE, "ConfigurationFile.h");
  
  while( !feof(f) )
  {
    c = fgetc(f);
    if(c == '[')
    {
      i = 0;
      do value[i++] = fgetc(f); while(value[i-1] != ']');
      value[i-1] = '\0';
      
      if( StringCompareNoCase(value, "screen") )
      {
        for(i2 = 0;i2 < 2;i2++)
        {
          do c = fgetc(f); while(c == ' ' || c == '\n');
          i = 0;
          value[i++] = c;
          
          do value[i++] = fgetc(f); while(value[i-1] != '=');
          value[i-1] = '\0';
          
          /*Valor*/
          i = 0;
          do value2[i++] = fgetc(f); while(value2[i-1] != '\n');
          value2[i-1] = '\0';
          
          if( StringCompareNoCase(value, "screen_w") )
            SCREEN_W = atoi(value2);
          else if( StringCompareNoCase(value, "screen_h") )
            SCREEN_H = atoi(value2);
        }
      }
      
      else if( StringCompareNoCase(value, "fullscreen") )
      {
        al_get_monitor_info(0, &info);
        SCREEN_W = info.x2 - info.x1; /* Assume this is 1366 */
        SCREEN_W = info.y2 - info.y1; /* Assume this is 768 */
      }
      
      /*Timer*/
      else if( StringCompareNoCase(value, "timer") )
      {
        do c = fgetc(f); while(c == ' ' || c == '\n');
        i = 0;
        value[i++] = c;
          
        do value[i++] = fgetc(f); while(value[i-1] != '=');
        value[i-1] = '\0';
          
        /*Valor*/
        i = 0;
        do value2[i++] = fgetc(f); while(value2[i-1] != '\n');
        value2[i-1] = '\0';
          
        if( StringCompareNoCase(value, "fps") )
          FPS = atoi(value2);
        else
          UNKNOWN_SCRIPT(value);
      }
      
      /*Sound*/
      else if( StringCompareNoCase(value, "sound") )
      {
        do c = fgetc(f); while(c == ' ' || c == '\n');
        i = 0;
        value[i++] = c;
        
        do value[i++] = fgetc(f); while(value[i-1] != '\n');
        value[i-1]  = '\0';
        MAX_SAMPLES = atoi(value);
      }
    }
  }
}
