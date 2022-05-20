#include "raylib.h"
#include <bits/stdc++.h>
#include "basicBullet.h"
#include "fishBullet.h"
#include "bulletManager.h"
#include "player.h"
#include "enemy.h"
const int screenWidth = 800;
const int screenHeight = 600;

int main(void)
{
    freopen("log", "w", stderr);
    Player player({400, 600}, 10, 5, 10, 300);
    PlayerHPBar playerHPBar(10, screenHeight - 20, 10, 25);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);

    BulletManager playerBullets;
    EnemyManager enemys;

    bool flag = 0;

    while (!WindowShouldClose())
    {
        float time = GetTime();

        if (flag == 0) {
            enemys.addEnemy(new SimpleEnemy(100.0, time, 20, 400, 50, 5));
            flag = 1;
        }

        player.Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_X))
        {
            //playerBullets.addBullet(new fishBullet(time, 5, player.getPosition(), 250, 0.1*float(1.0*rand()/RAND_MAX)));
        }
        
        auto bullets = enemys.updateTime(time);
        enemys.draw();
        for (auto b: bullets) playerBullets.addBullet(b);

        player.Draw();
        playerHPBar.Draw(player.getHP());
        playerBullets.updateTime(time, screenHeight, screenWidth, player.getPosition());
        playerBullets.DrawAllBullets();

        DrawText(TextFormat("%.5lf", time), 10, 10, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
