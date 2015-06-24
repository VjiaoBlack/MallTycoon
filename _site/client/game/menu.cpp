#include "../game/menu.h"


void Menu::draw() {
    switch(expanded) {
        case 0:
            // not expanded.
            break;
        case 1:
            // expanded.
            draw_rect(0,100,100,540,50,60,75,1); // menu body

            draw_rect(25,150,75,200,0,0,0,1); // menu buttons (1)

            if (highlight   !=  -1)
                draw_rect(25, 150 + 50 * highlight, 75, 200 + 50 * highlight, 100,100,100,1);


            break;
    }
}

void Menu::update(ViewMode& vm) {
    // checks for mouse position, what its hovering over, etc.
    if (!old_m && keys_held[ (int) 'm'] ) {
        expanded = !expanded;
    }

    if (keys_held[ (int) 'm' ]) {
        old_m = 1;
    } else {
        old_m = 0;
    }



    if (expanded) {
        // we should check to see what's pressed and what's not pressed.


        if (mouse_x > 25 && mouse_x < 75 &&
            mouse_y > 150 && mouse_y < 200) {
            // the cursor is over the road button.

            highlight = 0;

            if (keys_held[ (int) ' ']) {
                // placeholder for mouse_down
                std::cerr << "click\n";
                vm.set_construction_mode(0);
            }


        } else {
            highlight = -1;
        }
    }



}
