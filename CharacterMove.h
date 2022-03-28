#ifndef Character_Move__H_
#define Character_Move__H_

#include "Init.h"
#include "LTexture.h"
#include "Collision.h"

class character
{
public:
    LTexture gSpriteSheetTexture;
    static const int CHARACTER_WIDTH = 50;
    static const int CHARACTER_HEIGHT = 82;
    static const int CHARACTER_VEL = 6;
    SDL_RendererFlip flip;
    SDL_Rect mColliders = {0,0,CHARACTER_WIDTH,CHARACTER_HEIGHT};
    character();
    character(int x, int y);
    ~character();
    void loadCharacter(SDL_Renderer* gRenderer);

    //Takes key presses and adjusts the character's velocity
    void handleEvent(SDL_Event &e, bool &checkMove);

    void move(SDL_Rect &otherColliders, bool &gameOver);
    void renderCharacter(SDL_Renderer * gRenderer, SDL_Rect * clip = NULL);
    //std::vector<SDL_Rect>& getColliders();

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};

#endif // Character_Move__H_
