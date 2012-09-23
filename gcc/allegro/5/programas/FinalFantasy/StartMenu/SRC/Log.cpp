
#ifndef LOG_CPP
#define LOG_CPP

#define LOG_PATH    "log.txt"

#ifndef ALLEGRO5_INIT_H
  extern bool LOG_FIRST_TIME_OPEN;
#endif



void Log :: append(char *msg)
{
  if(LOG_FIRST_TIME_OPEN)
  {
    arq = fopen(LOG_PATH, "w");
    LOG_FIRST_TIME_OPEN = false;
  }
  else
    arq = fopen(LOG_PATH, "a+");
  fprintf(arq, msg);
  fprintf(arq, "\n");
  fclose(arq);
}


void Log :: close(){ fclose(arq); }

#endif
