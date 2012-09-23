CC = gcc
CFLAGS = -c -Wall
LDFLAGS =
SOURCE_EXT = c
SOURCES = $(wildcard *.$(SOURCE_EXT))
OBJECTS =$(SOURCES:.$(SOURCE_EXT)=.o)
OBJECTS_DIRECTORY = './objects/'
EXTERN_OBJECTS_DIRECTORY = './extern-obj/'
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(EXTERN_OBJECTS_DIRECTORY)/*.o -o $@
	mv *.o $(OBJECTS_DIRECTORY)

.(SOURCE_EXT).o:
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS_DIRECTORY)*.o $(EXECUTABLE)

install:
	mv $(EXECUTABLE) /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/$(EXECUTABLE)
