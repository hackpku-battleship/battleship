#ifndef STAGES_H
#define STAGES_H

#include <queue>
#include <algorithm>
#include "enemy.h"

void getStage(int stageid, float nowtime, std::queue<std::pair<float, Enemy*> > &queue);
#endif