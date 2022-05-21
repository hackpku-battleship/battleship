#ifndef INIT_H
#define INIT_H

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

namespace Mus {
extern Music openMusic;
extern Music stageMusics[4];
extern Music endMusic;
extern Music killedMusic;
};

namespace Img {
    extern Texture2D t1, t2, t3, h1, h2, h3, ky;
    void Init();
    void Release();
}
#endif