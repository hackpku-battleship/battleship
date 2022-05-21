#include "spinenemy.h"
#include "Vector2Basic.h"

spinEnemy::spinEnemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename, Vector2 vel, float spinrate):
    Enemy(_hp, _genTime, livetime, pos, _r, filename), vel(vel), spinrate(spinrate), lastalpha(0) {}
std::vector<Bullet *> spinEnemy::getBullet(float nowTime, BulletManager *manager) {
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (inPeriod(6, 5.5, dtime)) {
        //std::cerr << dtime << std::endl;
        lastalpha += (dtime - dutime) * spinrate;
        FOR_INTERVAL(dutime, dtime, 0.05) {
            for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 4) {
                Vector2 f = {cos(alpha + lastalpha), sin(alpha + lastalpha)};
                Bullet *b = new basicBullet(nowTime, 15, RED, 4, pos + 20 * f, 200 * f);
                ret.push_back(b);
            }
        }
    }
    dutime = dtime;
    return ret;
}