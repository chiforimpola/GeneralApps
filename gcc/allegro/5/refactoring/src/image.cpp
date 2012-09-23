
#ifndef IMAGE_CPP
#define IMAGE_CPP

#include "image.h"

ALLEGRO_BITMAP* Image::open(char *path, ALLEGRO_COLOR ignoreColor)
{
	image = al_load_bitmap(path);
	al_convert_mask_to_alpha(image, ignoreColor);
        if (image == NULL)
        {
            std::cout << "Erro ao abrir imagem: " << path;
            exit (-1);
        }

	return (image);
}

ALLEGRO_BITMAP* Image :: open (char *path, float r, float g, float b)
{
    image = al_load_bitmap (path);
    if (image == NULL)
    {
        std::cout << "Erro ao abrir imagem: " << path;
        exit (-1);
    }
    al_convert_mask_to_alpha (image, al_map_rgb (r, g, b));

    return (image);
}

ALLEGRO_BITMAP* Image::get()
{
	return (image);
}

void Image::print()
{
	ALLEGRO_DISPLAY *display = al_get_current_display();

	switch (mode)
	{
            case IMAGE_MODE_DEFAULT:
	        al_draw_bitmap(image, x, y, flag);
	        break;

	    case IMAGE_MODE_FULLSCREEN:
	    	al_draw_scaled_bitmap(
   			   image,
	    	   0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image),
	    	   0, 0, al_get_display_width(display), al_get_display_height(display), flag);
		    break;

	    case IMAGE_MODE_REGION:
	    	//al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
	    	al_draw_bitmap_region(
	    	   image,
	    	   region_x, region_y, region_w, region_h,
	    	   x, y, flag);
		    break;
	}
}

#endif
