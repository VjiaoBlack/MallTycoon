#include "tycoon.h"

Map* a;


void draw() {
    SDL_RenderClear(renderer);

    a->draw();



    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void update() {



    view_mode.update();
}

int main(int argv, char* argc[]) {

    init_sdl();
    mspf = 1000 / FPS;


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
        update();


        SDL_Delay(mspf);
    }

    clear_textures();
    delete_map(a);

    SDL_DestroyWindow(window);
    SDL_Quit();
}

