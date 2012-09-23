#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>

#define CLEAR_COLOR al_map_rgb (0, 0, 0)


int      screenw = 800,
         screenh = 600;
float    refreshratevalue = 0.3f;

ALLEGRO_DISPLAY       *screen;
ALLEGRO_COLOR          clearcolor;
ALLEGRO_TIMER         *refreshrate;
ALLEGRO_EVENT_QUEUE   *eventpool;

void core_init ();

int main (int argc, char *argv[]) {
    int                    finished = 0,
                           redraw = 1;
    core_init ();

    al_register_event_source (eventpool, al_get_display_event_source(screen));
    al_register_event_source (eventpool, al_get_keyboard_event_source());
    al_register_event_source (eventpool, al_get_mouse_event_source());
    al_register_event_source (eventpool, al_get_timer_event_source(refreshrate));

    al_start_timer (refreshrate);
    while (finished == 0) {
        ALLEGRO_EVENT  event;
        al_wait_for_event (eventpool, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == 59) finished = 1;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (event.timer.source == refreshrate) redraw = 1;
                break;
        }

        if (redraw && al_is_event_queue_empty (eventpool)) {
            redraw = 0;
        }
    }

    return (1);
}

void core_init () {
    int fatalerror = 0;
    if (!al_init()) {
        fprintf (stderr, "Erro ao iniciar Allegro\n");
        return (-1);
    }

    if (!al_init_image_addon()) {
        fprintf (stderr, "Erro ao iniciar addon de imagem\n");
        fatalerror = 1;
    }

    if (!al_install_keyboard()) {
        fprintf (stderr, "Erro ao instalar teclado\n");
        fatalerror = 1;
    }

    if (!al_install_mouse()) {
        fprintf (stderr, "Erro ao instalar mouse\n");
        fatalerror = 1;
    }

    if ( (screen=al_create_display(screenw, screenh)) == NULL ) {
        fprintf (stderr, "Erro ao criar display\n");
        fatalerror = 1;
    }
    al_set_target_bitmap (al_get_backbuffer (screen));

    if ( (refreshrate=al_create_timer (refreshratevalue)) == NULL ) {
        fprintf (stderr, "Erro ao criar timer\n");
        fatalerror = 1;
    }

    if ( (eventpool=al_create_event_queue()) == NULL ) {
        fprintf (stderr, "Erro ao criar event queue\n");
        fatalerror = 1;
    }

    if (fatalerror) {
        exit (-1);
    }

}
