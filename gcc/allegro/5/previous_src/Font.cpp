

#ifndef FONT_CPP
#define FONT_CPP

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


int Font :: getW(char *msg){ return (al_get_text_width(font, msg)); }

int Font :: getH(){ return (al_get_font_line_height(font)); }

void Font :: print(int x, int y, char *msg)
{
  al_draw_text(
        font, 
        color, 
        x, y,
        modo, msg);
}

  bool Font :: open(char *path2, int size, int modo2, ALLEGRO_COLOR color2)
  {
    if( !USING_FONT )
    {
      al_init_font_addon();
      if( !al_init_ttf_addon() )
      {
        Al_MessageBox(NULL, "Erro ao adicionar addon de fonte");
        exit(-1);
      }
      USING_FONT = true;
    }
    modo   = modo2;
    
    path   = (char *)malloc(strlen(path2));
    strcpy(path, path2);
    
    color  = color2;
    
    font   = al_load_ttf_font(path, size, 0);
    if(font == NULL)
      return (false);
    return (true);
  }

ALLEGRO_FONT*  Font :: getFont(){ return (font); }

#endif
