#include "raylib.h"
#include <bits/stdc++.h>
#include "bullet.h"
#include "player.h"
#include "enemy.h"

int main(void)
{
    freopen("log","w",stderr);
    const int screenWidth = 800;
    const int screenHeight = 600;
    Player player;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);
    
    BulletManager playerBullets;
    EnemyManager enemys;

    bool flag = 0;

    while (!WindowShouldClose())
    {
        float time=GetTime();

        if (flag == 0) {
            enemys.addEnemy(new SimpleEnemy(100.0, time, 20, 400, 50, 5));
            flag = 1;
        }

        player.Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if(IsKeyDown(KEY_X)){
            playerBullets.addBullet(new basicBullet(time, 3, player.getPosition(), {(1.*rand()/RAND_MAX-0.5)*2,(1.*rand()/RAND_MAX-0.5)*2}));
        }
        
        auto bullets = enemys.updateTime(time);
        enemys.draw();
        for (auto b: bullets) playerBullets.addBullet(b);

        player.Draw();
        playerBullets.updateTime(time);
        playerBullets.DrawAllBullets();

        DrawText(TextFormat("%.5lf",time),10,10,20,RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
