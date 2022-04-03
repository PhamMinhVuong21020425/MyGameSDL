#include "Virus.h"

Virus::Virus()
{
    mPosX = 0;
    mPosY = 0;
    mVelX = 3;
    mVelY = 0;
    frVirus = 0;

    //Set sprite clips Virus
    gVirusClips[0].x = 5;
    gVirusClips[0].y = 3;
    gVirusClips[0].w = 50;
    gVirusClips[0].h = 54;

    gVirusClips[1].x = 55;
    gVirusClips[1].y = 3;
    gVirusClips[1].w = 50;
    gVirusClips[1].h = 54;
}

void Virus::setPos(int x, int y)
{
    mPosX = x;
    mPosY = y;
}

Virus::~Virus()
{
    free();
}

void Virus::renderVirus(SDL_Renderer* &gRenderer)
{
    frVirus++;
    if(frVirus/11 >= 2) frVirus = 0;
    SDL_Rect* virusClip = &gVirusClips[frVirus/11];
    render(mPosX,mPosY,virusClip,gRenderer,0.0,NULL,SDL_FLIP_NONE);
    virusClip = NULL;
}

void Virus::move(SDL_Rect &otherColliders, SDL_Rect &mCollider, bool &gameOver)
{
    mPosX += mVelX;
    if( mPosX < 0 )
    {
        mVelX = rand()%9 + 2;
        mPosX = rand()%100;
        mPosY = rand()%1200;
    }
    if( mPosX + VIRUS_WIDTH > SCREEN_WIDTH )
    {
        mVelX = -rand()%10 - 2;
        mPosX = 1000 + rand()%900;
        mPosY = rand()%1200 + 10;
    }
    if(checkCollisionRect(CovidRect, otherColliders) == true)
    {
        mPosX = 1100 + rand()%900;
        mPosY = rand()%1200 + 10;
    }
    CovidRect.x = mPosX;
    CovidRect.y = mPosY;
    if(checkCollisionRect(CovidRect,mCollider) == true)gameOver = true;
}
