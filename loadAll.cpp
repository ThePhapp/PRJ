#include "game.h"

void Game::loadImagee()
{
    gSquareTexture = loadTexture("image/Player.png");
    gBulletTexture = loadTexture("image/Bullet.png");
    if (gSquareTexture == nullptr || gBulletTexture == nullptr)
    {
        std::cerr << "Failed to load textures!" << std::endl;
        closeSDL();
    }

    gObstacleTexture = loadTexture("image/obstacle.png");
    if (gObstacleTexture == nullptr)
    {
        std::cerr << "Failed to load obstacle texture!" << std::endl;
        closeSDL();
    }

    gHealth = loadTexture("image/health.png");
    if(gHealth == nullptr)
    {
        std::cerr << "Failed to load health texture!" << std::endl;
        closeSDL();
    }

}

void Game::loadBackground()
{
    gBackgroundTexture = loadTexture("image/Background.png");

    if (gBackgroundTexture == nullptr)
    {
        std::cerr << "Failed to load background texture!" << std::endl;
        closeSDL();
        exit(3);
    }
}

SDL_Texture* Game::loadTexture(const std::string& path)
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cerr << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        std::cerr << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return texture;
}
void Game::renderPoints() {
    std::string pointString = "Points: " + std::to_string(points);
    TTF_Font* font1 = TTF_OpenFont("font/2.ttf", 35);
    if (font1 == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font1, pointString.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Unable to render text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font1);
        return;
    }
    SDL_Texture* pointsTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (pointsTexture == nullptr) {
        std::cerr << "Unable to create texture from text surface: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font1);

    SDL_Rect dstRect = {10, 10, textSurface->w, textSurface->h}; 
    SDL_RenderCopy(gRenderer, pointsTexture, nullptr, &dstRect);
    SDL_DestroyTexture(pointsTexture); 
}

void Game::loadSoundd()
{
    gShootSound = Mix_LoadWAV("sound/shoot.wav");
    if(gShootSound==nullptr) {
        std::cerr<<"Failed to load ShootSound! Error: "<<Mix_GetError()<<std::endl;
    }
    gSound = Mix_LoadWAV("Sound/mission.wav");
    if(gSound==nullptr) {
        std::cerr<<"Failed to load gSound! Error: "<<Mix_GetError()<<std::endl;
    }
    gShotTrung = Mix_LoadWAV("Sound/gg.wav");
    if(gShotTrung==nullptr) {
        std::cerr<<"Failed to load gShotTrung! Error: "<<Mix_GetError()<<std::endl;
    }
    gCollision = Mix_LoadWAV("Sound/vacham.wav");
    if(gCollision==nullptr) {
        std::cerr<<"Failed to load gCollision! Error: "<<Mix_GetError()<<std::endl;
    }
    gGameOver = Mix_LoadWAV("Sound/GameOver.wav");
    if(gGameOver==nullptr) {
        std::cerr<<"Failed to load gGameOver! Error: "<<Mix_GetError()<<std::endl;
    }
}

void Game::renderHealth()
{
    int heartX = 10;
    int heartY = SCREEN_HEIGHT - HEALTH_HEIGHT - 10;

    for (int i = 0; i < maxHealth; ++i) {
        SDL_Rect destRect = {heartX, heartY, HEALTH_WIDTH, HEALTH_HEIGHT};
        if (i < currentHealth) {
            SDL_RenderCopy(gRenderer, gHealth, nullptr, &destRect);
        }
        heartX += HEALTH_WIDTH + HEALTH_SPACING;
    }
}

void Game::renderGameOver() 
{
    TTF_Font* font2 = TTF_OpenFont("font/1.ttf", 70);
    if(font2 == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColorGV = {225, 0, 0};
    SDL_Surface* gameOverSurface = TTF_RenderText_Solid(font2, "GameOver", textColorGV);
    if (gameOverSurface == nullptr) {
        std::cerr << "Unable to render Game Over surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font2);
        return;
    }

    SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(gRenderer, gameOverSurface);
    if (gameOverTexture == nullptr) {
        std::cerr << "Unable to create texture from Game Over surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(gameOverSurface);
        TTF_CloseFont(font2);
        return;
    }
    SDL_Rect gameOverRect = {(SCREEN_WIDTH - gameOverSurface->w) / 2, (SCREEN_HEIGHT - gameOverSurface->h) / 2, gameOverSurface->w, gameOverSurface->h};

    SDL_Surface* playAgainSurface = TTF_RenderText_Solid(font2, "Press Space to PlayAgain !!!", textColorGV);
    if (playAgainSurface == nullptr) {
        std::cerr << "Unable to render Play Again surface: " << TTF_GetError() << std::endl;
        SDL_DestroyTexture(gameOverTexture);
        TTF_CloseFont(font2);
        return;
    }

    SDL_Texture* playAgainTexture = SDL_CreateTextureFromSurface(gRenderer, playAgainSurface);
    if (playAgainTexture == nullptr) {
        std::cerr << "Unable to create texture from Play Again surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(playAgainSurface);
        SDL_DestroyTexture(gameOverTexture);
        TTF_CloseFont(font2);
        return;
    }
    SDL_Rect playAgainRect = {(SCREEN_WIDTH - playAgainSurface->w) / 2, gameOverRect.y + gameOverRect.h + 20, playAgainSurface->w, playAgainSurface->h};

    SDL_RenderCopy(gRenderer, gameOverTexture, nullptr, &gameOverRect);    //render
    SDL_RenderCopy(gRenderer, playAgainTexture, nullptr, &playAgainRect);
    if (Mix_PlayChannel(-1, gGameOver, 0) == -1)    //SoundVaCham
        {
            std::cerr << "Failed to play sound GameOver! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }
}
