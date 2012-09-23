#include <stdlib.h>
#include <stdio.h>

class FileController
{
    private:
        FILE           *file_handle;
        char           *filepath,
                       *mode;

    public:
        FileController();

        int open(char *filepath, char *mode);

        char* read();

        char *getFilepath();

        char *getMode();
};

