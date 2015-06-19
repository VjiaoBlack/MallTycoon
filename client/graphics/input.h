#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include <iostream>
#include <map>
#include "../graphics/graphics.h"

extern std::map<int,int> keys_held;
extern int sdl_quit;


extern int mouse_x, mouse_y;
extern int mouse_xvel, mouse_yvel;

void init_input();
void get_input();

#endif
