
#include <stdlib.h>
#include <stdio.h>
#include "getfilecontents.h"

int main () {
    printf ("%s", getfilecontents("makefile"));
}
