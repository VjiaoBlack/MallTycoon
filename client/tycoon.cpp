#include "tycoon.h"
#include <iostream>

Map* a;


void draw() {
    SDL_RenderClear(renderer);

    draw_line(0, 0, mouse_x, mouse_y, 255, 255, 255, 1);

    draw_map(a);

    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

int main(int argv, char* argc[]) {

    init_sdl();
    mspf = 1000 / FPS;
    xo = 100;
    yo = 100;


    struct timeval start, current;

    gettimeofday(&start, NULL);
    gettimeofday(&current, NULL);

    std::string str = "1111112221121211222111111";
    const char *cstr = str.c_str();

    a = new Map(5,5, cstr);

    while (!keys_held[ (int) 'q']) {

        gettimeofday(&current, NULL);
        get_input();
        draw();


        xo++;
        yo++;
        SDL_Delay(mspf);
    }


    delete_map(a);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

