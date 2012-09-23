#include <stdlib.h>
#include <stdio.h>

int getfilesize(char *path) {
    int    size = -1;
    FILE  *f = fopen (path, "r");

    if (f != NULL) {
        fseek (f, 0, SEEK_END);
        size = ftell (f);
        fclose (f);
    }
    return (size);
}

char *getfilecontents(char *path) {
    char               *buffer;
    int                 size;
    FILE               *f = fopen (path, "r");

    size = getfilesize(path);
    if (size == -1) return (NULL);

    buffer = (char*) malloc (size+1);

    fread (buffer, 1, size, f);

    fclose (f);

    return (buffer);
}

