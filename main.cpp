#include "raylib.h"
#include "bullet.h"
#include "player.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Player player;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player.Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);
        player.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
