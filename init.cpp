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
#include "easyenemy.h"
#include "predictenemy.h"
#include "Vector2Basic.h"
#include <queue>
#include "stages.h"

const Vector2 initPlayerPosition = {400, 900};
const int playgroundWidth = 1000;
const int playgroundHeight = 900;

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
        //检测是否碰撞，当无敌时不考虑是否被Hit
        if (player->prot != nullptr && bullets[i]->checkProt(player->getPosition(), player->getRadius()))
        {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
        else if (player->getcanHit() && bullets[i]->checkBox(player->getPosition(), player->getRadius()))
        {
            player->Hit(nowTime);
            //将玩家置为初始位置
            player->setPosition(initPlayerPosition);
            flag = 1;
            break;
        }
    //当发生Hit时
    if (flag)
    {
        for (int i = 0; i < bullets.size(); i++)
        {
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
                delete bullets[j];
                bullets.erase(bullets.begin() + j);
                enemys[i]->hit();
                if (!enemys[i]->isalive())
                {
                    delete enemys[i];
                    enemys.erase(enemys.begin() + i);
                }
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

    const int FastSpeed = 500, SlowSpeed = 200;

    PlayerHPBar *playerHPBar = new PlayerHPBar(10, screenHeight - 20, 10, 25);
    auto atk = std::make_shared<class Atk>(50);
    BulletManager *playerBullets = new BulletManager();
    BulletManager *enemyBullets = new BulletManager();
    EnemyManager *enemys = new EnemyManager();
    Player *player = new Player(initPlayerPosition, 5, 5, FastSpeed, SlowSpeed, 100, 1000, 2, kind);

    std::queue<std::pair<float, Enemy *>> enemyQueue;

    float time = 0.0;
    float playerLasttime = 0.0;

    const int MAX_STAGE = 3;
    int stagecnt = 2;

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

        if (player->getHP() <= 0)
            return Over::loop(screenWidth, screenHeight);
        float deltatime = GetFrameTime();
        time += deltatime;

        if (stagecnt < MAX_STAGE && enemys->isEmpty() && enemyBullets->isEmpty() && enemyQueue.empty())
        {
            stagecnt++;
            // std::cerr << stagecnt << std::endl;
            getStage(stagecnt, time, enemyQueue);
        }

        /*while (!enemyQueue.empty() && enemyQueue.front().first <= time)
        {
            enemys->addEnemy(enemyQueue.front().second);
            enemyQueue.pop();
        }*/

        player->Update(time);
        player->Move(deltatime);
        if (kind == 2)
            atk->Move(deltatime);
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawLine(1000, 0, 1000, 900, BLACK);
        player->Check(time);
        atk->Check(screenWidth, screenHeight);
        if (IsKeyDown(KEY_Z)) // 放技能
            if (player->useskill(time) && kind == 2)
            {
                atk->Add(Vector2{player->getPosition().x, player->getPosition().y - player->getRadius()});
            }
        if (kind == 1 && time - player->Lastt < LASTOFRING)
        {
            DrawRing(player->getPosition(), BOOMSCOPE - 2, BOOMSCOPE, 0.f, 360.f, 1, RED);
            auto bullets = enemyBullets->getBullets();
            for (int i = 0; i < bullets.size(); i++)
                if (bullets[i]->checkBox(player->getPosition(), BOOMSCOPE))
                {
                    delete bullets[i];
                    bullets.erase(bullets.begin() + i);
                }
            enemyBullets->setBullets(bullets);
        }
        if (IsKeyDown(KEY_X))
        {
            if (time - playerLasttime > 0.05)
            {
                for (float bias = -100; bias <= 100; bias += 20)
                {
                    playerBullets->addBullet(
                        new basicBullet(time, 5, enemyBullets, RED, 5,
                                        player->getPosition() + (Vector2){bias, -10.0}, (Vector2){0, -800}));
                }
                playerLasttime = time;
            }
        }

        if (IsKeyPressed(KEY_U))
        {
            float x = screenWidth / 3.0 + (1.0 * rand() / RAND_MAX - 0.5) * 100;
            float y = 100;
            enemys->addEnemy(new PredictEnemy(100, time, 20, {x, y}, 10, "source/lion.png"));
        }

        auto _bullets = enemys->updateTime(time, enemyBullets, player->getPosition());
        enemys->draw();
        for (auto b : _bullets)
            enemyBullets->addBullet(b);
        atk->HitBullet(enemyBullets);
        checkPlayerHit(player, enemyBullets, time);
        checkEnemysHit(enemys, playerBullets);

        player->Draw();
        atk->Draw();
        playerHPBar->Draw(player->getHP());
        playerBullets->updateTime(time, playgroundWidth, playgroundHeight, player->getPosition());
        playerBullets->DrawAllBullets();
        enemyBullets->updateTime(time, playgroundWidth, playgroundHeight, player->getPosition());
        enemyBullets->DrawAllBullets();

        // std::cerr<<enemyBullets->getBullets().size()<<std::endl;

        DrawText(TextFormat("FPS: %.0lf", 1 / GetFrameTime()), 10, 10, 20, RED);

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
    const char gg[50] = {"Game Over!"};
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
        DrawText(gg, Mid - 40, 200, 80, RED);
        for (int i = 0; i < 3; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], Mid, msgBox[i].y, 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}