#include "include/player.h"
#include "include/mathkae.h"
#include "include/game.h"
#include <stdlib.h>
#include <stdio.h>

Player* init_player(Vector2 pos, int size, float speed, Texture2D tex, int layer)
{
    Player* player = calloc(1, sizeof(Player));

    player->pos = pos;
    player->size = size;
    player->speed = speed;
    player->tex = tex;

    player->facing = 1;

    player->picked_weapon = NULL;

    player->layer = layer;

    return player;
}
void update_player(Player* player)
{
    Vector2 input = normalize_vec((Vector2){.x = IsKeyDown(KEY_D) - IsKeyDown(KEY_A), .y = IsKeyDown(KEY_S) - IsKeyDown(KEY_W)});

    if(input.x != 0)
    {
        player->facing = input.x > 0 ? 1 : -1;   
    }

    player->pos.x += input.x * player->speed * GetFrameTime();
    player->pos.y += input.y * player->speed * GetFrameTime();

    // BOUNDARIES
    if(player->pos.x < 0)
    {
        player->pos.x = 0;
    }
    else if(player->pos.x > WORLD_BOUNDARY_X - 64)
    {
        player->pos.x = WORLD_BOUNDARY_X - 64;
    }
    if(player->pos.y < 0)
    {
        player->pos.y = 0;
    }
    else if(player->pos.y > WORLD_BOUNDARY_Y - 64)
    {
        player->pos.y = WORLD_BOUNDARY_Y - 64;
    }

    if(player->picked_weapon != NULL)
    {
        player->picked_weapon->pos = player->pos;
        player->picked_weapon->layer = player->layer + 1;

        update_weapon(player->picked_weapon);

        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);

        float angle = atan2(mousePos.y - player->pos.y - player->size * SIZE_MULTIPLIER / 2, mousePos.x - player->pos.x - player->size * SIZE_MULTIPLIER / 2 );
        angle = angle * (180.0f / PI);

        player->picked_weapon->pos.x = player->pos.x + cos(angle * DEG2RAD) * player->picked_weapon->size * SIZE_MULTIPLIER;
        player->picked_weapon->pos.y = player->pos.y + sin(angle * DEG2RAD) * player->picked_weapon->size * SIZE_MULTIPLIER;

        player->picked_weapon->rotation = angle;

        // if(player->picked_weapon->can_attack == true)
        // printf("can attack: %d\n", player->picked_weapon->can_attack);
        // else
        // printf("elapsed time: %0.03f\n", player->picked_weapon->elapsed_attack_time);

        // facing
        player->facing = fabs(player->picked_weapon->rotation) < 90 ? 1 : -1;
    }

}
void draw_player(Player* player)
{
    // DrawTexture(player->tex, player->pos.x, player->pos.y, WHITE);
    // DrawTextureEx(player->tex, player->pos, 0, SIZE_MULTIPLIER, WHITE);
    if(DEBUG) DrawRectangleRec(get_player_rec(player), RED);
    
    DrawTexturePro(player->tex, (Rectangle){ .height = 16, .width = player->facing * 16, .x = 0, .y = 0},
    (Rectangle){ .height = 16 * SIZE_MULTIPLIER, .width = 16 * SIZE_MULTIPLIER, .x = player->pos.x, .y = player->pos.y },
    (Vector2){ 0 }, 0, WHITE);
}

Rectangle get_player_rec(Player* player)
{
    return (Rectangle){ .height = player->size * SIZE_MULTIPLIER, .width = player->size * SIZE_MULTIPLIER, .x = player->pos.x, .y = player->pos.y };
}