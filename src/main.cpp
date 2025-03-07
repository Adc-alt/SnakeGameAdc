#include <raylib.h>
#include "Game.h"

Color green = {173, 204, 96, 255};
Color darkGreen = {43,51,24,255};

int cellSize = 30;
int cellCount = 25;

double lastTimeUpdate = 0;

bool eventTrigger(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastTimeUpdate >= interval)
    {
        lastTimeUpdate = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(cellSize*cellCount, cellSize*cellCount, "Snake Game");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (eventTrigger(0.2))
        {
            if (game.running)
            {
                game.snake.Update();
                game.Update();
            }
        }

        // Input handling
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0,-1};
            game.running = true;
            game.isFirstRun = false;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0,1};
            game.running = true;
            game.isFirstRun = false;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1,0};
            game.running = true;
            game.isFirstRun = false;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = {1,0};
            game.running = true;
            game.isFirstRun = false;
        }

        ClearBackground(green);
        game.Draw();
        EndDrawing();
    
    }
    CloseWindow();
    return 0;
}