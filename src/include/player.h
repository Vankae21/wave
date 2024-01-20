#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "weapon.h"

typedef struct Player
{
    Vector2 pos;
    int size;
    float speed;
    int facing;
    Texture2D tex;

    Weapon* picked_weapon;

    int layer;
} Player;

Player* init_player(Vector2 pos, int size, float speed, Texture2D tex, int layer);
void update_player(Player* player);
void draw_player(Player* player);

Rectangle get_player_rec(Player* player);


#endif