#include "CharacterMove.h"

character::character()
{
    mPosX = (SCREEN_WIDTH - CHARACTER_WIDTH) / 2;
    mPosY = (SCREEN_HEIGHT - CHARACTER_HEIGHT) / 2;
    mVelX = 0;
    mVelY = 0;
    frChr = 0;
    for(int i=0; i<FRAMES_H; i++)
    {
        for(int j=0; j<FRAMES_W; j++)
        {
            clips[i][j].x = 165*j/FRAMES_W + 5;
            clips[i][j].y = 332*i/FRAMES_H + 3;
            clips[i][j].w = CHARACTER_WIDTH;
            clips[i][j].h = CHARACTER_HEIGHT;
        }
    }
}

character::~character()
{
    free();
}

void character::handleEvent(SDL_Event &e, Mix_Music* &gMusic)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= CHARACTER_VEL;
            just_move = 3;
            break;
        case SDLK_DOWN:
            mVelY += CHARACTER_VEL;
            just_move = 0;
            break;
        case SDLK_LEFT:
            mVelX -= CHARACTER_VEL;
            just_move = 1;
            break;
        case SDLK_RIGHT:
            mVelX += CHARACTER_VEL;
            just_move = 2;
            break;
        case SDLK_m:
            if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic( gMusic, -1 );
            else
            {
                if( Mix_PausedMusic() == 1 ) Mix_ResumeMusic();
                else Mix_PauseMusic();
            }
            break;
        default:
            break;
        }
        checkMove = true;
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += CHARACTER_VEL;
            just_move = 3;
            break;
        case SDLK_DOWN:
            mVelY -= CHARACTER_VEL;
            just_move = 0;
            break;
        case SDLK_LEFT:
            mVelX += CHARACTER_VEL;
            just_move = 1;
            break;
        case SDLK_RIGHT:
            mVelX -= CHARACTER_VEL;
            just_move = 2;
            break;
        default:
            break;
        }
        frChr = 12;
        checkMove = false;
    }
}

void character::move()
{
    //Move the character left or right
    mPosX += mVelX;
    mColliders.x = mPosX;

    //If the character went too far to the left or right
    if(mPosX < 0 || mPosX + CHARACTER_WIDTH > SCREEN_WIDTH)
    {
        mPosX -= mVelX;
        mColliders.x = mPosX;
    }

    //Move the character up or down
    mPosY += mVelY;
    mColliders.y = mPosY;

    //If the character went too far to the up or down
    if(mPosY < 0 || mPosY + CHARACTER_HEIGHT > SCREEN_HEIGHT)
    {
        mPosY -= mVelY;
        mColliders.y = mPosY;
    }
}

void character::renderCharacter(SDL_Renderer* &gRenderer)
{
    if(checkMove == true)frChr++;
    int frame = frChr/12;
    if(frame == FRAMES_W)frChr = 0;
    SDL_Rect* currentClip = &clips[just_move][frame];
    render(mPosX, mPosY, currentClip, gRenderer, 0.0, NULL, SDL_FLIP_NONE);
}
