
#ifndef ALLEGRO_CONTROLLER_CPP
#define ALLEGRO_CONTROLLER_CPP

#include "allegrocontroller.h"

bool AllegroController::installKeyboard ()
{
	return (al_install_keyboard());
}

bool AllegroController::installMouse()
{
	return (al_install_mouse());
}


#endif
