#include "spinenemy.h"
#include "Vector2Basic.h"

spinEnemy::spinEnemy(float _hp, float _genTime, float livetime, Vector2 pos, float _r, char* filename, Vector2 vel, float spinrate):
    Enemy(_hp, _genTime, livetime, pos, _r, filename), vel(vel), spinrate(spinrate), lastalpha(0) {}
std::vector<Bullet *> spinEnemy::getBullet(float nowTime, BulletManager *manager, Vector2 playerPosition) {
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (inPeriod(6, 5, dtime) && dtime <= 12) {
        //std::cerr << dtime << std::endl;
        lastalpha += (dtime - dutime) * spinrate;
        FOR_INTERVAL(dutime, dtime, 0.05) {
            for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 4) {
                Vector2 f = {cos(alpha + lastalpha), sin(alpha + lastalpha)};
                Bullet *b = new basicBullet(nowTime, 15, manager, RED, 4, pos + 20 * f, 200 * f);
                ret.push_back(b);
            }
        }
    }
    if (dtime >= 14 && dtime <= 30 && inPeriod(8, 7, dtime - 14)) {
        static int flag = 1;
        FOR_INTERVAL(dutime, dtime, 0.2) {
            float deltaalpha = getrand(0, PI / 8);
            for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 10) {
                float _alpha = alpha + deltaalpha;
                Vector2 f = {cos(_alpha), sin(_alpha)};
                Vector2 f2 = {cos(_alpha + PI / 2 * flag), sin(_alpha + PI / 2 * flag)};
                Bullet *b = new TurningBullet(nowTime, 20, ORANGE, 7, pos + 20 * f,
                150 * f, 60 * f2 + 50 * f, 4);
                ret.push_back(b);
            }
            if (flag == 1) flag = -1;
            else flag = 1;
        }
    }
    dutime = dtime;
    return ret;
}