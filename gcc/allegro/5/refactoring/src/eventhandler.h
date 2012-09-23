
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#define EVENT_TYPE_DISPLAY 0
#define EVENT_TYPE_MOUSE 1
#define EVENT_TYPE_KEYBOARD 2
#define EVENT_TYPE_TIMER 3

#include <allegro5/timer.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

#include "keyboard_codes.h"

class EventHandler
{
	private:
	    ALLEGRO_EVENT_QUEUE    *event_queue;
            ALLEGRO_EVENT           event;
	public:

	    EventHandler()
	    {
	    	event_queue = al_create_event_queue();

	    	if (!event_queue)
	    	{
	    		fprintf(stderr, "eventHandler: Erro ao criar event_queue");
	    		exit (-1);
	    	}
	    }

	    ALLEGRO_EVENT_QUEUE* getEventQueue();
	    ALLEGRO_EVENT waitForEvent();

	    bool isEmpty();

	    void registerDisplay(ALLEGRO_DISPLAY *display);
	    void registerKeyboard ();
	    void registerMouse();
	    void registerTimer (ALLEGRO_TIMER  *timer);

            int getType ()
            {
                return (event.type);
            }
};

#endif
