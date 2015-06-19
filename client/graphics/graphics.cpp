#include "graphics.h"

ViewMode view_mode;

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
