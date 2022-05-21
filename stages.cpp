#include "stages.h"
#include "simpleenemy.h"
#include "bakaDirect.h"
#include "denemy.h"
#include "Vector2Basic.h"
#include "spinenemy.h"
#include "shotSimpleTraceEnemy.h"
#include "stage2Enemy.h"
#include "predictenemy.h"
#include "easyenemy.h"

const int screenWidth = 1600 - 600;
const int screenHeight = 900;

void Stage1(float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    /*
    {
        Enemy * e = new DEnemy(50, nowtime + 0, 10, (Vector2){500, 50}, 50, "source/lion.png");
        queue.push(std::make_pair(nowtime + 0, e));
    }
    //*/
    char baka[20] = "source/baka.png";
    const int BakaCnt = 5;
    Vector2 Bakapos[BakaCnt] = {{500, 100}, {100, 100}, {800, 150}, {200, 400}, {900, 450}};
    float Bakavel[BakaCnt] = {20, 15, 30, 19, 9};
    float Bakaalpha[BakaCnt] = {PI / 2, PI * 3 / 4, PI * 3 / 2, PI, PI * 7 / 4};
    float Bakatime[BakaCnt] = {1, 4, 4, 8, 8};
    float BakaDutime = 5;

    //queue.push(std::make_pair(0, new SimpleEnemy(114514, nowtime, 1919810, {114,514}, 50, "source/fish1.png")));

    for (int i = 0; i < BakaCnt; i++) {
        Vector2 f = {cos(Bakaalpha[i]), sin(Bakaalpha[i])};
        Enemy * e = new bakaDirect(50, nowtime + Bakatime[i], BakaDutime, 
            Bakapos[i], 40, baka, Bakavel[i] * f);
        queue.push(std::make_pair(nowtime + Bakatime[i], e));
    }

    {
        const int STIME = 15;
        Enemy *e = new spinEnemy(200, nowtime + STIME, 30, (Vector2){500, 50}, 50, "source/zhuanzhuan.png", 
            (Vector2){0, 0}, 1);
        queue.push(std::make_pair(nowtime + STIME, e));
    }
    return;
}

void Stage2(float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    const int senmy = 6;
    Vector2 epos[senmy] = {{200, 200}, {800, 200}, {300, 300}, {700, 300}, {500, 100}, {500, 500}};
    float etime[senmy] = {1, 1, 5, 5, 8, 8};
    float dutime = 15;
    char devil[] = "source/devil.png";
    for (int i = 0; i < senmy; i++) {
        Enemy *e = new shotSimpleTraceEnemy(100, nowtime + etime[i], 10, epos[i], 40, devil, 40, 10);
        queue.push(std::make_pair(nowtime + etime[i], e));
    }
    queue.push(std::make_pair(15 + nowtime, new stage2Enemy(100, nowtime + 15, 25, {500,50}, 50, "source/tiger.png")));
    return;
}

void Stage3(float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    {
        const int easye = 5;
        Vector2 easypos[easye] = {{500, 100}, {300, 150}, {700, 150}, {100, 200}, {900, 200}};
        float easytime[easye] = {0.5, 1, 1, 2, 2};
        float easydutime = 20;
        for (int i = 0; i < easye; i++) {
            Enemy *e = new EasyEnemy(20, nowtime+ easytime[i], easydutime, easypos[i], 50, "source/fish0.png");
            queue.push(std::make_pair(nowtime + easytime[i], e));
        }
    }
    {
        const int prede = 3;
        Vector2 predpos[prede] = {{500, 100}, {350, 200}, {650, 200}};
        float predtime[prede] = {23, 23.7, 24.5};
        float predlive = 1000;
        for (int i = 0; i < 3; i++) {
            Enemy *e = new PredictEnemy(1000, nowtime + predtime[i], predlive, predpos[i], 50, "source/fish0.png");
            queue.push(std::make_pair(nowtime + predtime[i], e));
        }
    }
    
    queue.push(std::make_pair(nowtime + 50, new SimpleEnemy(5000, nowtime, nowtime + 1145141919, (Vector2){500, 50}, 50, "source/jellyfish.png")));
    return;
}

void getStage(int stageid, float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    switch (stageid)
    {
    case 1:
        Stage1(nowtime, queue);
        break;
    case 2:
        Stage2(nowtime, queue);
        break;
    case 3:
        Stage3(nowtime, queue);
        break;
    default:
        break;
    }
}