

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


#endif
