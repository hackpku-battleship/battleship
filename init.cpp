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
#include <memory>
#include "stages.h"

const Vector2 initPlayerPosition = {400, 900};
const int playgroundWidth = 1000;
const int playgroundHeight = 900;

Gif::Gif(int _T):totalframe(_T),currentframe(0){
}

void Gif::Load(std::string path) {
    for (int i = 0; i < totalframe; i++) {
        std::string tmp = "source/" + path + "/" + path + "-" + std::to_string(i) + ".png";
        Image png = LoadImage(tmp.c_str());
        ImageResize(&png, 1600, 900);

        src.push_back(LoadTextureFromImage(png));
        UnloadImage(png);
    }
}

void Gif::Draw(int X, int Y) {
    DrawTexture(src[currentframe / 10], X, Y, RAYWHITE);
    currentframe = (currentframe + 1 ) % (totalframe*10);
}

Gif::~Gif() {
    for (auto it: src) {
        UnloadTexture(it);
    }
    return;
}

Music Mus::openMusic;
Music Mus::stageMusics[4];
Music Mus::endMusic;
Music Mus::killedMusic;
Texture2D Img::t1;
Texture2D Img::t2;
Texture2D Img::t3;
Texture2D Img::h1;
Texture2D Img::h2;
Texture2D Img::h3;
Texture2D Img::ky;
Texture2D Img::sr;
Texture2D Img::sr2;
std::shared_ptr<Gif> Img::gif;

void Img::Init() {
    {
        Image png3 = LoadImage("source/marisa_huge2.png");
        Image png1 = LoadImage("source/yuka_huge.png");
        Image png2 = LoadImage("source/reimu_huge2.png");
        ImageResize(&png1, 400 - 10, 500);
        ImageResize(&png2, 400 - 10, 500);
        ImageResize(&png3, 400 - 10, 500);
        t1 = LoadTextureFromImage(png1);
        t2 = LoadTextureFromImage(png2);
        t3 = LoadTextureFromImage(png3);
        UnloadImage(png1);
        UnloadImage(png2);
        UnloadImage(png3);
    }
    BeginDrawing();
        //DrawLine(0, 450, 1600, 450, BLACK);
        //DrawLine(800, 0, 800, 900, BLACK);
        ClearBackground(RAYWHITE);
        DrawText("Loading..", 10, 10, 80, BLACK);
    EndDrawing();
    {
        Image pg3 = LoadImage("source/marisa.png");
        Image pg1 = LoadImage("source/yuka.png");
        Image pg2 = LoadImage("source/reimu.png");
        ImageResize(&pg1, 70, 70);
        ImageResize(&pg2, 70, 70);
        ImageResize(&pg3, 70, 70);
        h1 = LoadTextureFromImage(pg1);
        h2 = LoadTextureFromImage(pg2);
        h3 = LoadTextureFromImage(pg3);
        Image png1 = LoadImage("source/inst.png");
        ImageResize(&png1, 150, 700);
        ky = LoadTextureFromImage(png1);
        UnloadImage(png1);
    }
    BeginDrawing();
        //DrawLine(0, 450, 1600, 450, BLACK);
        //DrawLine(800, 0, 800, 900, BLACK);
        ClearBackground(RAYWHITE);
        DrawText("Loading...", 10, 10, 80, BLACK);
    EndDrawing();
    {
        gif = std::make_shared<Gif> (18);
        gif->Load("initbg");
    }
    BeginDrawing();
        //DrawLine(0, 450, 1600, 450, BLACK);
        //DrawLine(800, 0, 800, 900, BLACK);
        ClearBackground(RAYWHITE);
        DrawText("Loading....", 10, 10, 80, BLACK);
    EndDrawing();
    {
        Image irm = LoadImage("source/reimu_simple.png");
        ImageResize(&irm, 600, 800);
        sr = LoadTextureFromImage(irm);
        UnloadImage(irm);

        irm = LoadImage("source/reimu_simple2.png");
        ImageResize(&irm, 600, 800);
        sr2 = LoadTextureFromImage(irm);
        UnloadImage(irm);
    }
}

