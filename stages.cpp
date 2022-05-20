#include "stages.h"
#include "bakaDirect.h"
#include "denemy.h"

const int screenWidth = 1600 - 600;
const int screenHeight = 900;

void Stage1(float nowtime, std::queue<std::pair<float, Enemy*> > &queue) {
    char baka[20] = "source/baka.png";
    const int BakaCnt = 5;
    Vector2 Bakapos[BakaCnt] = {{500, 100}, {100, 100}, {800, 150}, {200, 400}, {900, 450}};
    float Bakatime[BakaCnt] = {1, 4, 4, 10, 15};
    float BakaDutime = 5;
    for (int i = 0; i < BakaCnt; i++) {
        Enemy * e = new bakaDirect(50, nowtime + Bakatime[i], BakaDutime, 
            Bakapos[i], 40, baka);
        queue.push(std::make_pair(nowtime + Bakatime[i], e));
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