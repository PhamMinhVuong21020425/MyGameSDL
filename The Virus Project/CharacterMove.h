#ifndef Character_Move__H_
#define Character_Move__H_

#include "Init.h"
#include "LTexture.h"
#include "Collision.h"

class character : public LTexture
{
public:
    static const int CHARACTER_WIDTH = 48;
    static const int CHARACTER_HEIGHT = 69;
    static const int CHARACTER_VEL = 10;
    static const int FRAMES_W = 3;
    static const int FRAMES_H = 4;
    int frChr = 0;
    SDL_Rect clips[FRAMES_H][FRAMES_W];
    int just_move, black_list = -1;

    bool checkMove = false;

    SDL_Rect mColliders = {10,10,CHARACTER_WIDTH,CHARACTER_HEIGHT};
    character();
    ~character();

    //Takes key presses and adjusts the character's velocity
    void handleEvent(SDL_Event &e, Mix_Music* &gMusic);

    void move();
    void renderCharacter(SDL_Renderer* &gRenderer);

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};

#endif // Character_Move__H_
