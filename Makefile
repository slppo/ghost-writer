CXX=g++
CXXFLAGS=-g -Wall -pedantic -std=c++11 -Ofast

LD=g++
LDFLAGS=
LDLIBS=pthread

OBJECTS=main.o Trie.o
PROGRAM=main

.PHONY: all rebuild clean

all: $(PROGRAM)

rebuild: clean all

clean:
	rm $(OBJECTS) $(PROGRAM) || true

$(PROGRAM): $(OBJECTS)
	$(LD) $(LDFLAGS) $(LDLIBS:%=-l%) -o $(PROGRAM) $(OBJECTS)
