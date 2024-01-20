#include "include/weapon.h"
#include "include/game.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Weapon* init_weapon(char* name, Vector2 pos, int type, int size, float damage, float range, Texture2D tex, int player_layer, float attack_time)
{
    Weapon* weapon = calloc(1, sizeof(Weapon));

    weapon->picked_up = false;

    weapon->name = name;
    weapon->pos = pos;
    weapon->type = type;
    weapon->size = size;
    weapon->damage = damage;
    weapon->range = range;
    weapon->tex = tex;

    weapon->layer = player_layer - 1;

    weapon->rotation = 0;

    weapon->attack_time = attack_time;
    weapon->elapsed_attack_time = 0;
    weapon->can_attack = true;

    return weapon;
}
void update_weapon(Weapon* weapon)
{
    if(!weapon->can_attack)
    {
        if(weapon->elapsed_attack_time >= weapon->attack_time)
        {
            weapon->can_attack = true;
            weapon->elapsed_attack_time = 0;
        }
        else
        {
            weapon->elapsed_attack_time += GetFrameTime();
        }
    }
    else
    {
        // attack
        if(IsMouseButtonPressed(0) || IsKeyPressed(KEY_SPACE))
        {
            printf("attacked\n");
            weapon->can_attack = false;
        }
    }
}
void draw_weapon(Weapon* weapon)
{
    if(DEBUG)
    {
        if(!weapon->picked_up)
        {
            DrawRectangleRec(get_weapon_rec(weapon), BLUE);
        }
        else
        {
            Color color = weapon->can_attack ? BLUE : RED;
            // if(weapon->type == CLOSE_RANGE)
                DrawCircle(weapon->pos.x + weapon->size * SIZE_MULTIPLIER / 2, weapon->pos.y + weapon->size * SIZE_MULTIPLIER / 2, weapon->range, color);
        }
    }

    DrawTexturePro(weapon->tex, (Rectangle){ .height = fabs(weapon->rotation) < 90 ? weapon->size : -weapon->size , .width = weapon->size, .x = 0, .y = 0},
    (Rectangle){ .x = weapon->pos.x + weapon->size * SIZE_MULTIPLIER / 2, .y = weapon->pos.y + weapon->size * SIZE_MULTIPLIER / 2,
    .height = weapon->size * SIZE_MULTIPLIER, .width = weapon->size * SIZE_MULTIPLIER },
    (Vector2){ .x = 32, .y = 32 }, weapon->rotation, WHITE);
}

Rectangle get_weapon_rec(Weapon* weapon)
{
    return (Rectangle){ .height = weapon->size * SIZE_MULTIPLIER, .width = weapon->size * SIZE_MULTIPLIER, .x = weapon->pos.x, .y = weapon->pos.y };
}