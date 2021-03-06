#include "utils.h"
#include "math.h"

float getrand(float l, float r) {
    if (l > r) return 0;
    return 1.0 * rand() / RAND_MAX * (r - l) + l;
}

int getInterval(float l, float r, float interval) {
    return (int)(r / interval) - (int)(l / interval);
}

bool inPeriod(float interval, float mid, float dtime) {
    int cnt = dtime / interval;
    return dtime <= mid || 
        (dtime <= interval * cnt + mid && dtime >= interval * cnt);
}