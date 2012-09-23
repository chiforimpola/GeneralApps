
#ifndef EVENT_HANDLER_CPP
#define EVENT_HANDLER_CPP

#include "eventhandler.h"

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
