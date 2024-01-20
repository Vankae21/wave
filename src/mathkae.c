#include "include/mathkae.h"
#include "include/game.h"

Vector2 normalize_vec(Vector2 vec)
{
    if(vec.x == 0 || vec.y == 0) return vec;
    Vector2 result = {.x = sqrt(vec.x * vec.x + vec.y * vec.y) / 2, .y = sqrt(vec.x * vec.x + vec.y * vec.y) / 2};

    if(vec.x < 0) result.x *= -1;
    if(vec.y < 0) result.y *= -1;

    return result;
}
float easeOut(float t) {
    return sinf(t * PI / 2); // You can experiment with different easing functions
}
Vector2 lerp(Vector2 a, Vector2 b, float speed)
{
    Vector2 result = a;

    if(b.x < WIDTH / 2.0f - 32)
    {
        b.x = WIDTH / 2.0f - 32;
    }
    else if(b.x > WORLD_BOUNDARY_X - WIDTH / 2.0f - 32)
    {
        b.x = WORLD_BOUNDARY_X - WIDTH / 2.0f - 32;
    }
    if(b.y < HEIGHT / 2.0f - 32)
    {
        b.y = HEIGHT / 2.0f - 32;
    }
    else if(b.y > WORLD_BOUNDARY_Y - HEIGHT / 2.0f - 32)
    {
        b.y = WORLD_BOUNDARY_Y - HEIGHT / 2.0f - 32;
    }
    

    float t = fmin(1.0f, speed * GetFrameTime()); // Progress of movement, limited to 1

    // Calculate the direction to move in each axis
    float dirX = (b.x >= a.x) ? 1.0f : -1.0f;
    float dirY = (b.y >= a.y) ? 1.0f : -1.0f;

    // Calculate the distance to the target in each axis
    float distX = fabs(b.x - a.x);
    float distY = fabs(b.y - a.y);

    // Apply ease-out effect based on the progress (t)
    float easedDistX = easeOut(t) * distX;
    float easedDistY = easeOut(t) * distY;

    // Move towards the target in each axis
    if (distX > 0.01f) {
        result.x += dirX * fmin(easedDistX, distX);
    }

    if (distY > 0.01f) {
        result.y += dirY * fmin(easedDistY, distY);
    }

    return result;
}