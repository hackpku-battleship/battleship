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

Music Mus::openMusic;
Music Mus::stageMusics[4];
Music Mus::endMusic;

int LastPlayedMusic = -1;
//*/

int Init::loop(int screenWidth, int screenHeight)
{
    //StopMusicStream(openMusic);
    //std::cerr << GetMusicTimeLength(openMusic) << std::endl;
    const char msg1[50] = "Start Game";
    const char msg2[50] = "Instructions";
    float Mid = screenWidth / 2.0f - 200;
    Rectangle msg1Box = {Mid, screenHeight / 2.0f - 100, 380, 50};
    Rectangle msg2Box = {Mid, screenHeight / 2.0f + 50, 380, 50};
    bool mouseOnText1 = true, mouseOnText2 = true;
    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::openMusic);
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
            bullets[i]->parryed();
            //delete bullets[i];
            //bullets.erase(bullets.begin() + i);
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

int checkEnemysHit(EnemyManager *enemyManager, BulletManager *playerBullets)
{
    int destroyed = 0;
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
                    ++destroyed;
                    delete enemys[i];
                    enemys.erase(enemys.begin() + i);
                }
                break;
            }
    }
    enemyManager->setEnemys(enemys);
    playerBullets->setBullets(bullets);
    return destroyed;
}

int Init::choose(int screenWidth, int screenHeight)
{
    Image png3 = LoadImage("source/alice_huge.png");
    Image png1 = LoadImage("source/reimu_huge.png");
    Image png2 = LoadImage("source/marisa_huge.png");
    ImageResize(&png1, 400, 500);
    ImageResize(&png2, 400, 500);
    ImageResize(&png3, 400, 500);
    Texture2D h1 = LoadTextureFromImage(png1);
    Texture2D h2 = LoadTextureFromImage(png2);
    Texture2D h3 = LoadTextureFromImage(png3);
    UnloadImage(png1);
    UnloadImage(png2);
    UnloadImage(png3);
    const char hint[50] = {"Choose your hero :"};
    const char msg[4][50] = {"Reimu", "Marisa", "Reimu", "Back"};
    float Bott = screenHeight - 200;
    bool MouseOn[4];
    Rectangle msgBox[4] = {{300, Bott, 180, 50}, {700, Bott, 180, 50}, {1100, Bott, 180, 50}, {1400, Bott + 40, 100, 30}};
    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::openMusic);
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 3)
                    return Init::loop(screenWidth, screenHeight);
                else {
                    return Init::choose_stage(screenWidth, screenHeight, i);
                }
                    //return Game::loop(screenWidth, screenHeight, i , 0);
            }
        BeginDrawing();
        //ImageDrawRectangle(&hero1, 0,0, 300,500, RAYWHITE);
        DrawTexture(h1, 150, 100 , RAYWHITE);
        DrawTexture(h2, 550, 100 , RAYWHITE);
        DrawTexture(h3, 950, 100 , RAYWHITE);
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