void Img::Release() {
    UnloadTexture(t1);
    UnloadTexture(t2);
    UnloadTexture(t3);
    UnloadTexture(h1);
    UnloadTexture(h2);
    UnloadTexture(h3);
    UnloadTexture(ky);
    UnloadTexture(sr);
    UnloadTexture(sr2);
    //gif->release();
    //delete gif;
}

int LastPlayedMusic = -1;
//*/

int Init::loop(int screenWidth, int screenHeight)
{
    // StopMusicStream(openMusic);
    // std::cerr << GetMusicTimeLength(openMusic) << std::endl;
    const char msg0[50] = "Battleship Shooting";
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
        { // ??????????????????
            return Init::choose(screenWidth, screenHeight);
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseOnText2)
        { // ??????????????????
            int ret = Inst::loop(screenWidth, screenHeight);
            if (!ret)
                return 0;
        }
        // ????????????
        auto col1 = mouseOnText1 ? GOLD : WHITE;
        auto col2 = mouseOnText2 ? GOLD : WHITE;
        Img::gif->Draw(0,0);
        DrawText(msg0, Mid - 300, screenHeight / 2.0f - 300, 100, SKYBLUE);
        DrawText(msg1, Mid, msg1Box.y, 60, col1);
        DrawText(msg2, Mid, msg2Box.y, 60, col2);
        EndDrawing();
    }
    return 0;
}

int checkPlayerHit(Player *player, BulletManager *enemyBullets, float nowTime)
{
    auto bullets = enemyBullets->getBullets();
    int flag = 0;
    for (int i = 0; i < bullets.size(); i++)
        //???????????????????????????????????????????????????Hit
        if (player->prot != nullptr && bullets[i]->checkProt(player->getPosition(), player->getRadius()))
        {
            bullets[i]->parryed();
            // delete bullets[i];
            // bullets.erase(bullets.begin() + i);
        }
        else if (player->getcanHit() && bullets[i]->checkBox(player->getPosition(), player->getRadius()))
        {
            player->Hit(nowTime);
            //???????????????????????????
            player->setPosition(initPlayerPosition);
            flag = 1;
            break;
        }
    //?????????Hit???
    if (flag)
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            delete bullets[i];
        }
        bullets.erase(bullets.begin(), bullets.end());
    }
    enemyBullets->setBullets(bullets);
    return flag;
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
    const char hint[50] = {"Choose your player :"};
    const char msg[4][50] = {"Yuka", "Reimu", "Marisa", "Back"};
    float Bott = screenHeight - 200;
    bool MouseOn[4];
    Rectangle msgBox[4] = {{300, Bott, 180, 50}, {700, Bott, 180, 50}, {1100, Bott, 180, 50}, {1400, Bott + 40, 100, 30}};
    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::openMusic);
        Img::gif->Draw(0, 0);
        ClearBackground(RAYWHITE);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 3)
                    return Init::loop(screenWidth, screenHeight);
                else
                {
                    return Init::choose_stage(screenWidth, screenHeight, i);
                }
                // return Game::loop(screenWidth, screenHeight, i , 0);
            }
        BeginDrawing();
        //ImageDrawRectangle(&hero1, 0,0, 300,500, RAYWHITE);
        DrawTexture(Img::t1, 150, 100 , RAYWHITE);
        DrawTexture(Img::t2, 550, 100 , RAYWHITE);
        DrawTexture(Img::t3, 950, 100 , RAYWHITE);
        DrawText(hint, 10, 10, 40, WHITE);
        for (int i = 0; i < 4; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], msgBox[i].x, msgBox[i].y, i == 3 ? 30 : 60, MouseOn[i] ? GOLD : WHITE);
        }
        EndDrawing();
    }
    return 0;
}

