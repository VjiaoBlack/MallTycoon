#include "map.h"


tile* new_tile(int x, int y, int type) {
    tile* t = (tile*) malloc(sizeof(tile));
    t->x = x;
    t->y = y;
    t->type = type;

    return t;
}

void free_tile(tile* t) {
    free(t);
}

map* new_map(int r, int c) {
    map* m = malloc(sizeof(map));
    m->rows = r;
    m->cols = c;

    m->tiles = malloc(sizeof(tile*) * r);

    for (int i = 0; i < r; ++i) {
        m->tiles[i] = malloc(sizeof(tile) * c);
        for (int j = 0; j < c; ++j) {
            m->tiles[i][j] = new_tile(i, j, 0);
        }
    }

    return m;
}
void free_map(map* m) {
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            free(m->tiles[i][j]);
        }
        free(m->tiles[i]);
    }
    free(m->tiles);
    free(m);
}


void populate_map(map* m, char* string) { // maybe this should be const*

    for (int r = 0; r < m->rows; r++) {
        for (int c = 0; c < m->cols; c++) {
            // treats 1D char array as 2D
            switch ((string)[r * (m->rows)+ c]) {
                case '1':
                    m->tiles[r][c]->type = 1;
                    break;
                case '2':
                    m->tiles[r][c]->type = 2;
                    break;
                default:
                    m->tiles[r][c]->type = 0;
                    break;
            }
        }
    }

}

void draw_map(map* m) {
    long long coords;
    int x, y;

    int r, g, b, a;


    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {

            coords = iso_to_screen(300,300, i, j);

            x = ((int) (coords >> 32)) & -1;
            y = (int) (coords & ( (long long) ((int) -1)));

            switch (m->tiles[i][j]->type) {
                case 1:
                    r = 0;
                    g = 0;
                    b = 255;
                    a = 255;
                    break;
                case 2:
                    r = 0;
                    g = 255;
                    b = 0;
                    a = 255;
                    break;
                default:
                    r = 0;
                    g = 0;
                    b = 0;
                    a = 0;
                    break;
            }


            draw_line(x-10,y,x+10,y, r, g, b, a);
            draw_line(x,y+5,x,y-5,   r, g, b, a);

        }
    }


}

// holds 2 ints
long long iso_to_screen(int x_off, int y_off, int r, int c) {

    long long x = x_off;
    long long y = y_off;

    x -= r * 16;
    x += c * 16;

    y += r * 8;
    y += c * 8;


    // fits 2 ints into 1 thing yay...
    x = x << 32;
    return x + y;
}


