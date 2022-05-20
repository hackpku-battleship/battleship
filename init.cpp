#include <cstdio>
#include "init.h"
#include "raylib.h"
#include "player.h"
#include "bullet.h"
#include "basicBullet.h"
#include "bulletManager.h"
#include "enemy.h"

int Init::loop(int screenWidth, int screenHeight) {
    const char msg1[50] = "Start Game";
    const char msg2[50] = "Instructions";
    float Mid = screenWidth / 2.0f - 200;
    Rectangle msg1Box = { Mid, screenHeight / 2.0f - 100, 380,50 };
    Rectangle msg2Box = { Mid, screenHeight / 2.0f + 50, 380,50 };
    bool mouseOnText1 = true, mouseOnText2 = true;
    while (!WindowShouldClose()) {
        mouseOnText1 = false, mouseOnText2 = false;
        if (CheckCollisionPointRec(GetMousePosition(), msg1Box)) mouseOnText1 = true;
        if (CheckCollisionPointRec(GetMousePosition(), msg2Box)) mouseOnText2 = true;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnText1) { // 进入游戏界面
            return Game::loop(screenWidth, screenHeight);
        } else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnText2) { // 进入说明界面
            int ret = Inst::loop(screenWidth, screenHeight);
            if (!ret) return 0;
        }
        // 初始界面    
        auto col1 = mouseOnText1 ? RED : BLACK;
        auto col2 = mouseOnText2 ? RED : BLACK;
        DrawText(msg1,  Mid, screenHeight / 2.0f - 100, 60, col1);
        DrawText(msg2,  Mid, screenHeight / 2.0f + 50, 60, col2);
        EndDrawing();
    }
    return 0;
}

int Game::loop(int screenWidth, int screenHeight) {
    Image Bgimage = LoadImage("source/1.png");
    Texture2D Bgtexture = LoadTextureFromImage(Bgimage);

    Player *player = new Player({400, 600}, 10, 5, 10, 300, 2);
    PlayerHPBar *playerHPBar = new PlayerHPBar(10, screenHeight - 20, 10, 25);

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

        bool hit = enemyBullets->checkBox(player->getPosition(), player->getRadius());
        if (hit)
            player->Hit(time);

        player->Draw();
        playerHPBar->Draw(player->getHP());
        playerBullets->updateTime(time, screenWidth, screenHeight, player->getPosition());
        playerBullets->DrawAllBullets();
        enemyBullets->updateTime(time, screenWidth, screenHeight, player->getPosition());
        enemyBullets->DrawAllBullets();

        DrawText(TextFormat("%.5lf", time), 10, 10, 20, RED);

        EndDrawing();
    }
    return 0;
}

int Inst::loop(int screenWidth, int screenHeight) {
    const char msg[50] = {"Back"};
    float Mid = screenWidth / 2.0f - 200;
    Rectangle msgBox = {Mid, screenHeight / 2.0f + 200, 150, 50};
    bool MouseOn = true;
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        MouseOn = CheckCollisionPointRec(GetMousePosition(), msgBox);
        BeginDrawing();
        //DrawRectangleRec(msgBox, LIGHTGRAY);
        if (MouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            return 1;
        DrawText(msg,  Mid, msgBox.y, 60, MouseOn ? RED : BLACK);
        EndDrawing();
    }
    return 0;
}

int Pause::loop(int screenWidth, int screenHeight) {
    const char msg[4][50] = {"Continue", "New Game", "Return to menu", "Instructions"};
    float Mid = screenWidth / 2.0f - 200;
    
    Rectangle msgBox[4] = {{ Mid, screenHeight / 2.0f - 200, 280,50 }
                          ,{ Mid, screenHeight / 2.0f - 100, 300,50 }
                          ,{ Mid, screenHeight / 2.0f + 0, 480,50 }
                          ,{ Mid, screenHeight / 2.0f + 100, 380,50 } };
    bool MouseOn[4]; 
    while (!WindowShouldClose()) {
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++) 
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (i == 0) return 3;
                else if(i != 3) return i;
                else {
                    int ret = Inst::loop(screenWidth, screenHeight);
                    if (!ret) return 0;
                }
            }
        BeginDrawing();
        for (int i = 0; i < 4; i++) {
            //DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i],  Mid, msgBox[i].y, 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}