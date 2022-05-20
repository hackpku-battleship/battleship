#include "raylib.h"
#include "bullet.h"

class Bullet{
    double genTime; // 子弹的生成时间
public:
    Bullet(){
        genTime = getTime();
    }
    virtual double Draw(double time);
    virtual bool checkBox();
};