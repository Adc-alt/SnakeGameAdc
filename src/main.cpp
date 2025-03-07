#include <raylib.h>
#include "Game.h"

int main()
{
    InitWindow(Game::cellSize*Game::cellCount, Game::cellSize*Game::cellCount, "Snake Game");
    SetTargetFPS(60);

    Game game = Game();
    game.run();
    CloseWindow();
    return 0;
}