#include "wrapper.h"

Uint32 pixel(int r, int g, int b) {
    return SDL_MapRGB(screen->format, r, g, b);
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y) {
    int bpp = 4;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    return (Uint32) *p;
}

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {
    int bpp = 4;
    // this is INEFFICIENT LOL
    // but it gets rids of bad out-of-bound errors. for now.

    if (x < 0 || y < 0) {
        return;
    }

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    *(Uint32 *)p = pixel;
    return;
}



void close_window() {
    SDL_FreeSurface(screen); // how to check if screen is initialized
    exit(0);
    return;
}

void quit(int code) {
    SDL_Quit();
    exit(1);
    return;
}
