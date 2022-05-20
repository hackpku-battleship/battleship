#include "enemy.h"
#include "Vector2Basic.h"
#include <iostream>

SimpleEnemy::SimpleEnemy(float _hp, float _gentime, float _livetime, float _x, float _y, float _r):
    Enemy(_hp, _gentime, _livetime, _x, _y, _r), rotatep(0.0) {}

std::vector<Bullet*> SimpleEnemy::getBullet(float nowTime) {
    float dtime = nowTime - gentime;
    std::vector<Bullet*> ret;
    //std::cerr << (int)dtime << " " << (int)dutime << std::endl;
    if ((int)dtime - (int)dutime >= 1) {
        ret.push_back(new fishBullet(nowTime, 30.0, (Vector2){x,y}, 300, 0.02));
    }
    if ((int)dtime * 2 - (int)dutime * 2>= 1) {
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 16) {
            Vector2 f = {cos(alpha + rotatep), sin(alpha + rotatep)};
            Bullet *b = new basicBullet(nowTime, 15.0, (Vector2){x, y} + 10.0f * f, 50.0f * f);
            ret.push_back(b);
        }
    }
    if ((int)(dtime * 0.8) - (int)(dutime * 0.8) >= 1) {
        for (int i = 0; i <= 20; i++) {
            float alpha = 1.0 * rand() / RAND_MAX * PI * 2;
            Vector2 f = {cos(alpha), sin(alpha)};
            float speed = 1.0 * rand() / RAND_MAX * 90 + 100;
            Bullet *b = new basicBullet(nowTime, 5.0, (Vector2){x, y} + 10.0f * f, speed * f);
            ret.push_back(b);
        }
        //std::cerr << dutime << " " << livetime << std::endl;
    }
    /*
    if ((int)(dtime * 10) - (int)(dutime * 10) >= 1) {
        x += (1.0 * rand() / RAND_MAX - 0.5)* 10;
        y += (1.0 * rand() / RAND_MAX - 0.5)* 10;
    }
    //*/
    dutime = dtime;
    return ret;
}

void SimpleEnemy::draw() {
    DrawCircleV((Vector2){x, y}, r, BLUE);
}