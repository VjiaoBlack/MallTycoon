#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "SDL.h"
#include <iostream>

void draw_line(int,int,int,int, int,int,int,int);

void init_sdl();

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


// TODO: this graphics world view thing.

#endif
