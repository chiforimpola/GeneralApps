CC = g++
CFLAGS = -c -Wall
LDFLAGS =
SOURCE_EXT = c
SOURCES = $(wildcard *.$(SOURCE_EXT))
OBJECTS =$(SOURCES:.$(SOURCE_EXT)=.o)
OBJECTS_DIRECTORY = './objects/'
EXECUTABLE = hexdump

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	mv *.o $(OBJECTS_DIRECTORY)

.(SOURCE_EXT).o:
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS_DIRECTORY)*.o $(EXECUTABLE)

install:
	mv $(EXECUTABLE) /usr/local/bin

uninstall:
	rm -rf /usr/local/bin/$(EXECUTABLE)
