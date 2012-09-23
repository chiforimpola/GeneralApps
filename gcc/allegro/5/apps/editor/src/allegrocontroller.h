
#ifndef ALLEGRO_CONTROLLER
#define ALLEGRO_CONTROLLER

#include <allegro5/allegro.h>
#include <iostream>
#include "displayhandler.h"
#include "eventhandler.h"
#include "timerhandler.h"
#include "mousehandler.h"

class AllegroController
{
        private:

	public:

	    AllegroController()
	    {
		   if(!al_init())
		   {
		      fprintf(stderr, "failed to initialize allegro!\n");
		      exit (-1);
		   }

	    }

	    bool installKeyboard ();
	    bool installMouse ();
};

bool AllegroController::installKeyboard ()
{
	return (al_install_keyboard());
}

bool AllegroController::installMouse()
{
	return (al_install_mouse());
}


#endif
