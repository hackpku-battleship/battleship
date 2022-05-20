#ifndef BULLET_H
#define BULLET_H
class Bullet{
    float genTime; // 子弹的生成时间
public:
    Bullet();
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