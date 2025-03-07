#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Food.h"

class Game {
public:
    Snake snake;
    Food food;
    bool running;
    bool isFirstRun;
    int counter;
    float blinkTime;    
    int lives;
    float lifeBlinkTime;
    bool isLifeBlinking;
    Texture2D heartTexture;  // Textura para el corazón

    Game();
    ~Game();  // Añadimos destructor para liberar la textura
    void Draw();
    void Update();
    void checkCollisionFood();
    void checkCollisionLimits();
    void GameOver();
    void Counter();
    void blinkText();
    void LoseLife();
    void DrawHearts();  // Nuevo método para dibujar los corazones
};

#endif 