int Init::choose_stage(int screenWidth, int screenHeight, int kind) {
    const char hint[50] = {"Choose the Stage :"};
    const char msg[4][50] = {"Stage1", "Stage2", "Stage3", "Back"};
    float Mid = screenHeight / 2 - 100;
    bool MouseOn[4];
    Rectangle msgBox[4] = {{Mid, 200, 100, 50}, {Mid, 400, 100, 50}, {Mid, 600, 100, 50}, {Mid, 800, 100, 50}};
    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::openMusic);
        Img::gif->Draw(0, 0);
        for (int i = 0; i < 4; i++)
            MouseOn[i] = CheckCollisionPointRec(GetMousePosition(), msgBox[i]);
        for (int i = 0; i < 4; i++)
            if (MouseOn[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 3)
                    return Init::choose(screenWidth, screenHeight);
                else
                {
                    StopMusicStream(Mus::openMusic);
                    PlayMusicStream(Mus::stageMusics[i]);
                    //std::cerr << "stage play" << " " << GetMusicTimeLength(Mus::stageMusics[i]) << std::endl;
                    return Game::loop(screenWidth, screenHeight, kind, i);
                }
            }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(hint, 10, 10, 40, WHITE);
        for (int i = 0; i < 4; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], msgBox[i].x, msgBox[i].y, 50, MouseOn[i] ? GOLD : WHITE);
        }
        EndDrawing();
    }
    return 0;
}

