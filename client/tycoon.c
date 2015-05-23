#include "tycoon.h"


map* a;

void draw() {
    SDL_RenderClear(renderer);
    draw_line(100, 100, mouse_x, mouse_y, 255, 255, 255, 255);
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



    a = new_map(5,5);
    populate_map(a, "1111112221121211222111111"); // maybe this should be const*

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d", a->tiles[i][j]->type);
        }
        printf("\n");
    }


    while (!keys_held['q']) {

        gettimeofday(&current, NULL);
        get_input();
        draw();


        xo++;
        yo++;
        SDL_Delay(mspf);
    }
    free_map(a);




    SDL_DestroyWindow(window);
    SDL_Quit();
}

