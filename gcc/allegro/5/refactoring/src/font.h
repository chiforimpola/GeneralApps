
#ifndef _FONT_H
#define _FONT_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


class Font
{
    private:
        ALLEGRO_FONT          *font;
        ALLEGRO_COLOR          color;

        void init();
    public:
        Font();
        Font (char*, int);

        void setColor (ALLEGRO_COLOR);
        ALLEGRO_COLOR getColor();

        ALLEGRO_FONT *getFont();

        void load(char*, int size);

        void printf(char*, int, int);
};


#endif


