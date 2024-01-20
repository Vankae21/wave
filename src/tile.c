#include "include/tile.h"
#include "include/game.h"
#include <stdlib.h>

Tile* init_tile(Vector2 pos, int type)
{
    Tile* tile = (Tile*)calloc(1, sizeof(Tile));

    tile->pos = pos;
    tile->type = type;

    return tile;
}
void draw_tile(Tile* tile, Texture2D tex)
{
    DrawTexturePro(tex, (Rectangle){ .height = 16, .width = 16, .x = 16 * tile->type, .y = 0 },
    (Rectangle){ .x = tile->pos.x, .y = tile->pos.y, .width = 16 * SIZE_MULTIPLIER, .height = 16 * SIZE_MULTIPLIER },
    (Vector2){0}, 0, WHITE);
}