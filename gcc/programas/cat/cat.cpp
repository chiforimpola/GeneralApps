

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

std::vector <std::string> filescontents;

int readFile (char *abspath)
{
    std::fstream fs;
    fs.open (abspath, std::fstream::in);
    if (fs.good())
    {
        short int      buffersize = 1024;
        std::string    strbuffer;
        char           buffer[buffersize];
        
        while (fs)
        {
            //fs.read (buffer, sizeof (buffer)-1);
            fs.getline (buffer, sizeof (buffer));
            std::cout << buffer << std::endl;
            strbuffer += buffer;
        }
        filescontents.push_back (strbuffer);
        fs.close();
    }
    else
    {
       std::cout << "Error while openning file [" << abspath << "]" << std::endl;
    }
}

int showFilesContents()
{
    std::vector <std::string>::iterator i;
    std::cout << filescontents[0];exit(-1);
    for (i = filescontents.begin();i != filescontents.end();i++)
    {
        std::cout << (*i);
    }
}

int main (int argc, char *argv[])
{
    unsigned short int i;
    for (i = 1;i < argc;i++)
    {
        readFile (argv[i]);
    }

    showFilesContents();
}

