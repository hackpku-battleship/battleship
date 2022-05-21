#include "enemy.h"
#include "simpleenemy.h"
#include "Vector2Basic.h"
#include <iostream>

SimpleEnemy::SimpleEnemy(float _hp, float _gentime, float _livetime, Vector2 pos, float _r, char *filename) : Enemy(_hp, _gentime, _livetime, pos, _r, filename), rotatep(0.0) {}
std::vector<Bullet *> SimpleEnemy::getBullet(float nowTime, BulletManager *creater, Vector2 playerPosition){
    float dtime = nowTime - gentime;
    std::vector<Bullet *> ret;
    if ((int)(dtime / 5) - (int)(dutime / 5) >= 1)
    {
        static bool current = true; 
        if(current){
            Vector2 startPosition = {rand()%1000,80}, direction = playerPosition - startPosition;
            ret.push_back(new soccerBullet(nowTime, 2.5, creater, BLANK, 80, startPosition , 2.0, startPosition + (2000.f / norm(direction)) * direction, "source/soccer80.png"));
            Vector2 startD = {-90, 820}, endD = {1090, 820};
            if(playerPosition.x < 500)std::swap(startD, endD);
            ret.push_back(new soccerBullet(nowTime, 2.0, creater, BLANK, 80, startD , 1.5, endD, "source/soccer80.png"));
        }else{
            int t0=rand()%2;
            int t=rand()%4;
            if(t0){
                if(t!=0) ret.push_back(new soccerBullet(nowTime, 1.5, creater, BLANK, 95, {200,80}, 1, {200, 920}, "source/soccer80.png"));
                if(t!=1) ret.push_back(new soccerBullet(nowTime, 1.5, creater, BLANK, 95, {400,80}, 1, {400, 920}, "source/soccer80.png"));
                if(t!=2) ret.push_back(new soccerBullet(nowTime, 1.5, creater, BLANK, 95, {600,80}, 1, {600, 920}, "source/soccer80.png"));
                if(t!=3) ret.push_back(new soccerBullet(nowTime, 1.5, creater, BLANK, 95, {800,80}, 1, {800, 920}, "source/soccer80.png"));
            }else{
                ret.push_back(new soccerBullet(nowTime, 1.5, creater, BLANK, 95, {200,80}, 1.0, {200, 920}, "source/soccer80.png"));
                ret.push_back(new soccerBullet(nowTime, 2.0, creater, BLANK, 95, {400,80}, 1.5, {400, 920}, "source/soccer80.png"));
                ret.push_back(new soccerBullet(nowTime, 2.5, creater, BLANK, 95, {600,80}, 2.0, {600, 920}, "source/soccer80.png"));
                ret.push_back(new soccerBullet(nowTime, 3.0, creater, BLANK, 95, {800,80}, 2.5, {800, 920}, "source/soccer80.png"));
            }
        }
        current^=1;
    }
    if ((int)(dtime * 0.1) - (int)(dutime * 0.1) >= 1)
    {
        ret.push_back(new eldenBullet(nowTime, 15.0, creater, Fade(YELLOW, 0.3), 30, pos, 80, 2, 0.5, playerPosition - pos));
        ret.push_back(new eldenBullet(nowTime, 12.0, creater, Fade(YELLOW, 0.3), 30, pos, 80, 1, 0.5, rotate(playerPosition - pos, (rand()%2 ? 1 : -1) * PI/2)));
    }
    /*
    if (int(dtime * 0.5) - int(dutime * 0.5) >= 1)
    {
        std::vector<Bullet *> bullets;
        for (float alpha = PI / 4; alpha <= PI * 2; alpha += PI / 2)
        {
            Vector2 f = {cos(alpha), sin(alpha)};
            Bullet *b = new fishBullet(nowTime, 2.0, creater, PURPLE, 8, {10 * f.x, 10 * f.y}, 100, alpha / 2, playerPosition - Vector2{10 * f.x, 10 * f.y}, true);
            bullets.push_back(b);
        }
        ret.push_back(new splitBullet(nowTime, 3.0, creater, ORANGE, 10, pos, {0, 50}, bullets));
    }*/
    if ((int)dtime * 2 - (int)dutime * 2 >= 1)
    {
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 16)
        {
            Vector2 f = {cos(alpha + rotatep), sin(alpha + rotatep)};
            Bullet *b = new basicBullet(nowTime, 15.0, creater, ORANGE, 5, pos + 10.0f * f, 80.0f * f);
            ret.push_back(b);
        }
    }
    if ((int)(dtime * 0.8) - (int)(dutime * 0.8) >= 1)
    {
        for (int i = 0; i <= 20; i++)
        {
            float alpha = 1.0 * rand() / RAND_MAX * PI * 2;
            Vector2 f = {cos(alpha), sin(alpha)};
            float speed = 1.0 * rand() / RAND_MAX * 90 + 100;
            Bullet *b = new basicBullet(nowTime, 20.0, creater, ORANGE, 5, pos + 10.0f * f, speed * f);
            ret.push_back(b);
        }
        // std::cerr << dutime << " " << livetime << std::endl;
    }
    dutime = dtime;
    return ret;
}
