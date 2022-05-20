#include "denemy.h"
#include "bullet.h"

DEnemy::DEnemy(float _hp, float _genTime, float _livetime, float _x, float _y, float _r) :
    Enemy(_hp, _genTime, _livetime, _x, _y, _r) {}
std::vector<Bullet*> DEnemy::getBullet(float nowTime) {
    std::vector<Bullet*> ret;
    float dtime = nowTime - gentime;
    if ((int)(dtime * 4) - (int)(dutime * 4) >= 1) {
        //std::cerr << dtime << " " << dutime << std::endl;
        for (int i = -4; i <= 4; i++) {
            Bullet *b = new basicBullet(nowTime, 15, (Vector2){x + i * 50, y + 30}, (Vector2){0, 50});
            ret.push_back(b);
            b = new accBullet(nowTime, 15, (Vector2){x + i * 50, y + 30}, (Vector2){i * 5, 10}, (Vector2){(float)i * 5, 40});
            ret.push_back(b);
        }
        //std::cerr << ret.size() << std::endl;
    }
    dutime = dtime;
    return ret;
}
void DEnemy::draw() {
    DrawCircleV((Vector2){x, y}, r, PURPLE);
}