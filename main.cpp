#include "raylib.h"
#include <bits/stdc++.h>
#include "bullet.h"
#include "player.h"
#include "enemy.h"

int main(void)
{
    freopen("log", "w", stderr);
    const int screenWidth = 800;
    const int screenHeight = 600;
    Player *player = new Player({400, 600}, 10, 5, 10, 300, 2);
    PlayerHPBar *playerHPBar = new PlayerHPBar(10, screenHeight - 20, 10, 25);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - custom frame control");
    SetTargetFPS(60);

    BulletManager *playerBullets = new BulletManager();
    BulletManager *enemyBullets = new BulletManager();
    EnemyManager *enemys = new EnemyManager();

    bool flag = 0;

    while (!WindowShouldClose())
    {
        float time = GetTime();

        if (flag == 0)
        {
            enemys->addEnemy(new SimpleEnemy(100.0, time, 20, 400, 50, 5));
            flag = 1;
        }
        player->Update(time);
        player->Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_X))
        {
            playerBullets->addBullet(new basicBullet(time, 5, player->getPosition(), {(1. * rand() / RAND_MAX - 0.5) * 100, (1. * rand() / RAND_MAX - 0.5) * 100}));
        }

        auto bullets = enemys->updateTime(time);
        enemys->draw();
        for (auto b : bullets)
            enemyBullets->addBullet(b);

        bool hit = enemyBullets->checkHit(player->getPosition(), player->getRadius());
        if (hit)
            player->Hit(time);

        player->Draw();
        playerHPBar->Draw(player->getHP());
        playerBullets->updateTime(time);
        playerBullets->DrawAllBullets();
        enemyBullets->updateTime(time);
        enemyBullets->DrawAllBullets();

        DrawText(TextFormat("%.5lf", time), 10, 10, 20, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
