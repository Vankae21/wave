#include "include/game.h"
#include "include/player.h"
#include "include/tile.h"
#include "include/mathkae.h"
#include "include/weapon.h"
#include <time.h>
#include <stdio.h>

#define COLS 32
#define ROWS 24

#define WEAPON_LEN 2

#define MAX_LAYER 3

// YOXLAMA
float yoxlama_rot = 0;
// YOXLAMA

bool DEBUG = true;

const int WORLD_BOUNDARY_X = COLS * 64, WORLD_BOUNDARY_Y = ROWS * 64;

Player* player = NULL;

// CAM --
Camera2D* camera;

//CAM --

// WEAPON ---

Weapon** weapons = NULL;

// WEAPON ---

Texture2D ground_textures;

Tile* tiles[COLS][ROWS];

char weapon_alert_text[128];

void init()
{
    srand(time(0));

    // PLAYER ---------
    player = init_player((Vector2){.x = 800, .y = 600}, 16, 300, LoadTexture("assets/man.png"), 1);

    // PLAYER ---------

    // CAM -----------
    camera = calloc(1, sizeof(Camera2D));
    camera->target = player->pos;
    camera->offset = (Vector2){ WIDTH / 2.0f - 32, HEIGHT / 2.0f - 32 };
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;

    // GROUND ---------
    ground_textures = LoadTexture("assets/tiles.png");

    // WEAPON ---
    Weapon* sword = init_weapon("Wooden Sword", (Vector2){player->pos.x + 100, player->pos.y}, CLOSE_RANGE, 16, 20.5f, 35.2f, LoadTexture("assets/wooden_sword.png"), player->layer, 2.0f);
    Weapon* wand = init_weapon("Magic Wand", (Vector2){player->pos.x + 200, player->pos.y}, LONG_RANGE, 16, 100.5f, 100.2f, LoadTexture("assets/wand.png"), player->layer, 5.0f);

    weapons = calloc(WEAPON_LEN, sizeof(Weapon*));

    for(int i = 0; i < WEAPON_LEN; i++)
    {
        switch (i)
        {
        case 0:
            weapons[i] = sword;
            break;
        
        case 1:
            weapons[i] = wand;
            break;

        default:
            break;
        }
    }

    int x = 0;
    for(int i = 0; i < COLS; i++)
    {
        int y = 0;
        for(int j = 0; j < ROWS; j++)
        {
            int random_i;
            int temp_random = rand() % 100;
            if(temp_random > 95)
            {
                random_i = 2;
            }
            else if(temp_random > 40)
            {
                random_i = 1;
            }
            else
            {
                random_i = 0;
            }

            tiles[i][j] = init_tile((Vector2){ x, y }, random_i);
            y += 16 * SIZE_MULTIPLIER;
        }
        x += 16 * SIZE_MULTIPLIER;
    }

    // GROUND ---------


}
void update()
{
    if(IsKeyPressed(KEY_ENTER)) DEBUG = DEBUG == true ? false : true;
    // PLAYER ---------
    update_player(player);

    camera->target = lerp(camera->target, player->pos, 2.5f);

    camera->zoom += (IsKeyDown(KEY_M) - IsKeyDown(KEY_N)) * 0.01f;
    if(IsKeyPressed(KEY_F)) camera->zoom = 1.0f;

    // WEAPON
    
    bool collided_weapon = false;
    for(int i = 0; i < WEAPON_LEN; i++)
    {
        if(player->picked_weapon != NULL)
        {
            collided_weapon = true;

            sprintf(weapon_alert_text, "Press Q to drop the %s", player->picked_weapon->name);
            if(IsKeyPressed(KEY_Q))
            {
                player->picked_weapon->layer = player->layer - 1;
                player->picked_weapon->rotation = 0;
                player->picked_weapon->picked_up = false;
                player->picked_weapon = NULL;
            }
            break;
        }
        else if(CheckCollisionRecs(get_player_rec(player), get_weapon_rec(weapons[i])))
        {
            collided_weapon = true;

            sprintf(weapon_alert_text, "Press E to pick the %s up", weapons[i]->name);
            if(IsKeyPressed(KEY_E))
            {
                player->picked_weapon = weapons[i];
                player->picked_weapon->picked_up = true;
            }

            break;
        }
    }
    if(collided_weapon == false)
    {
        sprintf(weapon_alert_text, " ");
    }

}
void late_update()
{

    BeginMode2D(*camera);
    // GROUND ---------
    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            draw_tile(tiles[i][j], ground_textures);
        }
    }

    if(DEBUG)
    DrawText("Debug mode is on. Press Enter to disable\nMovement: WASD, Pick up: E, Drop: Q, Zoom in/out: M/N\nReset Zoom View: F", 200, 300, 64, BLACK);

    // WEAPON ---------

    // PLAYER ---------
    
    draw_player(player);

    for(int i = 0; i < MAX_LAYER; i++)
    {
        if(player->layer == i)
        {
            draw_player(player);
        }
        for(int j = 0; j < WEAPON_LEN; j++)
        {
            if(weapons[j]->layer == i) draw_weapon(weapons[j]);
        }
    }

    yoxlama_rot += (IsMouseButtonDown(0) - IsMouseButtonDown(1)) * 1.0f;

    Vector2 origin = { .x = 32, .y = 32 };

    DrawRectanglePro((Rectangle){ .x = 400, .y = 400, .height = 16 * SIZE_MULTIPLIER, .width = 16 * SIZE_MULTIPLIER }, (Vector2){ 0 }, 0, BLUE);

    DrawTexturePro(player->tex, (Rectangle){ .height = 16, .width = 16, .x = 0, .y = 0 },
    (Rectangle){ .x = 400, .y = 400, .height = 16 * SIZE_MULTIPLIER, .width = 16 * SIZE_MULTIPLIER },
    origin, yoxlama_rot, WHITE);

    // PLAYER ---------
    EndMode2D();

    // UI

    DrawText(weapon_alert_text, 100, 100, 32, BLACK);


}
void end()
{
    // PLAYER ---------
    free(player);

    // PLAYER ---------
    
    // GROUND ---------
    for(int i = 0; i < COLS; i++)
    {
        for(int j = 0; j < ROWS; j++)
        {
            free(tiles[i][j]);
        }
    }

    // GROUND ---------

    // CAM -------

    for(int i = 0; i < WEAPON_LEN; i++)
    {
        free(weapons[i]);
    }
    free(weapons);

    free(camera);
}