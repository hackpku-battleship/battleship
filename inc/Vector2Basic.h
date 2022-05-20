#ifndef VECTOR2_BASIC_H
#define VECTOR2_BASIC_H

#include "raylib.h"

Vector2 operator +(Vector2 a, Vector2 b);//{return {a.x+b.x, a.y+b.y};}
Vector2 operator *(float a, Vector2 b);//{return {a*b.x, a*b.y};}
#endif