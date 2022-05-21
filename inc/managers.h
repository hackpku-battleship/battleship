#ifndef MANAGERS_H
#define MANAGERS_H

#include "bulletManager.h"
#include "enemy.h"
#include "player.h"

BulletManager* getPlayerBullets();
BulletManager* getEnemyBullets();
EnemyManager* getEnemys();
Player* getPlayer();
void initManagers();

#endif