
#ifndef _FONT_CPP
#define _FONT_CPP

#include "font.h"

void Font :: init ()
{
    al_init_font_addon();
    if (!al_init_ttf_addon())
    {
        std::cout<<"Erro ao iniciar addon TTF!"<<std::endl;
        exit (-1);
    }

    font = NULL;
}

Font :: Font ()
{
    init();
}

Font :: Font (char *path, int size)
{
    init();
    load(path, size);
}

void Font :: load (char *path, int size)
{
    font = al_load_ttf_font (path, size, 0);
}

void Font :: setColor(ALLEGRO_COLOR color2)
{
    color = color2;
}

ALLEGRO_COLOR Font :: getColor ()
{
    return (color);
}

ALLEGRO_FONT* Font :: getFont()
{
    return (font);
}

void Font :: printf (char *message, int x, int y)
{
    if (font != NULL)
        al_draw_text (font, getColor(), x, y, 0, message);
}

#endif


