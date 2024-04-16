CC = g++

CFLAGS =-c -Wall 
LDFLAGS = 

CCFLAGS = 
INCLUDE =
LIBS = -lpthread
LDFLAGS =

SOURCES=test.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./test.exe $(ARGS)

clean:
	rm -f test.exe  
	rm -f *.o  
