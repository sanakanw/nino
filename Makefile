.PHONY=default

CC=g++
CFLAGS=-O3 -g
SRC=$(wildcard src/*/*.cpp)
OBJ=$(patsubst src/%.cpp, build/bin/%.o, $(SRC))
HEADERS=$(wildcard src/*/*.h)
ASSETS=$(patsubst assets/%, build/assets/%, $(wildcard assets/*.*))
LIBS=-lSDL2 -lSDL2_image -lGL -lGLEW -lm

default: build/nino $(ASSETS)

build/nino: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

build/bin/%.o: src/%.cpp $(HEADERS) | build/bin/common build/bin/renderer build/bin/system build/bin/game
	$(CC) $(CFLAGS) -c -o $@ $<

build/assets/%: assets/% | build/assets
	cp $< $@

build/assets: | build/bin
	-mkdir $@

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
