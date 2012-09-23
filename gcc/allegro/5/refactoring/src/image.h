
#ifndef IMAGE_H
#define IMAGE_H

#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

#define IMAGE_MODE_DEFAULT     0
#define IMAGE_MODE_FULLSCREEN  1
#define IMAGE_MODE_REGION      2

class Image
{
	private:

	    ALLEGRO_BITMAP   *image;
	    long int          x, y,
	                      region_x, region_y,
	                      region_w, region_h;

	    int               flag,
	                      mode;

	public:

	    Image()
	    {
	    	al_init_image_addon();

	    	image = NULL;
	    	x = y = flag = 0;
	    	region_x = region_y = region_w = region_h = 0;

	    	mode = IMAGE_MODE_DEFAULT;
	    }

	    ALLEGRO_BITMAP* open(char *path, ALLEGRO_COLOR ignoreColor);
            ALLEGRO_BITMAP* open(char *path, float r, float g, float b);

	    ALLEGRO_BITMAP* get();

	    void setX(int x2)
	    {
	    	x = x2;
	    }

	    int getX(){ return (x); }

	    void setY(int y2)
	    {
	    	y = y2;
	    }

	    int getY(){ return (y); }

	    void setFlag(int flag2)
	    {
	    	flag = flag2;
	    }

	    int getFlag(){ return (flag); }

	    void setMode(int mode2)
	    {
	    	mode = mode2;
	    }

	    int getMode(){ return (mode); }

	    int getW()
	    {
	    	return (al_get_bitmap_width(image));
	    }

	    int getH()
	    {
	    	return (al_get_bitmap_height(image));
	    }

	    void setRegion(int x, int y, int w, int h)
	    {
	    	region_x = x;
	    	region_y = y;
	    	region_w = w;
	    	region_h = h;
                mode = IMAGE_MODE_REGION;
	    }

	    void print();
};


#endif
