
#ifndef DISPLAY_HANDLER_H
#define DISPLAY_HANDLER_H

#include "image.h"
#include "font.h"

#define DISPLAY_HANDLER_ONLY_POOL  0
#define DISPLAY_HANDLER_ONLY_PERSISTENT 1
#define _PERSISTENT_IMAGE_REMOVED_BLOCK -1

class DisplayHandler
{
	private:

	    ALLEGRO_DISPLAY  *display;
            ALLEGRO_COLOR     clear_color;
	    int               w, h;

            /*
             * Buffer de imagens.
             * Modo de uso:
             *    -A cada iteracao, imagens podem ser adicionadas nesse buffer para posterior amostra no fim do laco
             *
             *    -addBitmapToPool(Image):
             *      -> Aloca memoria para armazenar a instancia Image
             *    -show()
             *      -> Apresentara todas as imagens armazenadas no Pool e esvaziara o pool
             */
	    struct BITMAP_POOL
	    {
	    	Image            image;
	    	BITMAP_POOL     *next, *last;
	    };BITMAP_POOL   *bitmap_pool_first, *bitmap_pool_last, bitmap_pool;

            /*
             * Imagens muito utilizandas deveriam ficar armazenadas dentro desse
             * buffer.
             *    -addPersistentImage (Image):
             *      -> Adiciona a instancia Image dentro da Pool de imagens persistentes
             *    -showPersistentImages (int):
             *      -> Apresenta a imagem com indice igual ao parametro
             */
            struct _PERSISTENT_IMAGES
            {
                Image                image;
                unsigned long int    index;
                unsigned short int   to_print;
                _PERSISTENT_IMAGES   *next, *previous;
            };_PERSISTENT_IMAGES  *_persistent_images_first,
                                  *_persistent_images_last;

            /*
             * Ira armazenar todas as mensagens que forem adicionadas na tela para posterios mostragem
             */
            struct _MESSAGES_BUFFER
            {
                int              x, y;
                char            *message;
                Font             font;

                _MESSAGES_BUFFER *next, *previous;
            }; _MESSAGES_BUFFER    *_messages_buffer_first,
                                   *_messages_buffer_last;

	    BITMAP_POOL* pullBitmapPool();

            void printAndPullMessages();
	public:

	    DisplayHandler(int w2, int h2)
	    {
	    	w = w2;
	    	h = h2;

                clear_color = al_map_rgb (0, 0, 0);

	    	display = al_create_display (w, h);
	    	al_set_target_bitmap(al_get_backbuffer(display));

	    	bitmap_pool_first = bitmap_pool_last = NULL;
                _persistent_images_first = _persistent_images_last = NULL;
                _messages_buffer_first = _messages_buffer_last = NULL;
	    }

	    ALLEGRO_DISPLAY* get();

	    BITMAP_POOL* addBitmapToPool(Image);

            void addPersistentImage (Image);
            int  removePersistentImage (int);
            int  persistentImageToPrint (int);

	    void show(int);
            void clean();
	    void destroy();
	    void setPosition(int x, int y);

            void setClearColor(ALLEGRO_COLOR color);
            void setClearColor (int, int, int);

            void printf (Font, char *, int, int);

            ALLEGRO_COLOR getClearColor();
};


#endif
