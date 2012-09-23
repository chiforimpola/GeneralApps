
#ifndef _MOUSE_HANLDLER_H
#define _MOUSE_HANDLER_H

#define MOUSE_LBUTTON 1

class MouseHandler
{
    private:
        ALLEGRO_MOUSE_STATE    state;

    public:
        MouseHandler ();
        int getX();
        int getY();
        bool isButtonDown(int btn);
};

#endif


