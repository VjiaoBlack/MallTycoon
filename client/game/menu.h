#ifndef MENU_H
#define MENU_H

#include "../graphics/input.h"
#include "../graphics/graphics.h"

#include <iostream>

class Menu {
    int expanded;
    int old_m; // for toggling menu with keypress 'm'

    int highlight;
public:
    Menu(){expanded = 0;old_m = 0;highlight = -1;}
    void expand(){expanded = 1;}
    void retract(){expanded = 0;}
    void draw();
    void update(ViewMode& vm); // checks for cursor positions, etc.
};


#endif
