#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "Collision.h"
#include <vector>
#include "bullet.h"
#include "boss.h"

const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 900;
const int SQUARE_SIZE = 60;

class Game
{
public:
    Game();
    ~Game();
    void run();

    static std::vector<Bullet> bullets;

private:
    bool initSDL();
    void closeSDL();
    void spawnObstacle();
    void updateObstacle();
    void handleBulletCollision();
    void render();
    void loadImagee();
    void loadBackground();
    void renderBackground();
    void loadSoundd();
    bool isCollision();
    void renderPoints();
    void renderGameOver();
    void renderHealth();
    void handleBossBulletCollision();
    void fireBullet();
    void updateBullets();
    void handleEvent(SDL_Event &e, bool &quit);
    void loadTextTexture(const std::string &text);
    void loadMenu();
    void handleMainMenuEvent(SDL_Event &e, bool &quit, bool &showMainMenu);
    void handleGameOverEvent(SDL_Event &e, bool &quit, bool &gameOver);
    void renderMainMenu();

private:
    int backgroundPosX;
    int points;
    int level = 1;
    int miss;
    int highestPoint = 0;
    int maxHealth = 3;
    int currentHealth;
    bool isObstacleActive = false;
    bool showMainMenu = true;
    bool mouseOverPlay = false;
    bool mouseOverQuit = false;
    const int HEALTH_WIDTH = 50;
    const int HEALTH_HEIGHT = 50;
    const int HEALTH_SPACING = 10;
    Boss boss;

    SDL_Window *gWindow = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    SDL_Texture *gSquareTexture = nullptr;
    SDL_Texture *gBackgroundTexture;
    SDL_Texture *gBulletTexture = nullptr;
    SDL_Texture *textTexture;
    SDL_Texture *gObstacleTexture = nullptr;
    SDL_Texture *loadTexture(const std::string &path);
    SDL_Texture *gMenuTexture = nullptr;
    SDL_Rect menuRect;
    SDL_Rect gSquareRect;
    SDL_Rect dstRect = {10, 10, 200, 50};
    SDL_Rect gObstacleRect;
    SDL_Rect playButtonRect;
    SDL_Rect quitButtonRect;
    SDL_Rect playAgainButtonRect;
    SDL_Rect backToMenuButtonRect;
    SDL_Texture *gHealth = nullptr;
    Mix_Chunk *gShootSound = nullptr;
    Mix_Chunk *gCollision = nullptr;
    Mix_Chunk *gSound = nullptr;
    Mix_Chunk *gShotTrung = nullptr;
    Mix_Chunk *gGameOver = nullptr;
};

#endif // GAME_H
