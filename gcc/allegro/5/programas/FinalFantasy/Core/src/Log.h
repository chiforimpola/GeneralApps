
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/*
  ********************************************
  *                                          *
  *   Pretendo fazer para cada programa      *
  *   uma caixa de log onde manterei os      *
  *   as informacoes dos fluxos de dados     *
  *   do programa                            *
  *                                          *
  ********************************************
*/

struct Log
{
  char             *title;
  bool              OPEN;
  FILE             *arq;
  
  void append(char *msg);
  void close();
};


#endif
