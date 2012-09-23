
#ifndef TIMER_HANDLER
#define TIMER_HANDLER

#include <allegro5/timer.h>

class TimerHandler
{
	private:

	    ALLEGRO_TIMER   *timer;

	public:

	    TimerHandler (double time)
	    {
	    	timer = al_create_timer(time);
	    }

	    ALLEGRO_TIMER   *get();

	    void start();
};

ALLEGRO_TIMER* TimerHandler::get()
{
	return (timer);
}

void TimerHandler::start()
{
	al_start_timer(timer);
}

#endif
