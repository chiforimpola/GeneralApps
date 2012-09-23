
#ifndef TIMER_HANDLER_H
#define TIMER_HANDLER_H

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


#endif
