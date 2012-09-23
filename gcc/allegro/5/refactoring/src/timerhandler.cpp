
#ifndef TIMER_HANDLER_CPP
#define TIMER_HANDLER_CPP

#include "timerhandler.h"

ALLEGRO_TIMER* TimerHandler::get()
{
	return (timer);
}

void TimerHandler::start()
{
	al_start_timer(timer);
}

#endif
