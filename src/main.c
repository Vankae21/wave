#include "raylib.h"
#include "include/game.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);

    SetTargetFPS(FPS);

    SetExitKey(KEY_NULL);

    HideCursor();

    Texture2D crossbar_tex = LoadTexture("assets/crossbar.png");

    init();

    while(!WindowShouldClose())
    {
        update();
        BeginDrawing();
        ClearBackground(WHITE);
        late_update();
        DrawTextureEx(crossbar_tex, (Vector2){.x = GetMouseX() - 16, .y = GetMouseY() - 16}, 0, 2, BLACK);
        EndDrawing();
    }
    end();
    CloseWindow();

    return 0;
}