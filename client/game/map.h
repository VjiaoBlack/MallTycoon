#ifndef MAP_H
#define MAP_H


#include <iostream>
#include <vector>
#include "../graphics/graphics.h"

class Tile {
    int x, y;
public:
    Tile(int a, int b){
        x = a;
        y = b;
    }
    void operator=(const Tile src) {
        x = src.x;
        y = src.y;
    }
    int get_x(){return x;}
    int get_y(){return y;}
};

class Map {
    std::vector<Tile*>* tiles;
    std::vector<int>* types;
    int rows, cols;
public:
    Map(std::ifstream &data);
    int get_rows(){return rows;}
    int get_cols(){return cols;}
    int get_node_type(int r, int c);
    int set_node_type(int r, int c, int type);
    void delete_tiles();
};

void delete_map(Map* m);
// void populate_map(map*, char const*);

void draw_map(Map*);


long long iso_to_screen(int, int, int, int);


#endif
