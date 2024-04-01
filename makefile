CC = g++

CFLAGS =-c -Wall 
LDFLAGS = 

CCFLAGS = 
INCLUDE =
LIBS = 
LDFLAGS =

SOURCES=test.cpp shared_stack.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./test.exe $(ARGS)

clean:
	rm -f test.exe  
	rm -f *.o  
