#ifndef INIT_H
#define INIT_H

class Init {
public:
    static int loop(int, int);
    static int choose(int, int);
};

class Game {
public:
    static int loop(int, int, int);
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
#endif