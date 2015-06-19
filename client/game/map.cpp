#include "map.h"


Map::Map(std::ifstream &data){

    data >> rows;
    data >> cols;

    std::string str;
    const char* cstr;


    int type;

    tiles = new std::vector<Tile*>();
    types = new std::vector<int>();


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tiles->push_back(new Tile(i, j));
        }
    }

    for (int i = 0; i <= rows; i++) {
        data >> str;
        cstr = str.c_str();
        for (int j = 0; j <= cols; j++) {

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

            types->push_back(type);
        }
    }
}

int Map::get_node_type(int r, int c) {
    return types->at(c + r * (cols + 1));
}

int Map::set_node_type(int r, int c, int type) {
    int old_tile_type = types->at(c + r * cols);
    types->at(c + r * cols) = type;
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

    int type_nw;
    int type_ne;
    int type_sw;
    int type_se;

    std::string tile_type;

    SDL_Rect dstrect;
    SDL_Rect srcrect;
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 32;
    srcrect.h = 32;


    for (int i = 0; i < m->get_rows(); i++) {
        for (int j = 0; j < m->get_cols(); j++) {


            coords = iso_to_screen(view_mode.get_x_offset(),view_mode.get_y_offset(), i, j);

            x = ((int) (coords >> 32)) & -1;
            y = (int) (coords & ( (long long) ((int) -1)));

            dstrect.x = x - 32;
            dstrect.y = y - 16;
            dstrect.w = 64;
            dstrect.h = 64;

            type_nw = m->get_node_type(i  ,j  );
            type_ne = m->get_node_type(i  ,j+1);
            type_sw = m->get_node_type(i+1,j  );
            type_se = m->get_node_type(i+1,j+1);

            if (type_nw == 2 && type_ne == 2 &&
                type_sw == 2 && type_se == 2) {
                tile_type = "grass";
                srcrect.x = 0;
            } else

            if (type_nw == 1 && type_ne == 2 &&
                type_sw == 2 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 0;
            } else
            if (type_nw == 2 && type_ne == 1 &&
                type_sw == 2 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 32 * 1;
            } else
            if (type_nw == 2 && type_ne == 2 &&
                type_sw == 2 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 2;
            } else
            if (type_nw == 2 && type_ne == 2 &&
                type_sw == 1 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 32 * 3;
            } else

            if (type_nw == 1 && type_ne == 1 &&
                type_sw == 2 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 32 * 4;
            } else
            if (type_nw == 2 && type_ne == 1 &&
                type_sw == 2 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 5;
            } else
            if (type_nw == 2 && type_ne == 2 &&
                type_sw == 1 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 6;
            } else
            if (type_nw == 1 && type_ne == 2 &&
                type_sw == 1 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 32 * 7;
            } else

            if (type_nw == 1 && type_ne == 1 &&
                type_sw == 2 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 8;
            } else
            if (type_nw == 2 && type_ne == 1 &&
                type_sw == 1 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 9;
            } else
            if (type_nw == 1 && type_ne == 2 &&
                type_sw == 1 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 10;
            } else
            if (type_nw == 1 && type_ne == 1 &&
                type_sw == 1 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 32 * 11;
            } else

            if (type_nw == 1 && type_ne == 2 &&
                type_sw == 2 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 12;
            } else
            if (type_nw == 2 && type_ne == 1 &&
                type_sw == 1 && type_se == 2) {
                tile_type = "water";
                srcrect.x = 32 * 13;
            } else

            if (type_nw == 1 && type_ne == 1 &&
                type_sw == 1 && type_se == 1) {
                tile_type = "water";
                srcrect.x = 32 * 14;
            } else {
                std::cerr << type_nw;
                std::cerr << type_ne;
                std::cerr << type_sw;
                std::cerr << type_se;
            }


            SDL_RenderCopy(renderer, textures.at(tile_type), &srcrect, &dstrect); //srcrect, destrect

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


