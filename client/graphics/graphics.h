#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "SDL.h"
// #include "/Library/Frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

void draw_line(int,int,int,int, int,int,int,int);

void init_sdl();

void load_textures();

void clear_textures();

void init_graphics();

class ViewMode {
    int x_offset, y_offset;
public:
    ViewMode(){x_offset = y_offset = 0;}
    ViewMode(int x, int y){x_offset = x; y_offset = y;}
    int get_x_offset(){return x_offset;}
    int get_y_offset(){return y_offset;}
};

extern ViewMode view_mode;

extern SDL_Window* window;
extern SDL_Texture* texture;
extern SDL_Renderer* renderer;

extern SDL_Texture *grass;

extern std::map<std::string, SDL_Texture*> textures;



// TODO: this graphics world view thing.

#endif
