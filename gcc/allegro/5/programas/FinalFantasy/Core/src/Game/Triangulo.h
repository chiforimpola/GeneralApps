
#define TRIANGULO_H
#define TRIANGULO_CONFIGURATION_FILE     "triangulo.dat"

struct TrianguloValues
{
  unsigned long int    i, j,
                       n, MAX;
  
  TrianguloValues     *prox, *ante;
  
  void New();
  unsigned long int  getValue(int i, int j);
  TrianguloValues*   getAdress(int i, int j);
};TrianguloValues      *t_ini = NULL,
                       *t_fim = NULL,
                       *t_aux = NULL;
 


/****************************************************
               TrianguloValues
****************************************************/
void TrianguloValues :: New()
{
  if(t_ini == NULL)
  {
    t_ini = (TrianguloValues *)malloc(sizeof(struct TrianguloValues));
    t_ini->prox = t_ini->ante = NULL;
    t_aux = t_fim = t_ini;
  }
  else
  {
    t_aux = t_fim;
    t_fim = (TrianguloValues *)malloc(sizeof(struct TrianguloValues));
    t_aux->prox = t_fim;
    t_fim->ante = t_aux;
    t_fim->prox = NULL;
    t_aux = t_fim;
  }
}


/****************************************************
               TrianguloValues
****************************************************/
unsigned long int TrianguloValues :: getValue(int i, int j)
{
  TrianguloValues  *aux;
  
  for(aux = t_ini;aux != NULL;aux = aux->prox)
    if(aux->i == i && aux->j == j)
      return (aux->n);
  return (0);
}


/****************************************************
               TrianguloValues
****************************************************/
TrianguloValues* TrianguloValues :: getAdress(int i, int j)
{
  TrianguloValues  *aux;
  
  for(aux = t_ini;aux != NULL;aux = aux->prox)
    if(aux->i == i && aux->j == j)
      return (aux);
  return (NULL);
}



struct Triangulo : TrianguloValues
{
  unsigned long int    n;
  long int             spr_x, spr_y;
  ALLEGRO_BITMAP      *buffer;
  
  void init();
  void start();
  void print(ALLEGRO_FONT *font);
  void readConfigurationFile();
  
  void teste()
  {
    char aux[100];
    for(int i = 0;i < n;i++)
      for(j = 0;j < n;j++)
      {
        strcpy(aux, toString(i));
        strcat(aux, ", ");
        strcat(aux, toString(j));
        strcat(aux, " = ");
        strcat(aux, toString(TrianguloValues :: getValue(i, j)));
        Al_MessageBox(display, aux);
      }
  }
};Triangulo triangulo;


void Triangulo :: start()
{
  TrianguloValues  *aux = t_ini;
  volatile int      row = 0,
                    col = 0,
                    val = 0;
  
  for(int i = 0;i < MAX;i++)
  {
    if(row > 0 && col > 0)
    {
      aux = TrianguloValues :: getAdress(row, col);
      if(aux != NULL)
        aux->n = 
          TrianguloValues :: getValue(row - 1, col) + 
          TrianguloValues :: getValue(row - 1, col - 1);
    }
    val++;
    if(val == n)
    {
      row++;
      col = 0;
      val = 0;
    }
    else
      col++;
  }
}


void Triangulo :: print(ALLEGRO_FONT *font)
{
  volatile long int i,
                    row = 0,
                    col = 0,
                    val = 0,
                    x = 0,
                    y = 0;
  char              aux[1000];
  
  al_set_target_bitmap(buffer);
  al_clear_to_color(BLACK);
  
  for(i = 0;i < MAX;i++)
  {
    if(col == 0)
      strcpy(aux, toString(TrianguloValues :: getValue(row, col)));
    else if( TrianguloValues :: getValue(row, col) > 0 )
    {
      strcat(aux, " ");
      strcat(aux, toString(TrianguloValues :: getValue(row, col)));
    }
    
    val++;
    if(val == n)
    {
      val = 0;
      col = 0;
      row++;
      x = (SCREEN_W / 2) - ( (row*32) / 2 ) + 32;
      y += 20;
      al_draw_text(font, WHITE, x, y, 0, aux);
    }
    else
      col++;
  }
  al_set_target_bitmap(al_get_backbuffer(display));
  al_draw_bitmap(buffer, spr_x, spr_y, 0);
  /*
  al_draw_scaled_bitmap(
    buffer, 
    x, 0, 
    SCREEN_W - x, y, 
    SCREEN_W/2, 0,
    SCREEN_W, SCREEN_H, 0);
  */
}

void Triangulo :: init()
{
  unsigned long int i,
                    row = 0,
                    col = 0,
                    val = 0;
  
  readConfigurationFile();
  
  MAX = (n*n);
  spr_x = spr_y = 0;
  buffer = al_create_bitmap(SCREEN_W, SCREEN_H);
  al_convert_mask_to_alpha(buffer, INVISIBLE);
  
  for(i = 1;i <= MAX;i++)
  {
    TrianguloValues :: New();
    t_fim->i = row;
    t_fim->j = col;
    
    if(col == 0)
      t_fim->n = 1;
    else if(col == row)
      t_fim->n = 1;
    else
      t_fim->n = 0;
    
    val++;
    if(val < n)
      col++;
    else
    {
      val = 0;
      col = 0;
      row++;
    }
  }
  start();
}


void Triangulo :: readConfigurationFile()
{
  char       value[10];
  short int  i;
  FILE      *arq = fopen(TRIANGULO_CONFIGURATION_FILE, "r");
  
  n = 0;
  while( !feof(arq) && n == 0 )
  {
    while( fgetc(arq) != '<' && !feof(arq) ) { }
    do value[i++] = fgetc(arq); while(value[i-1] != '>' && !feof(arq) );
    value[i-1] = '\0';
    n = atoi(value);
    break;
  }
}
