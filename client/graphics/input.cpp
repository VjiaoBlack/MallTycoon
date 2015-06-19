// Victor 2/20

#include "input.h"

std::map<int,int> keys_held;
int sdl_quit;
int mouse_x, mouse_y;
int mouse_xvel, mouse_yvel;


void init_input() {
    keys_held.clear();
    sdl_quit = 0;
}


// does not handle: caps, control, fnction, option/alt, commmand, shift/tab??
void get_input() {
    SDL_Event event;

    // while clears the input queue. Thus, no lag!
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            sdl_quit = 1;
        }
        if (event.type == SDL_KEYUP) {  // any key is released
            keys_held[event.key.keysym.sym] = 0;

        }
        if (event.type == SDL_KEYDOWN) {  // any key is pressed
            keys_held[event.key.keysym.sym] = 1;


        }
        if (event.type == SDL_MOUSEMOTION) {
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;

            mouse_xvel = event.motion.xrel;
            mouse_yvel = event.motion.yrel;
        }
    }
}
