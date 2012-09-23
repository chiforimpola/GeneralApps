
#include <stdlib.h>
#include <stdio.h>
#include "src/allegrocontroller.cpp"
#include "src/displayhandler.cpp"
#include "src/image.cpp"
#include "src/eventhandler.cpp"
#include "src/mousehandler.cpp"
#include "src/font.cpp"
#include "src/timerhandler.cpp"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define BG_COLOR al_map_rgb (0, 0, 128)
#define FN_COLOR al_map_rgb (173, 225, 47)

int main(int argc, char *argv[])
{
    AllegroController  alcontroller;
    DisplayHandler     screen (atoi(argv[1]), atoi(argv[2]));
    Font               main_font ("fonts/default.ttf", 20);
    MouseHandler       mouse;
    EventHandler       events;
    TimerHandler       update_timer (0.2);
    bool               finished = false;
    volatile int       redraw = 0,
                       lnx = 0,
                       lny = 0,
                       i_buffer;
    char               buffer[1000];

    alcontroller.installMouse ();
    alcontroller.installKeyboard ();

    events.registerDisplay (screen.get());
    events.registerKeyboard ();
    events.registerMouse ();
    events.registerTimer (update_timer.get());

    screen.setClearColor (BG_COLOR);
    main_font.setColor (FN_COLOR);

    update_timer.start();
    i_buffer = 0;
    while (!finished)
    {
        ALLEGRO_EVENT ev = events.waitForEvent ();

        switch (events.getType())
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                finished = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                finished = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		if (mouse.isButtonDown(MOUSE_LBUTTON))
                {
                    finished = true;
                    break;
                }
                break;

            case ALLEGRO_EVENT_TIMER:
               if (ev.timer.source == update_timer.get())
                   redraw = 1;

        }

        if (redraw && al_is_event_queue_empty(events.getEventQueue()))
        {
           redraw = 0;
           screen.printf (main_font, "Teste de Mensagem!", 0, 0);
           screen.show(DISPLAY_HANDLER_ONLY_PERSISTENT);
        }
   }
}
