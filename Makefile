.PHONY=default

CC=g++
CFLAGS=-O3 -g
SRC=$(wildcard src/*/*.cpp)
OBJ=$(patsubst src/%.cpp, build/bin/%.o, $(SRC))
HEADERS=$(wildcard src/*/*.h)
LIBS=-lSDL2 -lSDL2_image -lGL -lGLEW -lm

build/nino: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

build/bin/%.o: src/%.cpp $(HEADERS) | build/bin/common build/bin/renderer build/bin/system build/bin/game
	$(CC) $(CFLAGS) -c -o $@ $<

build/bin/renderer: | build/bin
	-mkdir $@

build/bin/system: | build/bin
	-mkdir $@

build/bin/common: | build/bin
	-mkdir $@

build/bin/game: | build/bin
	-mkdir $@

build/bin: | build
	-mkdir $@

build:
	-mkdir $@
