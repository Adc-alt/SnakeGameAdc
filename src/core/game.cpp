#include "Game.h"
#include <raymath.h>
#include <cstdio>

// Definición de las constantes estáticas
const Color Game::green = {173, 204, 96, 255};
const Color Game::darkGreen = {43,51,24,255};
const int Game::cellSize = 30;
const int Game::cellCount = 25;

Game::Game() : snake(), food(snake.body), running(false), isFirstRun(true), 
               counter(0), blinkTime(0), lives(3), lifeBlinkTime(0), isLifeBlinking(false),
               lastTimeUpdate(0) {
    // Cargar la textura del corazón
    Image heartImage = LoadImage("assets/heart.png");  // Ruta corregida
    if (heartImage.data == nullptr) {
        printf("Error: Could not load heart.png\n");
    } else {
        ImageResize(&heartImage, 30, 30);  // Tamaño del corazón
        heartTexture = LoadTextureFromImage(heartImage);
        UnloadImage(heartImage);
    }
}

Game::~Game() {
    UnloadTexture(heartTexture);
}

void Game::DrawHearts() {
    Color heartColor = WHITE;
    if (isLifeBlinking) {
        lifeBlinkTime += GetFrameTime();
        if (((int)(lifeBlinkTime * 8) % 2) == 0) {
            heartColor = RED;
        }
        
        if (lifeBlinkTime >= 1.0f) {
            isLifeBlinking = false;
            lifeBlinkTime = 0;
        }
    }

    // Dibujar los corazones
    int heartSpacing = 35;  // Espacio entre corazones
    int startX = GetScreenWidth() - (heartSpacing * 3) - 20;  // Posición inicial X
    int y = 20;  // Posición Y
    
    for (int i = 0; i < 3; i++) {
        Color currentColor = (i < lives) ? heartColor : Fade(GRAY, 0.5f);
        DrawTexture(heartTexture, startX + (i * heartSpacing), y, currentColor);
    }
}

void Game::Draw() 
{
    if (isFirstRun)
    {
        DrawText("Snake Game", GetScreenWidth()/2 - MeasureText("Snake Game", 40)/2, 
                GetScreenHeight()/2 - 40, 40, WHITE);
        
        blinkTime += GetFrameTime();
        if (((int)(blinkTime * 2) % 2) == 0)
        {
            DrawText("Press any arrow key to start", GetScreenWidth()/2 - MeasureText("Press any arrow key to start", 20)/2, 
                    GetScreenHeight()/2 + 20, 20, WHITE);
        }
    }
    else if (running)
    {
        // Grid
        Color gridColor = {0, 0, 0, 80};
        for (int i = 0; i <= cellCount; i++)
        {
            DrawLineEx(
                (Vector2){(float)i * cellSize, 0}, 
                (Vector2){(float)i * cellSize, (float)cellCount * cellSize},
                1.0f,
                gridColor
            );
            DrawLineEx(
                (Vector2){0, (float)i * cellSize}, 
                (Vector2){(float)cellCount * cellSize, (float)i * cellSize},
                1.0f,
                gridColor
            );
        }

        // Juego
        food.Draw();
        snake.DrawSnake();
        
        // UI
        DrawText(TextFormat("Score: %d", counter), 20, 20, 20, WHITE);
        DrawHearts();  // Dibujar los corazones
    }
    else
    {
        DrawText("Game Over", GetScreenWidth()/2 - MeasureText("Game Over", 40)/2, 
                GetScreenHeight()/2 - 40, 40, WHITE);
                
        blinkTime += GetFrameTime();
        if (((int)(blinkTime * 2) % 2) == 0)
        {
            DrawText("Press any arrow key to restart", GetScreenWidth()/2 - MeasureText("Press any arrow key to restart", 20)/2, 
                    GetScreenHeight()/2 + 20, 20, WHITE);
        }
    }
}

void Game::Update() 
{
    if (running) {
        checkCollisionFood();
        checkCollisionLimits();
    }
}

void Game::checkCollisionFood() 
{
    if (Vector2Equals(snake.body[0], food.position)) {
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        counter++;
    }
}

void Game::checkCollisionLimits() 
{
    if (snake.body[0].x == cellCount || snake.body[0].x == -1 ||
        snake.body[0].y == cellCount || snake.body[0].y == -1) {
        LoseLife();
    }

    for (unsigned int i = 1; i < snake.body.size(); i++) {
        if (Vector2Equals(snake.body[0], snake.body[i])) {
            LoseLife();
        }
    }
}

void Game::LoseLife()
{
    lives--;
    isLifeBlinking = true;
    lifeBlinkTime = 0;
    
    if (lives <= 0)
    {
        GameOver();
    }
    else
    {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
    }
}

void Game::GameOver() 
{
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    counter = 0;
    lives = 3;  // Reiniciar vidas
} 

void Game::Counter()
{
    if (isFirstRun)
    {
        counter = 0;
    }
    else if (running && Vector2Equals(snake.body[0], food.position))
    {
        counter++;
    }
}

bool Game::eventTrigger(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastTimeUpdate >= interval)
    {
        lastTimeUpdate = currentTime;
        return true;
    }
    return false;
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (eventTrigger(0.2))
        {
            if (running)
            {
                snake.Update();
                Update();
            }
        }

        // Input handling
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
        {
            snake.direction = {0,-1};
            running = true;
            isFirstRun = false;
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction = {0,1};
            running = true;
            isFirstRun = false;
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction = {-1,0};
            running = true;
            isFirstRun = false;
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction = {1,0};
            running = true;
            isFirstRun = false;
        }

        ClearBackground(green);
        Draw();
        EndDrawing();
    }
}
