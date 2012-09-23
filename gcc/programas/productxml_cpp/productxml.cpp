
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

char *getFileContents (char *path) {
    FILE                *f;
    unsigned long int    size;
    char                *buffer;
    f = fopen (path, "r");
    if (f == NULL) return (NULL);
    fseek(f, 0, SEEK_END);
    size = ftell (f);
    rewind (f);

    buffer = (char *) malloc (size+1);
    fread (buffer, 1, size, f);

    return (buffer);
}

int show_help() {
}

int main (int argc, char *argv[]) {
    unsigned long int i;
    std::string       contents,
                      specialinfo;
    std::vector<std::string>  tags,
                              auxtags;
    short int         found_product = 0;
    unsigned long int total_products = 0;

    if (argc != 3) show_help();
    else {
        contents = getFileContents (argv[1]);
        for (i = 0;i < contents.size();i++) {
            if (contents[i] == '<') {
                i++;
                std::string tagcontents;
                while (contents[i] != '>') tagcontents += contents[i++];
                if (tagcontents[0] == '?') specialinfo = tagcontents;
                else if (found_product == 0) {
                    if (tagcontents == argv[2]) {
                        found_product = 1;
                        total_products++;
                    }
                } 
                else if (tagcontents[1] != '/') {
                    if (tagcontents == argv[2]) {
                        total_products++;
                    } else {
                        tags.push_back (tagcontents);
                    }
                } 
                else if (tagcontents[0] == '/') {
                    std::string aux;
                    short int a;
                    for (a=1;a<tagcontents.size();a++) aux += tagcontents[a];
                    std::cout << "tag finalizadora" << std::endl;
                    std::cout << a;
                    exit(1);
                }
            }
        }
    }
}
