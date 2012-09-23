#include <iostream>
#include "filecontroller.h"

int main (int argc, char *argv[])
{
    FileController         file;
    char                  *buffer;
    unsigned short int     i = 0;

    for (i = 1;i < argc;i++)
    {
        file.open (argv[i], "r");
        buffer = file.read();
        std::cout << buffer;
    }
}
