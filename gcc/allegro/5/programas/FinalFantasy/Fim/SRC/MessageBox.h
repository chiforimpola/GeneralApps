
#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <allegro5/allegro_native_dialog.h>

inline void Al_MessageBox(ALLEGRO_DISPLAY *display, char *msg)
{
  al_show_native_message_box(display, "Mensagem", "heading", msg, NULL, ALLEGRO_MESSAGEBOX_WARN);
}

#endif
