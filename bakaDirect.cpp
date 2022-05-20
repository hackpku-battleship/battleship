#include "bakaDirect.h"
#include "Vector2Basic.h"

bakaDirect::bakaDirect(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename):
        Enemy(_hp, _genTime, livetime, pos, _r,filename) {}

std::vector<Bullet *> bakaDirect::getBullet(float nowTime, BulletManager *manager) {
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (dtime <= 4) {
        FOR_INTERVAL(dutime, dtime, 0.5) {
            for (float alpha = 0.0; alpha <= PI * 2; alpha+= PI / 8) {
                Vector2 f1 = {cos(alpha), sin(alpha)};
                Bullet *b = new basicBullet(nowTime, 10, BLUE, 10, pos + 20 * f1, 100 * f1);
                ret.push_back(b);
            }
        }
    }
    dutime = dtime;
    return ret;
}