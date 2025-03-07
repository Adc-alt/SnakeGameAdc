#include "../include/Food.h"
#include <raymath.h>
#include <stdio.h>

extern int cellSize;
extern int cellCount;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}

Food::Food(deque<Vector2> snakeBody)
{
    Image image = LoadImage("assets/apple.png");
    if (image.data == nullptr) {
        printf("Error: Could not load apple.png\n");
    } else {
        ImageResize(&image, cellSize, cellSize);
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell()
{
    float x = GetRandomValue(0, cellCount-1);
    float y = GetRandomValue(0, cellCount-1);
    return Vector2{x,y};
}

Vector2 Food::GenerateRandomPos(deque<Vector2> snakeBody)
{
    Vector2 position = GenerateRandomCell();
    while (ElementInDeque(position, snakeBody))
    {
        position = GenerateRandomCell();
    }
    return position;
}