
#ifndef MESSAGE_H
#define MESSAGE_H

#ifndef FONT_H
 #include "Font.h"
#endif


struct Message
{
  char            *msg;
  Font             font;
  long int         x, y;
  
  void print();
  void start(long int x2, long int y2, char *msg2, Font font2);
};

#endif
