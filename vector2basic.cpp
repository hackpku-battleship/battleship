#include "vector2Basic.h"

float norm(Vector2 a){
    return sqrt(a.x*a.x+a.y*a.y);
}
int sqrNorm(Vector2 a){
    return a.x*a.x+a.y*a.y;
}
Vector2 operator +(Vector2 a, Vector2 b){return {a.x+b.x, a.y+b.y};}
Vector2 operator -(Vector2 a, Vector2 b){return {a.x-b.x, a.y-b.y};}
float operator *(Vector2 a, Vector2 b){return a.x*b.x+a.y*b.y;}
float operator %(Vector2 a, Vector2 b){return a.x*b.y-a.y*b.x;}
Vector2 operator *(float a, Vector2 b){return {a*b.x, a*b.y};}

Vector2 rotate(Vector2 a, float b){
    float cosb=cos(b), sinb=sin(b);
    return {
        float(cosb*a.x-sinb*a.y),
        float(sinb*a.x+cosb*a.y)
    };
}

Vector2 normalize(Vector2 vec) {
    float nm = 1.0 / norm(vec);
    return nm * vec;
}