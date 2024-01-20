#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720
#define TITLE "Wave"
#define FPS 60
#define SIZE_MULTIPLIER 4

extern bool DEBUG;

extern Camera2D* camera;

extern const int WORLD_BOUNDARY_X, WORLD_BOUNDARY_Y;

void init();
void update();
void late_update();
void end();

#endif