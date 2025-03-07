#include "../include/Snake.h"
#include <raymath.h>

extern int cellSize;
extern Color darkGreen;

Snake::Snake() {
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {1,0};
    addSegment = false;
}

void Snake::DrawSnake() {
    for (unsigned i = 0; i < body.size(); i++) {
        float x = body[i].x;
        float y = body[i].y;
        
        if (i == 0) {
            // Cabeza redondeada en forma de flecha
            Rectangle head = Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(head, 0.5, 6, Color{35, 92, 49, 255});
            
            // Punta de flecha (triángulo pequeño)
            Vector2 headCenter = {x * cellSize + cellSize/2, y * cellSize + cellSize/2};
            float rotation = 0.0f;
            
            if (direction.x == 1) rotation = 0.0f;
            else if (direction.x == -1) rotation = 180.0f;
            else if (direction.y == -1) rotation = -90.0f;
            else if (direction.y == 1) rotation = 90.0f;

            // Triángulo más pequeño para la punta
            Vector2 v1 = {headCenter.x + cellSize/3, headCenter.y};
            Vector2 v2 = {headCenter.x, headCenter.y - cellSize/4};
            Vector2 v3 = {headCenter.x, headCenter.y + cellSize/4};

            v1 = Vector2Rotate(Vector2Subtract(v1, headCenter), rotation*DEG2RAD);
            v2 = Vector2Rotate(Vector2Subtract(v2, headCenter), rotation*DEG2RAD);
            v3 = Vector2Rotate(Vector2Subtract(v3, headCenter), rotation*DEG2RAD);
            
            v1 = Vector2Add(v1, headCenter);
            v2 = Vector2Add(v2, headCenter);
            v3 = Vector2Add(v3, headCenter);

            DrawTriangle(v1, v2, v3, Color{35, 92, 49, 255});
        } 
        else if (i == body.size() - 1) {
            // Solo la última parte (cola) es más pequeña
            float size = cellSize * 0.7f;  // 70% del tamaño normal
            float offset = (cellSize - size) / 2;
            Rectangle segment = Rectangle{
                x*cellSize + offset, 
                y*cellSize + offset, 
                size, 
                size
            };
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
        else {
            // Resto del cuerpo normal
            Rectangle segment = Rectangle{x*cellSize, y*cellSize, (float)cellSize, (float)cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
}

void Snake::Update() {
    body.push_front(Vector2Add(body[0], direction));
    if (addSegment) {
        addSegment = false;
    } else {
        body.pop_back();
    }
}

void Snake::Reset() {
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {1,0};
} 