#include "shotSimpleTraceEnemy.h"
#include "utils.h"
#include "Vector2Basic.h"

shotSimpleTraceEnemy::shotSimpleTraceEnemy(float _hp, float _genTime, float livetime, Vector2 pos, 
        float _r, char* filename, float _fastv, float _slowv) : 
        Enemy(_hp, _genTime, livetime, pos, _r, filename), 
        fastv(_fastv), slowv(_slowv) {
            flag = -1;
        }
std::vector<Bullet *> shotSimpleTraceEnemy::getBullet(float nowTime, 
        BulletManager *manager, Vector2 playerPosition) {
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (inPeriod(3, 0.5, dtime)) {
        if (flag != 1) {
            float alpha = getrand(0, PI * 2);
            f = (Vector2){cos(alpha), sin(alpha)};
            flag = 1;
        }
        //std::cerr << "p1 " << dtime << std::endl;
        FOR_INTERVAL(dutime, dtime, 0.04) {
            Bullet *b = new traceBullet(nowTime, 20, manager, GRAY, 6, pos + (Vector2){0, 30}, 300);
            ret.push_back(b);
        }
        pos = pos + (dtime - dutime) * slowv * f;
    }
    else {
        //std::cerr << "p2 " << dtime << std::endl;
        if (flag != 0) {
            float alpha = getrand(0, PI * 2);
            f = (Vector2){cos(alpha), sin(alpha)};
            flag = 0;
        }
        pos = pos + (dtime - dutime) * fastv * f;
    }
    dutime = dtime;
    return ret;
}