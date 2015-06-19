#include "graphics.h"

ViewMode view_mode(400,100);

SDL_Window* window;
SDL_Texture* texture;
SDL_Renderer* renderer;

std::map<std::string, SDL_Texture*> textures;

int ViewMode::set_x_offset(int x) {
    int old = x_offset;
    x_offset = x;
    return old;
}
int ViewMode::set_y_offset(int y) {
    int old = y_offset;
    y_offset = y;
    return old;
}
float ViewMode::set_x_offvel(float x) {
    float old = x_offvel;
    x_offvel = x;
    return old;
}
float ViewMode::set_y_offvel(float y) {
    float old = y_offvel;
    y_offvel = y;
    return old;
}
float ViewMode::set_x_offacc(float x) {
    float old = x_offacc;
    x_offacc = x;
    return old;
}
float ViewMode::set_y_offacc(float y) {
    float old = y_offacc;
    y_offacc = y;
    return old;
}
void ViewMode::update() {
    y_offacc = 0;
    x_offacc = 0;

    float vel = 0.4;

    if (keys_held[SDLK_UP]) {
        y_offacc = -vel;
    } else if (y_offvel < 0) {
        y_offacc = vel;
    }

    if (keys_held[SDLK_DOWN]) {
        y_offacc = vel;
    } else if (y_offvel > 0) {
        y_offacc = -vel;
    }


    if (!keys_held[SDLK_UP] && !keys_held[SDLK_DOWN]) {
        if (y_offvel < vel && y_offvel > -vel) {
            y_offvel = 0;
            y_offacc = 0;
        }
    }

    if (keys_held[SDLK_LEFT]) {
        x_offacc = -vel;
    } else if (x_offvel < 0) {
        x_offacc = vel;
    }

    if (keys_held[SDLK_RIGHT]) {
        x_offacc = vel;
    } else if (x_offvel > 0) {
        x_offacc = -vel;
    }


    if (!keys_held[SDLK_RIGHT] && !keys_held[SDLK_LEFT]) {
        if (x_offvel < vel && x_offvel > -vel) {
            x_offvel = 0;
            x_offacc = 0;
        }
    }

    if (y_offvel > 3) {
        y_offacc = 0;
        y_offvel = 3;
    }

    if (y_offvel < -3) {
        y_offacc = 0;
        y_offvel = -3;

    }

    if (x_offvel > 3) {
        x_offacc = 0;
        x_offvel = 3;

    }

    if (x_offvel < -3) {
        x_offacc = 0;
        x_offvel = -3;

    }

    x_offvel = x_offvel + x_offacc;
    y_offvel = y_offvel + y_offacc;

    x_offset = x_offset + x_offvel;
    y_offset = y_offset + y_offvel;
}


void draw_line(int x1, int y1, int x2, int y2, int r, int g, int b, int a) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}



void clear_textures() {
    textures.clear();
}

void load_textures() {
    SDL_Texture* text;

    std::string files[] = {"grass","road","water"};
    int num_files = 3;

    for (int i = 0; i < num_files; i++) {
        /* Open the image files */
        std::string location = "res/" + files[i] + ".png";
        text = IMG_LoadTexture(renderer, location.c_str());
        if (!text) {
            fprintf(stderr, "Couldn't load %s: %s\n", location.c_str(), SDL_GetError());
        }
        SDL_SetRenderTarget(renderer, text);
        textures.insert ( std::pair<std::string,SDL_Texture*>(files[i],text) );
    }
}

void init_graphics() {
    load_textures();
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

    init_graphics();
}
