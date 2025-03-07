#ifndef SNAKE_H
#define SNAKE_H

#include <raylib.h>
#include <deque>

using namespace std;

class Snake {
public:
    deque<Vector2> body;
    Vector2 direction;
    bool addSegment;

    Snake();
    void DrawSnake();
    void Update();
    void Reset();
};

#endif 