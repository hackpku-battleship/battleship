#include "denemy.h"
#include "bullet.h"
#include "Vector2Basic.h"

DEnemy::DEnemy(float _hp, float _genTime, float _livetime, Vector2 pos, float _r, char* filename) :
 Enemy(_hp, _genTime, _livetime, pos, _r, filename) {}
std::vector<Bullet *> DEnemy::getBullet(float nowTime, BulletManager *manager, Vector2 playerPosition)
{
    std::vector<Bullet *> ret;
    float dtime = nowTime - gentime;
    if (inPeriod(3, 2, dtime)) {
        FOR_INTERVAL(dutime, dtime, 1) {
            //Bullet *b = new traceBullet(nowTime, 20, manager, RED, 6, pos + (Vector2){0, 40}, 4);
            for (float alpha = 0; alpha < PI * 2; alpha += PI / 8) {
                Vector2 df = {cos(alpha), sin(alpha)};
                Bullet *b = new turningTraceBullet(nowTime, 20, manager, RED, 6, pos + 20 * df, 
                100 * df, 500, 2);
                ret.push_back(b);
            }
        }
    }
    /*
    FOR_INTERVAL(dutime, dtime, 0.4) {
        //std::cerr << dtime << " " << dutime << std::endl;
        for (int i = -4; i <= 4; i++) {
            Bullet *b = new basicBullet(nowTime, 15, manager, PINK, 2, (Vector2){pos.x + i * 50, pos.y + 30}, (Vector2){0, 50});
            ret.push_back(b);
            b = new accBullet(nowTime, 15, manager, PINK, 2, (Vector2){pos.x + i * 50, pos.y + 30}, (Vector2){i * 5, 10}, (Vector2){(float)i * 5, 120});
            ret.push_back(b);
        }
    }
    FOR_INTERVAL(dutime, dtime, 2) {
        Bullet *b = new fishBullet(nowTime, 5, manager, PURPLE, 10, (Vector2){pos.x, pos.y + 50}, 300, 0.02);
        ret.push_back(b);
    }
    //*/
    /*
    FOR_INTERVAL(dutime, dtime, 0.2) {
        float alpha = 0.0;
        static int f = 1;
        for (alpha = 0.0; alpha <= PI * 2; alpha += PI / 16) {
            float talpha = alpha + PI / 2 * f;
            Vector2 f1 = {cos(alpha), sin(alpha)};
            Vector2 f2 = {cos(talpha), sin(talpha)};
            Bullet *b = new TurningBullet(nowTime, 15, (Vector2){x, y} + f1, 150.0 * f1, 70 * f2, 2 + getrand(0, 5)
                );
            ret.push_back(b);
        }
        if (f == 1) f = -1;
        else f = 1;
        //std::cerr << ret.size() << std::endl;
    }
    //*/
    /*
    FOR_INTERVAL(dutime, dtime, 2) {
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 8) {
            float randtime = getrand(0, 1.5);
            for (float beta = 0.0; beta <= PI * 2; beta += PI / 8) {
                Vector2 f1 = {cos(alpha), sin(alpha)};
                Vector2 f2 = {cos(beta), sin(beta)};
                Bullet *b = new TurningBullet(nowTime, 10, manager, GREEN, 4, pos + f1, 300 * f1, 50 * f2, 1 + randtime);
                ret.push_back(b);
            }
        }
    }
    //*/
    /*
    FOR_INTERVAL(dutime, dtime, 2) {
        for (float alpha = 0.0; alpha <= PI * 2; alpha += PI / 8) {
            //float randtime = getrand(0, 1.5);
            for (float beta = 0.0; beta <= PI * 2; beta += PI / 16) {
                Vector2 f1 = {cos(alpha), sin(alpha)};
                Vector2 f2 = {cos(beta), sin(beta)};
                Bullet *b = new TurningBullet(nowTime, 10, (Vector2){x,y} + f1, 300 * f1, 50 * f2, 1 + getrand(0, 1.5));
                ret.push_back(b);
            }
        }
    }
    //*/
    dutime = dtime;
    return ret;
}