#ifndef BULLET_H
#define BULLET_H

class Bullet{
    double genTime; // 子弹的生成时间
public:
    Bullet();
    double Draw(double); // 传入时间，将子弹显示在屏幕上
    bool checkBox();
};

class basicBullet: Bullet{
public:
    basicBullet();
    double Draw(double);
    bool checkBox();
};

#endif