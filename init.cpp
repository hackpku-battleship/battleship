#include <cstdio>
#include "init.h"
#include "raylib.h"
#include "player.h"
#include "bullet.h"
#include "basicBullet.h"
#include "bulletManager.h"
#include "enemy.h"
#include "enemymanager.h"
#include "simpleenemy.h"
#include "denemy.h"
#include "Vector2Basic.h"

const Vector2 initPlayerPosition = {400, 900};

int Init::loop(int screenWidth, int screenHeight)
{
    const char msg1[50] = "Start Game";
    const char msg2[50] = "Instructions";
    float Mid = screenWidth / 2.0f - 200;
    Rectangle msg1Box = {Mid, screenHeight / 2.0f - 100, 380, 50};
    Rectangle msg2Box = {Mid, screenHeight / 2.0f + 50, 380, 50};
    bool mouseOnText1 = true, mouseOnText2 = true;
    while (!WindowShouldClose())
    {
        mouseOnText1 = false, mouseOnText2 = false;
        if (CheckCollisionPointRec(GetMousePosition(), msg1Box))
            mouseOnText1 = true;
        if (CheckCollisionPointRec(GetMousePosition(), msg2Box))
            mouseOnText2 = true;
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnText1)
        { // 进入游戏界面
            return Init::choose(screenWidth, screenHeight);
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnText2)
        { // 进入说明界面
            int ret = Inst::loop(screenWidth, screenHeight);
            if (!ret)
                return 0;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnText2)
        { // 进入说明界面
            int ret = Inst::loop(screenWidth, screenHeight);
            if (!ret)
                return 0;
        }
        // 初始界面
        auto col1 = mouseOnText1 ? RED : BLACK;
        auto col2 = mouseOnText2 ? RED : BLACK;
        DrawText(msg1, Mid, screenHeight / 2.0f - 100, 60, col1);
        DrawText(msg2, Mid, screenHeight / 2.0f + 50, 60, col2);
        EndDrawing();
    }
    return 0;
}

void checkPlayerHit(Player *player, BulletManager *enemyBullets, float nowTime)
{
    auto bullets = enemyBullets->getBullets();
    bool flag = 0;
    for (int i = 0; i < bullets.size(); i++)
        if (player->getcanHit() && bullets[i]->checkBox(player->getPosition(), player->getRadius()))
        {
            player->Hit(nowTime);
            player->setPosition(initPlayerPosition);
            flag = 1;
            break;
        }
    if (flag) {
        for (int i = 0; i < bullets.size(); i++) {
            delete bullets[i];
        }
        bullets.erase(bullets.begin(), bullets.end());
    }
    enemyBullets->setBullets(bullets);
}

void checkEnemysHit(EnemyManager *enemyManager, BulletManager *playerBullets)
{
    auto enemys = enemyManager->getEnemys();
    auto bullets = playerBullets->getBullets();
    for (int i = 0; i < enemys.size(); i++)
    {
        for (int j = 0; j < bullets.size(); j++)
            if (bullets[j]->checkBox({enemys[i]->getX(), enemys[i]->getY()}, enemys[i]->getR()))
            {
                bullets.erase(bullets.begin() + j);
                enemys[i]->hit();
                if (!enemys[i]->isalive())
                    enemys.erase(enemys.begin() + i);
                break;
            }
    }
    enemyManager->setEnemys(enemys);
    playerBullets->setBullets(bullets);
}

int Init::choose(int screenWidth, int screenHeight)
{
    const char hint[50] = {"Choose your hero :"};
    const char msg[4][50] = {"Hero1", "Hero2", "Hero3", "Back"};
    float Bott = screenHeight - 200;
    bool MouseOn[4];
    Rectangle msgBox[4] = {{300, Bott, 180, 50}, {700, Bott, 180, 50}, {1100, Bott, 180, 50}, {1400, Bott + 40, 100, 30}};
    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 3)
                    return Init::loop(screenWidth, screenHeight);
                else
                    return Game::loop(screenWidth, screenHeight, i);
            }
        BeginDrawing();
        DrawText(hint, 10, 10, 40, BLACK);
        for (int i = 0; i < 4; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], msgBox[i].x, msgBox[i].y, i == 3 ? 30 : 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}

