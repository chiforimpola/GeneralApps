
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

MouseHandler :: MouseHandler()
{
    if (!al_is_mouse_installed()) al_install_mouse();
}

int MouseHandler :: getX()
{
    al_get_mouse_state (&state);
    return (state.x);
}

int MouseHandler :: getY()
{
    al_get_mouse_state (&state);
    return (state.y);
}

bool MouseHandler :: isButtonDown(int btn)
{
    al_get_mouse_state (&state);
    return (al_mouse_button_down (&state, btn));
}

#endif