int Init::choose_stage(int screenWidth, int screenHeight, int kind) {
    const char hint[50] = {"Choose the Level :"};
    const char msg[4][50] = {"Lv1", "Lv2", "Lv3", "Back"};
    float Mid = screenHeight / 2 - 100;
    bool MouseOn[4];
    Rectangle msgBox[4] = {{Mid, 200, 100, 50}, {Mid, 400, 100, 50}, {Mid, 600, 100, 50}, {Mid, 800, 100, 50}};
    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::openMusic);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 3)
                    return Init::choose(screenWidth, screenHeight);
                else {
                    StopMusicStream(Mus::openMusic);
                    PlayMusicStream(Mus::stageMusics[i]);
                    std::cerr << "stage play" << " " << GetMusicTimeLength(Mus::stageMusics[i]) << std::endl;
                    return Game::loop(screenWidth, screenHeight, kind, i);
                }
            }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(hint, 10, 10, 40, BLACK);
        for (int i = 0; i < 4; i++)
        {
            //DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], msgBox[i].x, msgBox[i].y,  50, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}

int Game::loop(int screenWidth, int screenHeight, int kind, int stage)
{
    //Image Bgimage = LoadImage("source/1.png");
    Texture2D Bgtexture = LoadTexture("source/bg-ps.png");

    const int FastSpeed = 500, SlowSpeed = 200;

    PlayerBar *playerHPBar = new PlayerBar(10, screenHeight - 20, 10, 25, MAROON);
    PlayerBar *playerLPBar = new PlayerBar(10, screenHeight - 50, 10, 25, BLUE);
    auto atk = std::make_shared<class Atk>(50);
    BulletManager *playerBullets = new BulletManager();
    BulletManager *enemyBullets = new BulletManager();
    EnemyManager *enemys = new EnemyManager();
    Player *player = new Player(initPlayerPosition, 5, 5, FastSpeed, SlowSpeed, 510, 1000, 2, kind);

    std::queue<std::pair<float, Enemy *> > enemyQueue;

    float time = 0.0;
    float playerLasttime = 0.0;

    const int MAX_STAGE = 3;
    int stagecnt = stage, destroyedEnemy = 0;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::stageMusics[stagecnt]);
        if (IsKeyPressed(KEY_P))
        {
            PauseMusicStream(Mus::stageMusics[stagecnt]);
            int ret = Pause::loop(screenWidth, screenHeight);
            ResumeMusicStream(Mus::stageMusics[stagecnt]);
            switch (ret)
            {
            case 0: //退出
                return 0;
            case 1: //重新开始
            {
                StopMusicStream(Mus::stageMusics[stagecnt]);
                PlayMusicStream(Mus::openMusic);
                return Init::choose(screenWidth, screenHeight);
            }
            case 2: //返回菜单
            {
                StopMusicStream(Mus::stageMusics[stagecnt]);
                PlayMusicStream(Mus::openMusic);
                return Init::loop(screenWidth, screenHeight);
            }
            default:
                break;
            }
        }

        if (player->getHP() <= 0) {
            StopMusicStream(Mus::stageMusics[stagecnt]);
            PlayMusicStream(Mus::endMusic);
            return Over::loop(screenWidth, screenHeight);
        }
        float deltatime = GetFrameTime();
        time += deltatime;

        if (stagecnt <= MAX_STAGE && enemys->isEmpty() && enemyBullets->isEmpty() && enemyQueue.empty())
        {
            if (stagecnt == MAX_STAGE)
            {
                StopMusicStream(Mus::stageMusics[stagecnt]);
                PlayMusicStream(Mus::endMusic);
                return Win::loop(screenWidth, screenHeight);
            }
            StopMusicStream(Mus::stageMusics[stagecnt]);
            stagecnt++;
            PlayMusicStream(Mus::stageMusics[stagecnt]);
            // std::cerr << stagecnt << std::endl;
            getStage(stagecnt, time, enemyQueue);
        }
        
        while (!enemyQueue.empty() && enemyQueue.front().first <= time)
        {
            enemys->addEnemy(enemyQueue.front().second);
            enemyQueue.pop();
        }
        
        player->Update(time);
        player->Move(deltatime);
        if (kind == 2)
            atk->Move(deltatime);
        BeginDrawing();

        ClearBackground(RAYWHITE);
        //draw background
        DrawLine(1000, 0, 1000, 900, BLACK);
        {
            int frameWidth = Bgtexture.width;
            int frameHeight = Bgtexture.height;
            std::cerr << frameHeight << " " << frameWidth << std::endl;
            Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
            Rectangle destRec = { 0.0, 0.0, 1000, 900};
            Vector2 origin = {0, 0};
            DrawTexturePro(Bgtexture, sourceRec, destRec, origin, 0.0, WHITE);
        }

        player->Check(time);
        atk->Check(screenWidth, screenHeight);
        if (IsKeyDown(KEY_Z)) // 放技能
            if (player->useskill(time) && kind == 2)
            {
                atk->Add(Vector2{player->getPosition().x, player->getPosition().y - player->getRadius()});
            }
        if (kind == 1 && time - player->Lastt < LASTOFRING)
        {
            float nowRadius = BOOMSCOPE * (1 - (LASTOFRING - (time - player -> Lastt)));
            DrawRing(player->getPosition(), nowRadius - 2, nowRadius, 0.f, 360.f, 1, RED);
            auto bullets = enemyBullets->getBullets();
            for (int i = 0; i < bullets.size(); i++)
                if (bullets[i]->checkBox(player->getPosition(), nowRadius))
                {
                    bullets[i]->parryed();
                    //delete bullets[i];
                    //bullets.erase(bullets.begin() + i);
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
                        new basicBullet(time, 5, enemyBullets, Fade(YELLOW, 0.2), 5,
                                        player->getPosition() + (Vector2){bias, -10.0}, (Vector2){0, -800}));
                }
                playerLasttime = time;
            }
        }

        if (IsKeyPressed(KEY_U))
        {
            float x = screenWidth / 3.0 + (1.0 * rand() / RAND_MAX - 0.5) * 100;
            float y = 100;
            enemys->addEnemy(new PredictEnemy(1000, time, 10000, {x, y}, 40, "source/lion.png"));
        }

        auto _bullets = enemys->updateTime(time, enemyBullets, player->getPosition());
        enemys->draw();
        for (auto b : _bullets)
            enemyBullets->addBullet(b);
        atk->HitBullet(enemyBullets);
        atk->HitEnemy(enemys);
        checkPlayerHit(player, enemyBullets, time);
        destroyedEnemy += checkEnemysHit(enemys, playerBullets);

        player->Draw();
        atk->Draw();
        playerHPBar->Draw(player->getHP());
        playerLPBar->Draw(player->getLP());
        playerBullets->updateTime(time, playgroundWidth, playgroundHeight, player->getPosition());
        playerBullets->DrawAllBullets();
        enemyBullets->updateTime(time, playgroundWidth, playgroundHeight, player->getPosition());
        enemyBullets->DrawAllBullets();

        // std::cerr<<enemyBullets->getBullets().size()<<std::endl;

        DrawText(TextFormat("FPS: %.0lf", 1 / GetFrameTime()), 10, 10, 20, RED);


        DrawText(TextFormat("STAGE %d", stagecnt), 1020, 10, 40, BLACK);
        DrawText(TextFormat("enemy destroyed: %d", destroyedEnemy), 1020, 50, 20, BLACK);

        EndDrawing();
    }
    return 0;
}

