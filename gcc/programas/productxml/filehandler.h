

#include <iostream>
#include <stdlib.h>

class FileHandler
{
    private:
        FILE          *file;
        char          *abspath,
                      *mode;

    public:

        FileHandler (char *abspath, char *mode);

        void open ();
        char* read();
};

