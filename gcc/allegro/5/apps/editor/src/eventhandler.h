
#ifndef EVENT_HANDLER
#define EVENT_HANDLER

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

ALLEGRO_EVENT_QUEUE* EventHandler::getEventQueue()
{
	return (event_queue);
}

ALLEGRO_EVENT EventHandler::waitForEvent()
{
	al_wait_for_event(event_queue, &event);

	return (event);
}

bool EventHandler::isEmpty()
{
	return (al_is_event_queue_empty(event_queue));
}

void EventHandler::registerDisplay(ALLEGRO_DISPLAY *display)
{
	al_register_event_source(
			event_queue, al_get_display_event_source(display));
}

void EventHandler::registerKeyboard()
{
	al_register_event_source(
			event_queue, al_get_keyboard_event_source());
}

void EventHandler::registerMouse()
{
	al_register_event_source(
			event_queue, al_get_mouse_event_source());
}

void EventHandler::registerTimer (ALLEGRO_TIMER  *timer)
{
	al_register_event_source(
			event_queue, al_get_timer_event_source(timer));
}

#endif