int Game::loop(int screenWidth, int screenHeight, int kind)
{
    Image Bgimage = LoadImage("source/1.png");
    Texture2D Bgtexture = LoadTextureFromImage(Bgimage);

    Player *player = new Player(initPlayerPosition, 10, 5, 10, 100, 2);
    PlayerHPBar *playerHPBar = new PlayerHPBar(10, screenHeight - 20, 10, 25);

    BulletManager *playerBullets = new BulletManager();
    BulletManager *enemyBullets = new BulletManager();
    EnemyManager *enemys = new EnemyManager();

    float time = 0.0;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_P))
        {
            int ret = Pause::loop(screenWidth, screenHeight);
            switch (ret)
            {
            case 0: //退出
                return 0;
            case 1: //重新开始
                return Init::choose(screenWidth, screenHeight);
            case 2: //返回菜单
                return Init::loop(screenWidth, screenHeight);
            default:
                break;
            }
        }

        if (player->getHP() <= 0) return Over::loop(screenWidth, screenHeight);
        time += GetFrameTime();

        player->Update(time);
        player->Move();
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (IsKeyDown(KEY_X))
        {
            static float playerLasttime = 0.0;
            if (time - playerLasttime > 0.05) {
                for (float bias = -100; bias <= 100; bias += 20) {
                    playerBullets->addBullet(
                        new basicBullet(time, 5, RED, 5, 
                            player->getPosition() + (Vector2){bias, -10.0}, (Vector2){0, -300}));
                }
                playerLasttime = time;
            }
        }

        if (IsKeyPressed(KEY_U))
        {
            float x = screenWidth / 3.0 + (1.0 * rand() / RAND_MAX - 0.5) * 100;
            float y = 100;
            enemys->addEnemy(new DEnemy(100, time, 30, x, y, 10));
        }

        auto _bullets = enemys->updateTime(time, enemyBullets);
        enemys->draw();
        for (auto b : _bullets)
            enemyBullets->addBullet(b);

        checkPlayerHit(player, enemyBullets, time);
        checkEnemysHit(enemys, playerBullets);

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

int Inst::loop(int screenWidth, int screenHeight)
{
    const char msg[50] = {"Back"};
    float Mid = screenWidth / 2.0f - 200;
    Rectangle msgBox = {Mid, screenHeight / 2.0f + 200, 150, 50};
    bool MouseOn = true;
    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        MouseOn = CheckCollisionPointRec(GetMousePosition(), msgBox);
        BeginDrawing();
        // DrawRectangleRec(msgBox, LIGHTGRAY);
        if (MouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return 1;
        DrawText(msg, Mid, msgBox.y, 60, MouseOn ? RED : BLACK);
        EndDrawing();
    }
    return 0;
}

int Pause::loop(int screenWidth, int screenHeight)
{
    const char msg[4][50] = {"Continue", "New Game", "Return to menu", "Instructions"};
    float Mid = screenWidth / 2.0f - 200;

    Rectangle msgBox[4] = {{Mid, screenHeight / 2.0f - 200, 280, 50}, {Mid, screenHeight / 2.0f - 100, 300, 50}, {Mid, screenHeight / 2.0f + 0, 480, 50}, {Mid, screenHeight / 2.0f + 100, 380, 50}};
    bool MouseOn[4];
    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 0)
                    return 3;
                else if (i != 3)
                    return i;
                else
                {
                    int ret = Inst::loop(screenWidth, screenHeight);
                    if (!ret)
                        return 0;
                }
            }
        BeginDrawing();
        for (int i = 0; i < 4; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], Mid, msgBox[i].y, 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
        if (IsKeyPressed(KEY_P))
            return 3;
    }
    return 0;
}

int Over::loop(int screenWidth, int screenHeight)
{
    const char msg[3][50] = {"New Game", "Return to menu", "Quit"};
    float Mid = screenWidth / 2.0f - 200;

    Rectangle msgBox[3] = {{Mid, screenHeight / 2.0f - 100, 300, 50}, {Mid, screenHeight / 2.0f + 0, 480, 50}, {Mid, screenHeight / 2.0f + 100, 130, 50}};
    bool MouseOn[3];

    while (!WindowShouldClose())
    {
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 3; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 3; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 2)
                    return 0;
                else if (i == 1)
                    return Init::loop(screenWidth, screenHeight);
                else
                    return Init::choose(screenWidth, screenHeight);
            }
        BeginDrawing();
        for (int i = 0; i < 3; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], Mid, msgBox[i].y, 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}