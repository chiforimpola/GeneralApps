
#include <stdlib.h>
#include <stdio.h>
#include "confparser.h"

int main (int argc, char *argv[]) {
  unsigned short int             i;
  struct confparserparameters   *a;

  for (i = 2;i < argc;i++) {
    parser (0, argv[1]);
    while ( (a=getNodeValue(0, argv[i])) != NULL ) printf ("%s, %s\n", a->parameter, a->value);
  }
  return (1);
}
