#include "graphics.h"

void draw_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}


void init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("My Game Window",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        800, 640,
                        SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Couldn't set window mode %d x %d: %s\n", 800, 640, SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED);
}
