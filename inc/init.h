#ifndef INIT_H
#define INIT_H
#include <vector>
#include <string>
#include "raylib.h"
class Init {
public:
    static int loop(int, int);
    static int choose(int, int);
    static int choose_stage(int, int, int);
};

class Game {
public:
    static int loop(int, int, int, int);
};

class Inst {
public:
    static int loop(int, int);
};

class Pause {
public:
    static int loop(int, int);
};

class Over {
public:
    static int loop(int, int);
};

class Win{
public:
    static int loop(int, int);
};

class Gif {
    std::vector<Texture2D> src;
    int W, H, currentframe, totalframe; 
public:
    Gif(int _W, int _H, int _totalframe);
    void Load(std::string path);
    void Draw(int X, int Y);
};

#endif