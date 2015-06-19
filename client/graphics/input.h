#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include <iostream>
#include "../graphics/graphics.h"

extern int keys_held[323];
extern int sdl_quit;


extern int mouse_x, mouse_y;
extern int mouse_xvel, mouse_yvel;

void init_input();
void get_input();

#endif
