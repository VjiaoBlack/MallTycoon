# makefile

COMPILE=gcc -g -Wall -c
LINK=gcc -g -Wall
SDL_FLAGS=-framework SDL2


all: tycoon

tycoon: build/tycoon.o graphics/graphics.o build/wrapper.o build/input.o build/map.o
	$(LINK) build/tycoon.o graphics/graphics.o build/wrapper.o build/input.o build/map.o -o tycoon $(SDL_FLAGS)

build/tycoon.o: tycoon.c tycoon.h
	$(COMPILE) tycoon.c -o build/tycoon.o $(SDL_FLAGS)

build/graphics.o: graphics/graphics.c graphics/graphics.h
	$(COMPILE) graphics/graphics.c -o build/graphics.o $(SDL_FLAGS)

build/map.o: game/map.c game/map.h
	$(COMPILE) game/map.c -o build/map.o

build/wrapper.o: graphics/wrapper.c graphics/wrapper.h
	$(COMPILE) graphics/wrapper.c -o build/wrapper.o $(SDL_FLAGS)

build/input.o: graphics/input.c graphics/input.h
	$(COMPILE) graphics/input.c -o build/input.o $(SDL_FLAGS)

clean:
	rm *.o tycoon
	rm build/*
