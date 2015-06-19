#include "tycoon.h"

Map* a;


void draw() {
    SDL_RenderClear(renderer);

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

    std::ifstream map_data;
    map_data.open("res/map.txt");



    a = new Map(map_data);

    while (!keys_held[ (int) 'q']) {

        gettimeofday(&current, NULL);
        get_input();
        draw();


        xo++;
        yo++;
        SDL_Delay(mspf);
    }

    clear_textures();
    delete_map(a);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

