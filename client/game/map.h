#ifndef MAP_H
#define MAP_H


#include <iostream>
#include <vector>
#include "../graphics/graphics.h"

class Tile {
    int x, y, type;
public:
    Tile(int a, int b, int c){
        x = a;
        y = b;
        type = c;
    }
    void operator=(const Tile src) {
        x = src.x;
        y = src.y;
        type = src.type;
    }
    int get_x(){return x;}
    int get_y(){return y;}
    int get_type(){return type;}
    int set_type(int t);
};

class Map {
    std::vector<Tile*>* tiles;
    int rows, cols;
public:
    Map(int r, int c, const char* str);
    int get_rows(){return rows;}
    int get_cols(){return cols;}
    int get_tile_type(int x, int y);
    int set_tile_type(int x, int y, int type);
    void delete_tiles();
};

void delete_map(Map* m);
// void populate_map(map*, char const*);

void draw_map(Map*);


long long iso_to_screen(int, int, int, int);


#endif
