
#ifndef ALLEGRO_CONTROLLER
#define ALLEGRO_CONTROLLER

#include <allegro5/allegro.h>
#include <iostream>

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


#endif
