#include "stages.h"
#include "bakaDirect.h"
#include "denemy.h"
#include "Vector2Basic.h"
#include "spinenemy.h"

const int screenWidth = 1600 - 600;
const int screenHeight = 900;

void Stage1(float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    char baka[20] = "source/baka.png";
    const int BakaCnt = 5;
    Vector2 Bakapos[BakaCnt] = {{500, 100}, {100, 100}, {800, 150}, {200, 400}, {900, 450}};
    float Bakavel[BakaCnt] = {20, 15, 30, 19, 9};
    float Bakaalpha[BakaCnt] = {PI / 2, PI * 3 / 4, PI * 3 / 2, PI, PI * 7 / 4};
    float Bakatime[BakaCnt] = {1, 4, 4, 8, 8};
    float BakaDutime = 5;
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
}

void getStage(int stageid, float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    switch (stageid)
    {
    case 1:
        Stage1(nowtime, queue);
        break;
    
    default:
        break;
    }
}