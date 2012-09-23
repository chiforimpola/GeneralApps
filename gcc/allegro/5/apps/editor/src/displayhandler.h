
#ifndef DISPLAY_HANDLER
#define DISPLAY_HANDLER

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


ALLEGRO_DISPLAY* DisplayHandler::get ()
{
	if (display == NULL)
		display = al_create_display(w, h);

	return (display);
}

void DisplayHandler::show(int mode)
{
    al_clear_to_color (getClearColor());

    printAndPullMessages();

    switch (mode)
    {
        case DISPLAY_HANDLER_ONLY_POOL:
        {
            BITMAP_POOL *aux = pullBitmapPool();
            while (aux != NULL)
            {
                aux->image.print();
                aux = pullBitmapPool();
            }
            break;
        }

        case DISPLAY_HANDLER_ONLY_PERSISTENT:
        {
            _PERSISTENT_IMAGES   *aux2;
            for (aux2 = _persistent_images_first;aux2 != NULL;aux2 = aux2->next)
            {
                if (aux2->to_print)
                {
                    aux2->to_print = 0;
                    aux2->image.print();
                }
            }
            break;
        }
    }
//BITMAP_POOL *aux = pullBitmapPool();

    al_flip_display();
}

void DisplayHandler :: clean()
{
    al_clear_to_color (getClearColor());
}

ALLEGRO_COLOR DisplayHandler :: getClearColor()
{
    return (clear_color);
}

void DisplayHandler :: setClearColor(ALLEGRO_COLOR color)
{
    clear_color = color;
}

void DisplayHandler :: setClearColor (int r, int g, int b)
{
    clear_color = al_map_rgb (r, g, b);
}

void DisplayHandler::destroy ()
{
	al_destroy_display(display);

	display = NULL;
}

/*
 * Implementacao dos metodos da fila de
 * bitmaps que deverao ser impressos na tela
 */

DisplayHandler::BITMAP_POOL* DisplayHandler::addBitmapToPool(Image image)
{
	BITMAP_POOL   *aux = NULL,
	              *first = bitmap_pool_first,
	              *last = bitmap_pool_last;

	aux = (BITMAP_POOL*)malloc(sizeof(BITMAP_POOL));
	aux->image = image;

	if (first == NULL)
	{
		bitmap_pool_first = aux;
		bitmap_pool_first->next = NULL;
		bitmap_pool_first->last = NULL;

		bitmap_pool_last = bitmap_pool_first;
	}

	else
	{
		aux->last = last;
		last->next = aux;
		aux->next = NULL;

		bitmap_pool_last = aux;
	}
}

DisplayHandler::BITMAP_POOL* DisplayHandler::pullBitmapPool()
{
    if (bitmap_pool_first != NULL)
    {
        BITMAP_POOL *aux = (BITMAP_POOL *) malloc (sizeof (BITMAP_POOL));
        aux->image = bitmap_pool_first->image;
        if (bitmap_pool_first->next != NULL)
        {
            bitmap_pool_first = bitmap_pool_first->next;
            delete (bitmap_pool_first->last);
            bitmap_pool_first->last = NULL;
        }
        else
        {
            delete (bitmap_pool_first);
            bitmap_pool_first = bitmap_pool_last = NULL;
        }

        return (aux);
    }

    return (NULL);

	if (bitmap_pool_first != NULL)
	{
	    BITMAP_POOL *aux = (BITMAP_POOL*)malloc(sizeof(BITMAP_POOL));

	    aux->image = bitmap_pool_first->image;

	    if (bitmap_pool_first->next != NULL)
	    {
		    bitmap_pool_first = bitmap_pool_first->next;
	    	delete (bitmap_pool_first->last);
	        bitmap_pool_first->last = NULL;
	    }

	    else
	    {
	    	bitmap_pool_first = NULL;
	    	delete (bitmap_pool_first);
	    }

	    return (aux);
	}
}

void DisplayHandler::setPosition (int x, int y)
{
	al_set_window_position (display, x, y);
}

/*
 * Adiciona as imagens persistentes na estrutura
 */
void DisplayHandler :: addPersistentImage(Image img)
{
    _PERSISTENT_IMAGES   *first = _persistent_images_first,
                         *last = _persistent_images_last,
                         *aux;
    int                  free_space = 0;

    if (free_space == 0)
    {
        aux = (_PERSISTENT_IMAGES *) malloc (sizeof (_PERSISTENT_IMAGES));
        aux->image = img;
        aux->to_print = 0;
        aux->next = NULL;

        if (first == NULL)
        {
             first = aux;
            first->previous = NULL;
            last = first;
            first->index = 0;
            _persistent_images_first = first;
        }
        else
        {
            aux->previous = last;
            last->next = aux;
            last = aux;
            last->index = last->previous->index + 1;
            _persistent_images_last = last;
        }
    }
}


int DisplayHandler :: removePersistentImage (int index)
{
    _PERSISTENT_IMAGES   *aux;

    for (aux = _persistent_images_first;aux != NULL;aux = aux->next)
    {
        if (aux->index == index)
        {
            aux->index = _PERSISTENT_IMAGE_REMOVED_BLOCK;
            return (1);
        }
    }

    return (0);
}

int DisplayHandler :: persistentImageToPrint (int index)
{
    int                    found = 0;
    _PERSISTENT_IMAGES    *aux = _persistent_images_first;

    for (;aux != NULL;aux = aux->next)
    {
        if (aux->index == index)
        {
            aux->to_print = 1;
            found = 1;
            break;
        }
    }

    if (found) al_flip_display();

    return (found);
}

void DisplayHandler :: printf (Font font, char *message, int x, int y)
{
    _MESSAGES_BUFFER    *aux = (_MESSAGES_BUFFER *) malloc (sizeof (_MESSAGES_BUFFER));

    aux->message = (char *) malloc (strlen(message)+1);
    strcpy (aux->message, message);
    aux->x = x;
    aux->y = y;
    aux->font = font;
    aux->next = NULL;

    if (_messages_buffer_first == NULL)
    {
        _messages_buffer_first = _messages_buffer_last = aux;
        _messages_buffer_first->previous = NULL;
    }
    else
    {
        _messages_buffer_last->next = aux;
        aux->previous = _messages_buffer_last;
        _messages_buffer_last = aux;
    }
}

void DisplayHandler :: printAndPullMessages()
{
    _MESSAGES_BUFFER   *aux;

    for (aux = _messages_buffer_first;aux != NULL;aux = aux->next)
    {
       if (aux->previous != NULL)
       {
           free (aux->previous);
           aux->previous = NULL;
       }
       aux->font.printf (aux->message, aux->x, aux->y);
    }

    free (_messages_buffer_last);
    _messages_buffer_first = _messages_buffer_last = NULL;
}

#endif