int Game::loop(int screenWidth, int screenHeight, int kind, int stage)
{
    // Image Bgimage = LoadImage("source/1.png");
    Texture2D Bgtexture = LoadTexture("source/bg-ps.png");

    const int FastSpeed = 500, SlowSpeed = 200;

    PlayerBar *playerHPBar = new PlayerBar(10, screenHeight - 20, 10, 25, MAROON);
    PlayerBar *playerLPBar = new PlayerBar(10, screenHeight - 50, 10, 25, BLUE);
    auto atk = std::make_shared<class Atk>(50);
    BulletManager *playerBullets = new BulletManager();
    BulletManager *enemyBullets = new BulletManager();
    EnemyManager *enemys = new EnemyManager();
    Player *player = new Player(initPlayerPosition, 5, 10, FastSpeed, SlowSpeed, 510, 1000, 2, kind);

    std::queue<std::pair<float, Enemy *>> enemyQueue;

    float time = 0.0;
    float playerLasttime = 0.0;

    const int MAX_STAGE = 3;
    int stagecnt = stage, destroyedEnemy = 0;
    int iskilledmusicplayed = 0;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(Mus::stageMusics[stagecnt]);
        if (iskilledmusicplayed) {
            UpdateMusicStream(Mus::killedMusic);
            if (GetMusicTimePlayed(Mus::killedMusic) >= GetMusicTimeLength(Mus::killedMusic) * 0.9) {
                iskilledmusicplayed = 0;
                StopMusicStream(Mus::killedMusic);
            }
        }
        if (IsKeyPressed(KEY_P))
        {
            PauseMusicStream(Mus::stageMusics[stagecnt]);
            int ret = Pause::loop(screenWidth, screenHeight);
            ResumeMusicStream(Mus::stageMusics[stagecnt]);
            switch (ret)
            {
            case 0: //??????
                return 0;
            case 1: //????????????
            {
                StopMusicStream(Mus::stageMusics[stagecnt]);
                PlayMusicStream(Mus::openMusic);
                return Init::choose(screenWidth, screenHeight);
            }
            case 2: //????????????
            {
                StopMusicStream(Mus::stageMusics[stagecnt]);
                PlayMusicStream(Mus::openMusic);
                return Init::loop(screenWidth, screenHeight);
            }
            default:
                break;
            }
        }

        if (player->getHP() <= 0)
        {
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
        // draw background
        DrawLine(1000, 0, 1000, 900, BLACK);
        {
            int frameWidth = Bgtexture.width;
            int frameHeight = Bgtexture.height;
            //std::cerr << frameHeight << " " << frameWidth << std::endl;
            Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
            Rectangle destRec = { 0.0, 0.0, 1000, 900};
            Vector2 origin = {0, 0};
            DrawTexturePro(Bgtexture, sourceRec, destRec, origin, 0.0, WHITE);
        }

        player->Check(time);
        atk->Check(screenWidth, screenHeight);
        if (IsKeyDown(KEY_Z)) // ?????????
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
                    //bullets[i]->parryed();
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
        if (checkPlayerHit(player, enemyBullets, time)) {
            if (iskilledmusicplayed == 0) {
                std::cerr << "killed" << std::endl;
                iskilledmusicplayed = 1;
                PlayMusicStream(Mus::killedMusic);
            }
        }
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

        DrawText(TextFormat("FPS: %.0lf", 1 / GetFrameTime()), 10, 10, 20, GOLD);

        DrawText(TextFormat("STAGE %d", stagecnt), 1020, 10, 40, BLACK);
        DrawText(TextFormat("enemy destroyed: %d", destroyedEnemy), 1020, 50, 20, BLACK);
        DrawTexture(((player->getcanHit()) ? Img::sr : Img::sr2), 1000, 80, RAYWHITE);

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
    const char Name[3][50] = {"Yuka", "Reimu", "Marisa"};
    const char Skill[3][2][50] = {{{"Summon a unmbrella and it can resist"},
                                   {"the attack from the front, last 5s."}},
                                  {{"Instantly clears surrounding bullets."},
                                   {""}},
                                  {{"Launch a large bullet, it can clears the"},
                                   {"path and deal damage to the first enemy."}}};
    
    
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
        DrawTexture(Img::ky, 550, 150 , RAYWHITE);
        DrawLine(800, 100, 800, 850, BLACK);
        DrawText(msg1, 200, 50, 60, BLACK);
        DrawText(msg2, 900, 50, 60, BLACK);
        DrawText(msg, msgBox.x, msgBox.y, 30, MouseOn ? GOLD : BLACK);
        for (int i = 0; i < 9; i++)
            DrawText(inst[i], 100, 150 + i * 80, 50, BLUE);
        for (int i = 0; i < 3; i++)
        {
            DrawText(Name[i], 900, 150 + 200 * i, 40, ORANGE);
            for (int j = 0; j < 2; j++)
                DrawText(Skill[i][j], 950, 250 + 200 * i + 30 * j, 30, PURPLE);
        }
        DrawTexture(Img::h1, 1200, 150 , RAYWHITE);
        DrawTexture(Img::h2, 1200, 350 , RAYWHITE);
        DrawTexture(Img::h3, 1200, 550 , RAYWHITE);
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
                if (i == 2)
                {
                    StopMusicStream(Mus::endMusic);
                    return 0;
                }
                else if (i == 1)
                {
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::loop(screenWidth, screenHeight);
                }
                else
                {
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
                if (i == 2)
                {
                    StopMusicStream(Mus::endMusic);
                    return 0;
                }
                else if (i == 1)
                {
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::loop(screenWidth, screenHeight);
                }
                else
                {
                    StopMusicStream(Mus::endMusic);
                    PlayMusicStream(Mus::openMusic);
                    return Init::choose(screenWidth, screenHeight);
                }
            }
        BeginDrawing();
        DrawText(allclear, Mid - 40, 200, 80, GOLD);
        for (int i = 0; i < 3; i++)
        {
            // DrawRectangleRec(msgBox[i], LIGHTGRAY);
            DrawText(msg[i], Mid, msgBox[i].y, 60, MouseOn[i] ? RED : BLACK);
        }
        EndDrawing();
    }
    return 0;
}