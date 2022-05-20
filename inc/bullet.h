#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

class Bullet{
    float genTime; // 子弹的生成时间
public:
    Bullet(float);
    float updateTime(float);
    void Draw();
    bool checkBox();
};

class basicBullet: Bullet{
    Vector2 position, velocity;
public:
    basicBullet(float, Vector2, Vector2);
    float updateTime(float);
    void Draw();
    bool checkBox();
}; 
#endif