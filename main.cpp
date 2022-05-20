#include "raylib.h"
#include <bits/stdc++.h>
#include "bullet.h"
#include "player.h"

int main(void)
{
    freopen("log", "w", stderr);
    const int screenWidth = 800;
    const int screenHeight = 600;
    Player player({400, 600}, 10, 5, 50, 300);
    PlayerHPBar playerHPBar(10, screenHeight - 20, 10, 25);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);

    BulletManager playerBullets;

    while (!WindowShouldClose())
    {
        float time = GetTime();

        player.Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_X))
        {
            playerBullets.addBullet(new basicBullet(time, 3, player.getPosition(), {(1. * rand() / RAND_MAX - 0.5) * 2, (1. * rand() / RAND_MAX - 0.5) * 2}));
        }

        player.Draw();
        playerHPBar.Draw(player.getHP());
        playerBullets.updateTime(time);
        playerBullets.DrawAllBullets();

        DrawText(TextFormat("%.5lf", time), 10, 10, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
