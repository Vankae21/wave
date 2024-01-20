#ifndef TILE_H
#define TILE_H
#include "raylib.h"

typedef struct Tile
{
    Vector2 pos;
    
    enum
    {
        SAND_0,
        SAND_1,
        SAND_2
    } type;

} Tile;

Tile* init_tile(Vector2 pos, int type);
void draw_tile(Tile* tile, Texture2D tex);

#endif