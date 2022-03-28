#include "Virus.h"

Virus::Virus()
{
    mPosX = 0; mPosY = 0;
    mVelX = 0; mVelY = 0;
}

void Virus::loadVirus (SDL_Renderer* gRenderer)
{
    gVirusTexture.loadFromFile("image/Covid.png", gRenderer);
}

void Virus::renderVirus(SDL_Renderer * gRenderer, SDL_Rect* clip)
{
    gVirusTexture.render(mPosX, mPosY, clip, gRenderer);
}

void Virus::move(SDL_Rect &otherColliders)
{
    mPosX += 3;

    //If the character went too far to the left or right
    if(mPosX < 0 || mPosX + VIRUS_WIDTH > SCREEN_WIDTH || checkCollisionRect(Covid, otherColliders) == true)
    {
        mPosX = 0;
    }

    mPosY = 300;

    Covid.x = mPosX;
    Covid.y = mPosY;
}

Virus::~Virus()
{
    gVirusTexture.free();
}
