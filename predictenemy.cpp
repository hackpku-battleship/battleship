#include "enemy.h"
#include "predictenemy.h"
#include "basicBullet.h"
#include "splitBullet.h"
#include "accBullet.h"
#include "Vector2Basic.h"
#include <iostream>

PredictEnemy::PredictEnemy(float hp, float gentime, float livetime, Vector2 pos, float r, char *filename) : Enemy(hp, gentime, livetime, pos, r, filename)
{
    predictLastTime = stateLastTime = accLastTime = gentime;
    state = rand() % 4 + 1;
}

std::vector<Bullet *> PredictEnemy::getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition)
{
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (state == 1 && nowTime - stateLastTime >= 2)
    {
        if (int(dtime * 0.4) - int(dutime * 0.4) >= 1)
        {
            Bullet *b = new fishBullet(nowTime, 20, creater, PURPLE, 15, pos, 200, PI / 2);
            ret.push_back(b);
        }
        if (int(dtime * 0.2) - int(dutime * 0.2) >= 1)
        {

            for (float _ang = 0; _ang <= PI; _ang += PI / 6)
            {
                std::vector<Bullet *> bullets;
                for (float ang = 0; ang <= 2 * PI; ang += PI / 16)
                {
                    Vector2 f = {cos(ang), sin(ang)};
                    Bullet *b = new accBullet(nowTime, 10, creater, RED, 5, {0, 0}, {0, 0}, {200 * f.x, 200 * f.y});
                    bullets.push_back(b);
                }
                ret.push_back(new splitBullet(nowTime, rand() % 10, creater, GREEN, 15, pos, {80 * cos(_ang), 80 * sin(_ang)}, bullets));
            }
        }
        if (int(dtime * 2) - int(dutime * 2) >= 1)
        {
            Vector2 dir = {playerPosition.x - playerLastPosition.x, playerPosition.y - playerLastPosition.y};
            Vector2 velocity = {dir.x / (nowTime - predictLastTime), dir.y / (nowTime - predictLastTime)};
            float time = sqrt((pos.x - playerPosition.x) * (pos.x - playerPosition.x) + (pos.y - playerPosition.y) * (pos.y - playerPosition.y)) / 800;
            Vector2 predict = {playerPosition.x + time * velocity.x, playerPosition.y + time * velocity.y};
            float ang = atan2(predict.y - pos.y, predict.x - pos.x);
            Vector2 f = {cos(ang), sin(ang)};
            Bullet *b = new basicBullet(nowTime, 15, creater, BLUE, 15, pos, {800 * f.x, 800 * f.y});
            ret.push_back(b);
        }
    }
    else if (state == 2 && nowTime - stateLastTime >= 2)
    {
        if (int(dtime * 2) - int(dutime * 2) >= 1)
        {
            for (float x = 0; x <= 1000; x += (rand() & 1 ? 40 : 80))
            {
                ret.push_back(new basicBullet(nowTime, 30, creater, RED, 10, {x, pos.y}, {0, 800}));
            }
        }
    }
    else if (state == 3 && nowTime - stateLastTime >= 2)
    {
        if (int(dtime * 4) - int(dutime * 4) >= 1)
        {
            Vector2 pos;
            do
                pos = {float(rand() % 1000),
                       float(rand() % 900)};
            while (-200 <= pos.x - playerPosition.x && pos.x - playerPosition.x <= 200 && -200 <= pos.y - playerPosition.y && pos.y - playerPosition.y <= 200);
            ret.push_back(new fishBullet(nowTime, 5, creater, ORANGE, 15, pos, 200, PI / 2));
        }
    }
    else if (state == 4 && nowTime - stateLastTime >= 2)
    {

        if (nowTime - accLastTime >= 0.5 - 0.01 * accCount)
        {
            for (float ang = 0; ang <= PI * 2; ang += PI / 16)
            {
                float _ang = ang + (PI / 64) * (accCount % 4);
                Vector2 f = {cos(_ang), sin(_ang)};
                Bullet *b = new accBullet(nowTime, 15, creater, PURPLE, 30, pos, {100 * f.x, 100 * f.y}, {200 * f.x, 200 * f.y});
                ret.push_back(b);
            }
            accCount++;
            accLastTime = nowTime;
        }
    }
    if (nowTime - stateLastTime >= stateLengths[state])
    {
        accCount = 0;
        int new_state;
        do
            new_state = rand() % 4 + 1;
        while (state == new_state);
        state = new_state;
        stateLastTime = nowTime;
    }
    if (int(dtime * 10) - int(dutime * 10) >= 1)
    {
        playerLastPosition = playerPosition;
        predictLastTime = nowTime;
    }
    dutime = dtime;
    return ret;
}