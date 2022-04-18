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

void Virus::setPos(const int &x, const int &y)
{
    mPosX = x;
    mPosY = y;
}

Virus::~Virus()
{
    free();
}

void Virus::move(SDL_Rect &otherColliders, SDL_Rect &mCollider, bool &gameOver, bool &destroyWall)
{
    mPosX += mVelX;
    if( mPosX < 0 )
    {
        mVelX = rand()%15 + 2;
        mPosX = rand()%100;
        mPosY = rand()%1200;
    }
    if( mPosX + VIRUS_WIDTH > SCREEN_WIDTH )
    {
        mVelX = -rand()%11 - 2;
        mPosX = 1000 + rand()%900;
        mPosY = rand()%1200 + 10;
    }
    if(checkCollisionRect(CovidRect, otherColliders) == true)
    {
        //Handle sound effect
        Mix_Chunk *gScratch = Mix_LoadWAV("sound/scratch.wav");
        if ( gScratch == NULL ) printf ( "Error loaded scratch sound!\n" );
        Mix_PlayChannel(-1, gScratch, 0);
        gScratch = NULL;

        destroyWall = true;

        mPosX = 1100 + rand()%900;
        mPosY = rand()%1200 + 10;
    }

    CovidRect.x = mPosX;
    CovidRect.y = mPosY;

    //If chacracter collision with virus
    if(checkCollisionRect(CovidRect, mCollider) == true)
    {
        gameOver = true;

        //Erase covid
        mPosX = -1000;
        mPosY = -100;

        //Handle sound effect
        Mix_Chunk *gWarning = Mix_LoadWAV("sound/warning.wav");
        if ( gWarning == NULL ) printf ( "Error loaded warning sound!\n" );
        Mix_PlayChannel(-1, gWarning, 0);
        gWarning = NULL;
    }
}

void Virus::renderVirus(SDL_Renderer* &gRenderer)
{
    frVirus++;
    if(frVirus/11 >= 2) frVirus = 0;
    SDL_Rect* virusClip = &gVirusClips[frVirus/11];
    render(mPosX,mPosY,virusClip,gRenderer,0.0,NULL,SDL_FLIP_NONE);
    virusClip = NULL;
}
