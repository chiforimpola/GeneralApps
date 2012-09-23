
#ifndef _MOUSE_HANLDLER_CPP
#define _MOUSE_HANDLER_CPP

#include "mousehandler.h"

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


