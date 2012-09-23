
#ifndef MESSAGE_CPP
#define MESSAGE_CPP

#ifndef FONT_H
  #include "Font.h"
#endif

#ifndef STRING_H
  #include "String.h"
#endif


  void Message :: print()
  {
    font.print(x, y, msg);
  }
  
  void Message :: start(long int x2, long int y2, char *msg2, Font font2)
  {
    font = font2;
    msg  = (char *)malloc(StringLengh(msg2) + 2);
    strcpy(msg, msg2);
    
    x = x2;
    y = y2;
  }

#endif
