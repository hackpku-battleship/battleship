#include "Vector2Basic.h"

Vector2 operator +(Vector2 a, Vector2 b){return {a.x+b.x, a.y+b.y};}
Vector2 operator *(float a, Vector2 b){return {a*b.x, a*b.y};}