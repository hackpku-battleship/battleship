#ifndef UTILS_H
#define UTILS_H

#define FOR_INTERVAL(l, r, interval) for (int __itv = 0, __interval = getInterval(l, r, interval); __itv < __interval; __itv++)

float getrand(float l, float r);
int getInterval(float l, float r, float interval);

#endif