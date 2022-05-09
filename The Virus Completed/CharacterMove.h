#ifndef Character_Move__H_
#define Character_Move__H_

#include "Init.h"
#include "BaseFunction.h"
#include "LTexture.h"

class character : public LTexture
{
public:
    static const int CHARACTER_WIDTH = 42;
    static const int CHARACTER_HEIGHT = 69;
    static const int CHARACTER_VEL = 8;
    static const int FRAMES_W = 3;
    static const int FRAMES_H = 4;
    int frChr;
    SDL_Rect clips[FRAMES_H][FRAMES_W];
    int just_move;

    bool checkMove = false;

    SDL_Rect mColliders = {
                             (SCREEN_WIDTH - CHARACTER_WIDTH) / 2,
                             (SCREEN_HEIGHT - CHARACTER_HEIGHT) / 2,
                              CHARACTER_WIDTH, CHARACTER_HEIGHT
                          };
    character();
    ~character();
    int getPosX();
    int getPosY();

    //Takes key presses and adjusts the character's velocity
    void handleEvent( SDL_Event &e, Mix_Music* &gMusic );

    void move(SDL_Rect &wallCollider);
    void renderCharacter( SDL_Renderer* &gRenderer );
    void renderEffect( SDL_Renderer* &gRenderer );

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};

#endif // Character_Move__H_
