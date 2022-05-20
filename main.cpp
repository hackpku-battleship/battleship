#include "raylib.h"
#include "bullet.h"
#include "player.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Player player({400, 600}, 10, 5, 50, 300);
    PlayerHPBar playerHPBar(10, screenHeight - 20, 10, 25);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        player.Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);
        player.Draw();
        playerHPBar.Draw(player.getHP());
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
