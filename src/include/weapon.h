#ifndef WEAPON_H
#define WEAPON_H
#include "raylib.h"

typedef struct Weapon
{
    char* name;
    Vector2 pos;
    bool picked_up;
    int size;
    Texture2D tex;

    enum
    {
        CLOSE_RANGE,
        LONG_RANGE
    } type;

    float damage;
    float range;
    float attack_time;
    float elapsed_attack_time;
    bool can_attack;

    int layer;

    float rotation;
} Weapon;

Weapon* init_weapon(char* name, Vector2 pos, int type, int size, float damage, float range, Texture2D tex, int player_layer, float attack_time);
void update_weapon(Weapon* weapon);
void draw_weapon(Weapon* weapon);

Rectangle get_weapon_rec(Weapon* weapon);

#endif