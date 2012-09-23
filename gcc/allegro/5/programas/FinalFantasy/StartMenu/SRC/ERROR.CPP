

#ifndef ERROR_CPP
#define ERROR_CPP


#define OPEN_MESSAGE_ERROR     "Arquivo nao encontrado: "
#define UNKNOWN_SCRIPT_ERROR   "Script nao reconhecido: "



void FATAL_ERROR(char *msg, char *header)
{
  char *aux = (char *)malloc(strlen(msg) + strlen(header) + 5);
  strcpy(aux, msg);
  strcat(aux, " ");
  strcat(aux, "[");
  strcat(aux, header);
  strcat(aux, "]");
  al_show_native_message_box(
    NULL, 
    "Fatal Error", "ERROR", 
    aux, 
    NULL,
    ALLEGRO_MESSAGEBOX_ERROR);
  free(&aux);
  exit(-1);
}

void OPEN_ERROR(char *path, char *header)
{
  char *aux = (char *)malloc(strlen(path) + strlen(header) + strlen(OPEN_MESSAGE_ERROR));
  strcpy(aux, OPEN_MESSAGE_ERROR);
  strcat(aux, path);
  strcat(aux, " ");
  strcat(aux, "[");
  strcat(aux, header);
  strcat(aux, "]");
  al_show_native_message_box(
    NULL, 
    "Arquivo nao encontrado!", "ERROR", 
    aux, 
    NULL,
    ALLEGRO_MESSAGEBOX_ERROR);
  //free(&aux);
  exit(-1);
}

/*Script nao reconhecido*/
void UNKNOWN_SCRIPT(char *msg)
{
  char *aux = (char *)malloc(StringLengh(UNKNOWN_SCRIPT_ERROR) + StringLengh(msg) + 5);
  
  strcpy(aux, UNKNOWN_SCRIPT_ERROR);
  strcat(aux, "'");
  strcat(aux, msg);
  strcat(aux, "'");
  
  Al_MessageBox(NULL, aux);
  free(aux);
}

#endif
