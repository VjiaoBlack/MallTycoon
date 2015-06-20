COMPILE		=	g++ -g -Wall -O2 -c
LINK		=	g++ -g -Wall -O2
SDL_FLAGS	= 	`sdl2-config --cflags --libs` -lSDL2_image


# Visual Studio
# Include SDL_image.h and add SDL2_image.lib to your linker dependencies.
#
# GCC or Clang on Linux and MinGW on Windows
# Include SDL2/SDL_image.h and add -lSDL2_image to the SDLLIB variable in your makefile.
#
# Clang on Mac
# Include SDL2_image/SDL_image.h and add -framework SDL2_image to the SDL variable in your makefile.
#
# - http://www.willusher.io/sdl2%20tutorials/2013/08/18/lesson-3-sdl-extension-libraries/


all: tycoon

tycoon: build/tycoon.o build/graphics.o build/wrapper.o build/input.o build/map.o build/menu.o
	$(LINK) build/tycoon.o build/graphics.o build/wrapper.o build/input.o build/map.o build/menu.o $(SDL_FLAGS) -o tycoon

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

build/menu.o: game/menu.cpp game/menu.h
	$(COMPILE) game/menu.cpp $(SDL_FLAGS) -o build/menu.o

clean:
	rm *.o tycoon
	rm build/*
