
	#include <stdlib.h>
	#include <stdio.h>
	#include <iostream>
	#include <string>
	#include "src/allegrocontroller.h"

	#define BG_COLOR al_map_rgb (0, 0, 128)
	#define FN_COLOR al_map_rgb (173, 225, 47)
	#define SCREEN_WIDTH 640
	#define SCREEN_HEIGTH 480
	
	struct _SCREEN_MESSAGES
	{
		char                      *message;
		struct _SCREEN_MESSAGES   *next, *previous;
	};struct _SCREEN_MESSAGES     *_screen_messages_first = NULL,
	                              *_screen_messages_last = NULL;
	
	void _screen_messages_clear (void)
	{
		struct _SCREEN_MESSAGES *aux;
		
		if (_screen_messages_first != NULL)
		{
			for (aux = _screen_messages_first->next;aux != NULL;aux = aux->next)
			{
				free (aux->previous);
			}
			free (_screen_messages_last);
	    }
		_screen_messages_first = _screen_messages_last = NULL;
	}
	
	void _screen_messages_add (const char *message)
	{
		struct _SCREEN_MESSAGES   *aux = (struct _SCREEN_MESSAGES *) malloc (sizeof (struct _SCREEN_MESSAGES));
		
		aux->message = (char *) malloc (strlen (message)+1);
		strcpy (aux->message, message);
		aux->next = NULL;
		
		if (_screen_messages_first == NULL)
		{
			_screen_messages_first = aux;
			_screen_messages_first->previous = NULL;
			_screen_messages_last = _screen_messages_first;
		}
		
		else
		{
			_screen_messages_last->next = aux;
			aux->previous = _screen_messages_last;
			_screen_messages_last = aux;
		}
	}
	
	int main(int argc, char *argv[])
	{
	    AllegroController  alcontroller;
	    DisplayHandler     screen (SCREEN_WIDTH, SCREEN_HEIGTH);
	    Font               main_font ("fonts/default.ttf", 20);
	    MouseHandler       mouse;
	    EventHandler       events;
	    TimerHandler       update_timer (0.2);
	    bool               finished = false;
	    volatile int       redraw = 0,
			       lnx = 0,
			       lny = 0,
			       i_buffer;
	    short int          execute_command = 0;
	    unsigned short int col = 0,
	                       row = 0;
	    char               buffer[1000];
	    std::string        command = "",
			       command_preffix = ">>> ",
			       message_buffer = "";

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
				{
					std::string keypressed = al_keycode_to_name (ev.keyboard.keycode);
					
					if (strcmp(keypressed.c_str(), "Left") == 0)
					{
					}
					
					else if (strcmp (keypressed.c_str(), "Right") == 0 )
					{
					}
					
					else if (strcmp (keypressed.c_str(), "Up") == 0 )
					{
					}
					
					else if (strcmp (keypressed.c_str(), "Down") == 0 )
					{
					}
					
					else if (strcmp (keypressed.c_str(), "Escape") == 0 )
					{
						finished = true;
					}
					
					else
					{
						message_buffer = "";
						std::cout<<keypressed.c_str()<<std::endl;
						if (strcmp (keypressed.c_str(), "space") == 0)
						{
							command += " ";
						}
						else if (strcmp (keypressed.c_str(), "equal") == 0)
						{
							command += "=";
						}
						else if (strcmp (keypressed.c_str(), "minus") == 0)
						{
							command += "-";
						}
						else if (strcmp (keypressed.c_str(), "ISO_Level3_Shift") == 0)
						{
							command += "/";
						}
						else if (strcmp (keypressed.c_str(), "period") == 0)
						{
							command += ".";
						}
						else if (strcmp (keypressed.c_str(), "BackSpace") == 0)
						{
							if (command != "")
							{
								char aux[strlen(command.c_str())];
								int i;
								for (i = 0;i < strlen(command.c_str())-1;i++)
								{
									aux[i] = command[i];
								}
								aux[i] = '\0';
								command = aux;
							}
						}
					
					else if (strcmp (keypressed.c_str(), "Return") == 0)
					{
                        execute_command = 1;
                        row += al_get_font_line_height (main_font.getFont());
                        _screen_messages_add (command.c_str());
                    }
                    else
                    {
						command += keypressed;
					}
					message_buffer += command;
				}
                break;
            }
            
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
           if ( !((command != "reset" || command != "clear") && execute_command == 1))
           {
			   struct _SCREEN_MESSAGES  *aux;
			   unsigned short int        y = 0;
			   for (aux = _screen_messages_first;aux != NULL;aux = aux->next)
			   {
				   screen.printf (main_font, aux->message, col, y);
				   y += al_get_font_line_height (main_font.getFont());
			   }
	       }

           if (execute_command == 0)
           {
               unsigned short int message_buffer_len = strlen (message_buffer.c_str())+1;
               char aux[message_buffer_len+strlen(command_preffix.c_str())+1];
               strcpy (aux, command_preffix.c_str());
               strcat (aux, message_buffer.c_str());
               screen.printf (main_font, aux, col, row);
           }
           
           else if (command == "clear" || command == "reset")
           {
			   _screen_messages_clear();
			   row = 0;
			   execute_command = 0;
			   message_buffer = command = "";
		   }
           
           else
           {
               execute_command = 0;
               FILE   *f = popen (command.c_str(), "r");
               char    buffer[1024];
               std::string buffer2 = "";
               message_buffer = command = "";
               if (f != NULL)
               {
			       while (fgets (buffer, sizeof(buffer), f) != NULL)
				   {
					   _screen_messages_add (buffer);
					   row += al_get_font_line_height (main_font.getFont());
					   std::cout << buffer << std::endl;
				   }
		       }
		       else _screen_messages_add ("comando nao encontrado...");
           }

           screen.show(DISPLAY_HANDLER_ONLY_PERSISTENT);
        }
   }
}
