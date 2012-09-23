CC = g++
CFLAGS = -c -Wall
LDFLAGS = 
LIBRARIES = /usr/lib/liballegro.so /usr/lib/liballegro_image.so /usr/lib/liballegro_acodec.so /usr/lib/liballegro_audio.so /usr/lib/liballegro_ttf.so /usr/lib/liballegro_font.so
SOURCE_EXT = cpp
SOURCES = $(wildcard *.$(SOURCE_EXT))
OBJECTS =$(SOURCES:.$(SOURCE_EXT)=.o)
OBJECTS_DIRECTORY = './objects/'
EXTERN_OBJECTS_DIRECTORY = './objs'
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(EXTERN_OBJECTS_DIRECTORY)/*.o -o $@ $(LIBRARIES)
	mv *.o $(OBJECTS_DIRECTORY)

.(SOURCE_EXT).o:
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS_DIRECTORY)*.o $(EXECUTABLE)

install:
	mv $(EXECUTABLE) /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/$(EXECUTABLE)
