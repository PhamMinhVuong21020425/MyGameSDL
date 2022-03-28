#include "CharacterMove.h"

character::character()
{
    mPosX = (SCREEN_WIDTH - CHARACTER_WIDTH) / 2;
    mPosY = (SCREEN_HEIGHT - CHARACTER_HEIGHT) / 2;
    mVelX = 0;
    mVelY = 0;
    flip = SDL_FLIP_NONE;
}

character::character(int x, int y)
{
    mPosX = x;
    mPosY = y;
    mVelX = 0;
    mVelY = 0;
    flip = SDL_FLIP_NONE;

}

void character::loadCharacter(SDL_Renderer* gRenderer)
{
    gSpriteSheetTexture.loadFromFile("image/Sprite.png", gRenderer);
}

void character::handleEvent(SDL_Event &e, bool &checkMove)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= CHARACTER_VEL; break;
        case SDLK_DOWN:
            mVelY += CHARACTER_VEL; break;
        case SDLK_LEFT:
            mVelX -= CHARACTER_VEL;
            flip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_RIGHT:
            mVelX += CHARACTER_VEL;
            flip = SDL_FLIP_NONE;
            break;
        }
        checkMove = true;
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += CHARACTER_VEL; break;
        case SDLK_DOWN:
            mVelY -= CHARACTER_VEL; break;
        case SDLK_LEFT:
            mVelX += CHARACTER_VEL;
            flip = SDL_FLIP_HORIZONTAL;
            break;
        case SDLK_RIGHT:
            mVelX -= CHARACTER_VEL;
            flip = SDL_FLIP_NONE;
            break;
        }
        checkMove = false;
    }
}

void character::move( SDL_Rect &otherColliders, bool &gameOver )
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

    if( checkCollisionRect(mColliders, otherColliders) == true )gameOver = true;
}

void character::renderCharacter(SDL_Renderer * gRenderer, SDL_Rect * clip)
{
    gSpriteSheetTexture.render(mPosX, mPosY, clip, gRenderer, 0.0, NULL, flip);
}

character::~character()
{
    gSpriteSheetTexture.free();
}

