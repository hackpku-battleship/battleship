#include "enemy.h"
#include "Vector2Basic.h"
#include <iostream>

SimpleEnemy::SimpleEnemy(float _hp, float _gentime, float _livetime, float _x, float _y, float _r):
    Enemy(_hp, _gentime, _livetime, _x, _y, _r) {}

std::vector<Bullet*> SimpleEnemy::getBullet(float nowTime) {
    float dtime = nowTime - gentime;
    std::vector<Bullet*> ret;
    //std::cerr << (int)dtime << " " << (int)dutime << std::endl;
    if ((int)dtime * 2 - (int)dutime * 2>= 1) {
        //std::cerr << "ret" << std::endl;
        //float dx = 1.0, dy = 0.0;
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 16) {
            Vector2 f = {cos(alpha), sin(alpha)};
            Bullet *b = new basicBullet(nowTime, 100.0, (Vector2){x, y} + 10.0f * f, 50.0f * f);
            ret.push_back(b);
        }
        for (int i = 0; i <= 40; i++) {
            float alpha = 1.0 * rand() / RAND_MAX * PI * 2;
            Vector2 f = {cos(alpha), sin(alpha)};
            Bullet *b = new basicBullet(nowTime, 100.0, (Vector2){x, y} + 10.0f * f, 30.0f * f);
            ret.push_back(b);
        }
    }
    dutime = dtime;
    return ret;
}

void SimpleEnemy::draw() {
    DrawCircleV((Vector2){x, y}, r, BLUE);
}