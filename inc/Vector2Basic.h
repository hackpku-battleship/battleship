#ifndef VECTOR2_BASIC_H
#define VECTOR2_BASIC_H

#include "raylib.h"
#include <cmath>

float norm(Vector2 a);
int sqrNorm(Vector2 a);
Vector2 operator +(Vector2 a, Vector2 b);
Vector2 operator -(Vector2 a, Vector2 b);
float operator *(Vector2 a, Vector2 b);
float operator %(Vector2 a, Vector2 b);
Vector2 rotate(Vector2 a, float b);
Vector2 operator *(float a, Vector2 b);
Vector2 normalize(Vector2 vec);
#endif