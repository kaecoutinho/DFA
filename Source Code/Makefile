# Makefile
# Kaê Angeli Coutinho
# MIT license

# Constants

OUTPUT = Runtime
OBJECTS = DFA.o DFABuilder.o State.o StateBuilder.o Transition.o $(OUTPUT).o
CC = g++
CFLAGS = -w
LDFLAGS = 

# Default target

all: libraries
	$(CC) $(CFLAGS) $(OBJECTS) -o $(OUTPUT) $(LDFLAGS)

# Libraries target

libraries: $(OUTPUT).o DFA.o DFABuilder.o State.o StateBuilder.o Transition.o

# File targets

# Object files

$(OUTPUT).o: $(OUTPUT).cpp
	$(CC) $(CFLAGS) -c $<

DFA.o: DFA.cpp DFA.h
	$(CC) $(CFLAGS) -c $<

DFABuilder.o: DFABuilder.cpp DFABuilder.h
	$(CC) $(CFLAGS) -c $<

State.o: State.cpp State.h
	$(CC) $(CFLAGS) -c $<

StateBuilder.o: StateBuilder.cpp StateBuilder.h
	$(CC) $(CFLAGS) -c $<

Transition.o: Transition.cpp Transition.h
	$(CC) $(CFLAGS) -c $<

# Clean targets

clean:
	rm -rf $(OBJECTS)

cleanall:
	rm -rf $(OBJECTS) $(OUTPUT)
