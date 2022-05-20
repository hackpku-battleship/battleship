#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "raylib.h"
#include "bullet.h"
#include <bits/stdc++.h>

struct BulletManager{
    std::vector<Bullet*>bullets;
    void addBullet(Bullet*x){bullets.push_back(x);}
    void updateTime(double nowTime, int Height, int Weight, Vector2 playerPosition){
        for(int i=0;i<bullets.size();++i){
            if(!bullets[i]->inScreen(Height, Weight) || !bullets[i]->checkAlive(nowTime)){
                delete bullets[i];
                bullets.erase(bullets.begin()+i);
                --i;
            }else bullets[i]->updateTime(nowTime, playerPosition);
        }
    }
    void DrawAllBullets(){
        for(Bullet*p:bullets){
            p->Draw();
        }
    }
    bool checkBox(Vector2 x, double r){
        for(Bullet*p:bullets)
            if(p->checkBox(x,r))return true;
        return false;
    }
    std::vector<Bullet*> getBullets() {
        return bullets;
    }
    void setBullets(std::vector<Bullet*> v) {
        bullets=v;
    }
};

#endif