#include "Heart.h"

Heart::Heart(SDL_Renderer* &gRenderer)
{
    heartTexture = loadTexture("image/heart.png", gRenderer);
    heartAnimationTexture = loadTexture("image/HeartAnimation.png", gRenderer);
    HeartRect = {rand() % (SCREEN_WIDTH - 60) + 10, rand() % 3000 + 50, 35, 35};
    heart = 3;
    for(int i = 0; i < FRAME_HEART; i++)
    {
        HeartClips[i] = { 1330 * i / FRAME_HEART, 0, HEART_WIDTH, HEART_HEIGHT };
    }
}

Heart::~Heart()
{
    free();
    SDL_DestroyTexture(heartTexture);
    heartTexture = NULL;
}

void Heart::handleHeart(SDL_Rect &mColliders, Uint32 &HeartTime)
{
    //Handle heart for character
    if(checkCollisionRect(mColliders, HeartRect) == true)
    {
        Mix_Chunk* SoundHeart = Mix_LoadWAV("sound/winter.wav");
        Mix_PlayChannel(-1, SoundHeart, 0);
        SoundHeart = NULL;
        heart++;
        HeartRect = {-100, -100, 0, 0};
        if(heart > 5) heart = 5;
    }

    if((SDL_GetTicks() - HeartTime) / 1000 >= 3)
    {
        HeartRect = {rand() % (SCREEN_WIDTH - 60) + 10, rand() % 3500 + 50, 35, 35};
        HeartTime = SDL_GetTicks();
    }

}

void Heart::renderHeart(SDL_Renderer* &gRenderer)
{
    //Cat ra mot phan cua anh goc
    SDL_Rect sourceRectHeart = {0, 0, 30, 30};

    //Render heart
    for(int i = 1; i <= heart; i++)
    {
        //Hien thi anh vua cat ra man hinh voi vi tri, kich thuoc cua desRect
        SDL_Rect desRect = {10 + 30*(i - 1), 80, 30, 30};
        SDL_RenderCopy(gRenderer, heartTexture, &sourceRectHeart, &desRect);
    }

    sourceRectHeart = HeartClips[frame/10];
    SDL_RenderCopyEx(gRenderer, heartAnimationTexture, &sourceRectHeart, &HeartRect, 0.0, NULL, SDL_FLIP_NONE);
    frame++;
    if(frame/10 >= FRAME_HEART)frame = 0;
}