int Inst::loop(int screenWidth, int screenHeight)
{
    const char msg[50] = {"Back"};
    const char msg1[50] = {"Base operation"};
    const char msg2[50] = {"Skill intruction"};
    const char inst[9][50] = {{"Upward"}, {"Downward"}, {"Leftward"}, {"Rightward"},
                              {"Pause"}, {"Attack"}, {"Skill"}, {"Slow Move"}, {"Quit"}};
    const char Name[3][50] = {"Reimu", "Marisa", "Alice"};
    const char Skill[3][2][50] = {{{"Summon a unmbrella and it can resist"},
                                  {"the attack from the front, last 5s."}},
                                  {{"Instantly clears surrounding bullets."},
                                  {""}},
                                  {{"Launch a large bullet, it can clears the"},
                                   {"path and deal damage to the first enemy."}}};
    Image pg3 = LoadImage("source/alice.png");
    Image pg1 = LoadImage("source/reimu.png");
    Image pg2 = LoadImage("source/marisa.png");
    ImageResize(&pg1, 70, 70);
    ImageResize(&pg2, 70, 70);
    ImageResize(&pg3, 70, 70);
    Texture2D h1 = LoadTextureFromImage(pg1);
    Texture2D h2 = LoadTextureFromImage(pg2);
    Texture2D h3 = LoadTextureFromImage(pg3);
    
    Image png1 = LoadImage("source/inst.png");
    ImageResize(&png1, 150, 700);
    Texture2D ky = LoadTextureFromImage(png1);
    UnloadImage(png1);
    
    float Mid = screenWidth / 2.0f - 200;
    Rectangle msgBox = {1400, screenHeight / 2.0f + 400, 120, 25};
    bool MouseOn = true;
    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::openMusic);
        ClearBackground(RAYWHITE);
        MouseOn = CheckCollisionPointRec(GetMousePosition(), msgBox);
        // DrawRectangleRec(msgBox, LIGHTGRAY);
        if (MouseOn && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return 1;
        BeginDrawing();
        DrawTexture(ky, 550, 150 , RAYWHITE);
        DrawLine(800, 100, 800, 850, BLACK);
        DrawText(msg1, 200, 50, 60, BLACK);
        DrawText(msg2, 900, 50, 60, BLACK);
        DrawText(msg, msgBox.x, msgBox.y, 30, MouseOn ? RED : BLACK);
        for (int i = 0; i < 9; i++)
            DrawText(inst[i], 100, 150 + i * 80,50,BLUE);
        for (int i = 0; i < 3; i++) {
            DrawText(Name[i], 900, 150 + 200 * i, 40, ORANGE);
            for (int j = 0; j < 2 ;j++)
                DrawText(Skill[i][j], 950, 250 + 200 * i + 30*j, 30, PURPLE);
        }
        DrawTexture(h1, 1200, 150 , RAYWHITE);
        DrawTexture(h2, 1200, 350 , RAYWHITE);
        DrawTexture(h3, 1200, 550 , RAYWHITE);
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
        UpdateMusicStream(Mus::endMusic);
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 3; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 3; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 2) {
                    StopMusicStream(Mus::endMusic);
                    return 0;
                }
                else if (i == 1) {
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::loop(screenWidth, screenHeight);
                }
                else{
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::choose(screenWidth, screenHeight);
                }
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

int Win::loop(int screenWidth, int screenHeight)
{
    const char msg[3][50] = {"New Game", "Return to menu", "Quit"};
    const char allclear[50] = {"All clean!"};
    float Mid = screenWidth / 2.0f - 200;

    Rectangle msgBox[3] = {{Mid, screenHeight / 2.0f - 100, 300, 50}, {Mid, screenHeight / 2.0f + 0, 480, 50}, {Mid, screenHeight / 2.0f + 100, 130, 50}};
    bool MouseOn[3];

    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::endMusic);
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 3; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 3; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 2) {
                    StopMusicStream(Mus::endMusic);
                    return 0;
                }
                else if (i == 1) {
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::loop(screenWidth, screenHeight);
                }
                else {
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::choose(screenWidth, screenHeight);
                }
            }
        BeginDrawing();
        DrawText(allclear, Mid - 40, 200, 80, RED);
        for (int i = 0; i < 3; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], Mid, msgBox[i].y, 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}