#include "raylib.h"
#include "bullet.h"

class Bullet{
    float genTime; // 子弹的生成时间
public:
    Bullet(float nowTime){
        genTime = nowTime;
    }
    float updateTime(float nowTime){
        float delta=nowTime-genTime;
        genTime=nowTime;
        return delta;
    }
    virtual void Draw();
    virtual bool checkBox();
};