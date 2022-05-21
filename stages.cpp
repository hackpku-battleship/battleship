#include "stages.h"
#include "simpleenemy.h"
#include "bakaDirect.h"
#include "denemy.h"
#include "Vector2Basic.h"
#include "spinenemy.h"
#include "shotSimpleTraceEnemy.h"

const int screenWidth = 1600 - 600;
const int screenHeight = 900;

void Stage1(float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    {
        Enemy * e = new DEnemy(50, nowtime + 0, 10, (Vector2){500, 50}, 50, "source/lion.png");
        queue.push(std::make_pair(nowtime + 0, e));
    }
    char baka[20] = "source/baka.png";
    const int BakaCnt = 5;
    Vector2 Bakapos[BakaCnt] = {{500, 100}, {100, 100}, {800, 150}, {200, 400}, {900, 450}};
    float Bakavel[BakaCnt] = {20, 15, 30, 19, 9};
    float Bakaalpha[BakaCnt] = {PI / 2, PI * 3 / 4, PI * 3 / 2, PI, PI * 7 / 4};
    float Bakatime[BakaCnt] = {1, 4, 4, 8, 8};
    float BakaDutime = 5;

    queue.push(std::make_pair(0, new SimpleEnemy(114514, nowtime, 1919810, {114,514}, 50, "source/fish1.png")));

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
        Enemy *e = new shotSimpleTraceEnemy(100, nowtime + etime[i], 30, epos[i], 40, devil, 40, 10);
        queue.push(std::make_pair(nowtime + etime[i], e));
    }
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
    default:
        break;
    }
}