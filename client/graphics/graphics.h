#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "SDL.h"
#include "input.h"
#include <math.h>
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
    float x_offvel, y_offvel;
    float x_offacc, y_offacc;
public:
    ViewMode(){x_offset = y_offset = x_offvel = y_offvel = x_offacc = y_offacc = 0;}
    ViewMode(int x, int y){x_offset = x; y_offset = y; y_offvel = x_offvel = x_offacc = y_offacc = 0;}
    int get_x_offset(){return x_offset;}
    int get_y_offset(){return y_offset;}
    int set_x_offset(int x);
    int set_y_offset(int y);

    float get_x_offvel(){return x_offvel;}
    float get_y_offvel(){return y_offvel;}
    float set_x_offvel(float x);
    float set_y_offvel(float y);

    float get_x_offacc(){return x_offacc;}
    float get_y_offacc(){return y_offacc;}
    float set_x_offacc(float x);
    float set_y_offacc(float y);

    void update();
};

extern ViewMode view_mode;

extern SDL_Window* window;
extern SDL_Texture* texture;
extern SDL_Renderer* renderer;

extern SDL_Texture *grass;

extern std::map<std::string, SDL_Texture*> textures;



// TODO: this graphics world view thing.

#endif
