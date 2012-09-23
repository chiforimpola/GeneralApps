

#include <stdlib.h>
#include <stdio.h>
#include "TrianguloPascal.h"

int main (int argc, char *argv[])
{
    TrianguloPascal t;
    t.create (atoi(argv[1]));
    t.Show();
}
