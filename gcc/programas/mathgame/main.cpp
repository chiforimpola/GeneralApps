
#include <stdlib.h>
#include <stdio.h>
#include "MathGame.h"

int main (int argc, char *argv[])
{
    int       a = atoi(argv[1]),
              b = atoi (argv[2]);
    MathGame math;
    math.init(a, b);
    math.print();
}
