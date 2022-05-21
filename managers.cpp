#include "managers.h"

BulletManager *playerBullets;
BulletManager *enemyBullets;
EnemyManager *enemys;
Player *player;

BulletManager* getPlayerBullets(){return playerBullets;}
BulletManager* getEnemyBullets(){return enemyBullets;}
EnemyManager* getEnemys(){return enemys;}
Player* getPlayer(){return player;}

void initManagers(){
    playerBullets = new BulletManager();
    enemyBullets = new BulletManager();
    enemys = new EnemyManager();
    player = new Player({400, 600}, 10, 5, 10, 300, 2);
}