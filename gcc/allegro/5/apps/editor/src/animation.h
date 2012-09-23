

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Image.h"

class Animation
{
    private:

	    long int             x, y;
	    EventHandler        eventHandler;

	    struct Sprites
	    {
	    	Image            image;
	    	ALLEGRO_TIMER   *changeTimer;
	    	Sprites      *prox, *ante;
	    };Sprites *sprites_first, *sprites_last;

	    Sprites *actualFrame;

    public:

	    Animation(EventHandler eventHandler2)
	    {
	    	sprites_first = sprites_last = NULL;
	    	x = y = 0;

	    	eventHandler = eventHandler2;
	    }

    	void addFrame(Image image, double changeTimer);
    	void addFrame(char *path, ALLEGRO_COLOR ignoredColor, int flag, int mode, double changeTimer);
    	void start();
    	void stop();
    	void changeFrame();
    	void setEventHandler(EventHandler eventHandler);
    	void setX(long int x2){ x = x2; }
    	void setY(long int y2){ y = y2; }

    	bool isPlaying();

    	long int getX(){ return (x); }
    	long int getY(){ return (y); }

    	Image getFrame();
    	Image* getFramePointer();
    	ALLEGRO_TIMER *getTimer();
};


void Animation::addFrame(Image image, double changeTimer)
{
	Sprites    *aux = (Sprites *)malloc(sizeof(Sprites) + sizeof(image));

	aux->image = image;
	aux->changeTimer = al_create_timer (changeTimer);

	eventHandler.registerTimer (aux->changeTimer);

	if (sprites_first == NULL)
	{
		sprites_first = aux;
		sprites_first->ante = sprites_first->prox = NULL;
		sprites_last = sprites_first;
	}

	else
	{
		sprites_last->prox = aux;
		aux->ante = sprites_last;
		sprites_last = aux;
	}
}

void Animation::addFrame(char *path, ALLEGRO_COLOR ignoredColor, int flag, int mode, double changeTimer)
{
	Image   image;

	image.open (path, ignoredColor);
	image.setFlag(flag);
	image.setMode(mode);

	addFrame(image, changeTimer);
}

void Animation::start()
{
	if (sprites_first != NULL)
	{
		actualFrame = sprites_first;
		al_start_timer (actualFrame->changeTimer);
	}
}

void Animation::stop()
{
	if (actualFrame != NULL)
	{
		if(isPlaying())
			al_stop_timer (actualFrame->changeTimer);
		actualFrame = NULL;
	}
}

void Animation::changeFrame()
{
	if (actualFrame != NULL)
	{
		al_stop_timer (actualFrame->changeTimer);

		if (actualFrame->prox != NULL)
			actualFrame = actualFrame->prox;
		else
			actualFrame = sprites_first;
	}

	else
		actualFrame = sprites_first;

	eventHandler.registerTimer(actualFrame->changeTimer);
	al_start_timer (actualFrame->changeTimer);
}

void Animation::setEventHandler(EventHandler eventHandler2)
{
	eventHandler = eventHandler2;
}

bool Animation::isPlaying()
{
	if (actualFrame == NULL)
		return (false);

	return (al_get_timer_started(actualFrame->changeTimer));
}

Image Animation::getFrame()
{
	if (actualFrame != NULL)
		return (actualFrame->image);
}

Image* Animation::getFramePointer()
{
	if(actualFrame != NULL)
		return (&actualFrame->image);
}

ALLEGRO_TIMER* Animation::getTimer()
{
	if (actualFrame != NULL)
		return (actualFrame->changeTimer);
}

#endif
