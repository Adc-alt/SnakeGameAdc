#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include <deque>

using namespace std;

bool ElementInDeque(Vector2 element, deque<Vector2> deque);

class Food
{
    public:
        Vector2 position;
        Texture2D texture;

        // Constructor y destructor
        Food(deque<Vector2> snakeBody);
        ~Food();

        // Métodos de la clase
        void Draw();
        Vector2 GenerateRandomCell();
        Vector2 GenerateRandomPos(deque<Vector2> snakeBody);

};

#endif