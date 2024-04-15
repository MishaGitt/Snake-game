#ifndef MYSNAKE_SNAKE_H
#define MYSNAKE_SNAKE_H

#include "globalScope.h"

using namespace std;

class Snake {
public:
    // Member variables
    Sound gameOver = LoadSound("SFX\\gameOver.mp3");
    deque<Vector2> body;
    Vector2 direction;
    int score;
    char scoreBuffer[1];

    void draw();
    void controls();
    void updateBody();
    void checkCollision();
    void unloadMembers();
};

#endif //MYSNAKE_SNAKE_H