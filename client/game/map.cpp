#include "map.h"


int Tile::set_type(int t) {
    int a = type;
    type = t;
    return a;
}

Map::Map(std::ifstream &data){

    data >> rows;
    data >> cols;

    std::string str;
    const char* cstr;


    int type;

    tiles = new std::vector<Tile*>();

    for (int i = 0; i < rows; i++) {

        data >> str;

        cstr = str.c_str();


        for (int j = 0; j < cols; j++) {

            switch (cstr[j]) {
                case '1':
                    type = 1;
                    break;
                case '2':
                    type = 2;
                    break;
                default:
                    type = 0;
                    break;
            }

            tiles->push_back(new Tile(i, j, type));
        }
    }
}

int Map::get_tile_type(int r, int c) {
    return tiles->at(r + c * cols)->get_type();
}

int Map::set_tile_type(int x, int y, int type) {
    int old_tile_type = tiles->at(x + y * cols)->get_type();
    tiles->at(x + y * cols)->set_type(type);
    return old_tile_type;
}

void Map::delete_tiles() {
    for (std::vector<Tile*>::iterator i = tiles->begin(); i != tiles->end(); ++i) {
        delete *i;
    }
}

void delete_map(Map* m) {
    m->delete_tiles();

    delete m;
}



void draw_map(Map* m) {
    long long coords;
    int x, y;

    int r, g, b, a;

    SDL_Rect dstrect;
    SDL_Rect srcrect;
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 32;
    srcrect.h = 32;


    for (int i = 0; i < m->get_rows(); i++) {
        for (int j = 0; j < m->get_cols(); j++) {




            coords = iso_to_screen(300,300, i, j);

            x = ((int) (coords >> 32)) & -1;
            y = (int) (coords & ( (long long) ((int) -1)));

            dstrect.x = x - 32;
            dstrect.y = y - 16;
            dstrect.w = 64;
            dstrect.h = 64;





            switch (m->get_tile_type(j,i)) {
                case 1:
                    r = 0;
                    g = 0;
                    b = 255;
                    a = 255;
                    SDL_RenderCopy(renderer, textures.at("water"), &srcrect, &dstrect); //srcrect, destrect

                    break;
                case 2:
                    r = 0;
                    g = 255;
                    b = 0;
                    a = 255;
                    SDL_RenderCopy(renderer, textures.at("grass"), NULL, &dstrect); //srcrect, destrect

                    break;
                default:
                    r = 0;
                    g = 0;
                    b = 0;
                    a = 0;
                    break;
            }


            // draw_line(x-10,y,x+10,y, r, g, b, a);
            // draw_line(x,y+5,x,y-5,   r, g, b, a);

        }
    }




}




// holds 2 ints
long long iso_to_screen(int x_off, int y_off, int r, int c) {

    long long x = x_off;
    long long y = y_off;

    x -= r * 32;
    x += c * 32;

    y += r * 16;
    y += c * 16;


    // fits 2 ints into 1 thing yay...
    x = x << 32;
    return x + y;
}


