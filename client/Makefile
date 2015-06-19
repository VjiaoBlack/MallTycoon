COMPILE		=	g++ -g -Wall -O2 -c
LINK		=	g++ -g -Wall -O2
SDL_FLAGS	= 	`sdl2-config --cflags --libs`

all: tycoon

tycoon: build/tycoon.o build/graphics.o build/wrapper.o build/input.o build/map.o
	$(LINK) build/tycoon.o build/graphics.o build/wrapper.o build/input.o build/map.o $(SDL_FLAGS) -o tycoon

build/tycoon.o: tycoon.cpp tycoon.h
	$(COMPILE) tycoon.cpp $(SDL_FLAGS) -o build/tycoon.o

build/graphics.o: graphics/graphics.cpp graphics/graphics.h
	$(COMPILE) graphics/graphics.cpp $(SDL_FLAGS) -o build/graphics.o

build/map.o: game/map.cpp game/map.h
	$(COMPILE) game/map.cpp $(SDL_FLAGS) -o build/map.o

build/wrapper.o: graphics/wrapper.cpp graphics/wrapper.h
	$(COMPILE) graphics/wrapper.cpp $(SDL_FLAGS) -o build/wrapper.o

build/input.o: graphics/input.cpp graphics/input.h
	$(COMPILE) graphics/input.cpp $(SDL_FLAGS) -o build/input.o

clean:
	rm *.o tycoon
	rm build/*
