#include <stdio.h>
#include <stdlib.h>
#include "../graphics/graphics.h"


typedef struct {
    int x;
    int y;
    int type;

} tile;

typedef struct {
    tile*** tiles;
    int rows;
    int cols;
} map;


tile* new_tile(int, int, int);
void free_tile(tile*);

map* new_map(int, int);
void free_map(map*);
void populate_map(map*, char*); // maybe this should be const*

void draw_map(map*);


long long iso_to_screen(int, int, int, int);
