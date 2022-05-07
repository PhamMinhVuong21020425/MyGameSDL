#ifndef HEART__H_
#define HEART__H_

#include "Init.h"
#include "LTexture.h"
#include "Collision.h"

class Heart : public LTexture
{
public:
    static const int FRAME_HEART = 10;
    static const int HEART_WIDTH = 133;
    static const int HEART_HEIGHT = 110;
    int heart;
    SDL_Rect HeartClips[FRAME_HEART];

    Heart(SDL_Renderer* &gRenderer);
    ~Heart();
    void handleHeart(SDL_Rect &mColliders, Uint32 &HeartTime);
    void renderHeart(SDL_Renderer* &gRenderer);

private:
    SDL_Rect HeartRect;
    SDL_Texture *heartTexture = NULL;
    SDL_Texture *heartAnimationTexture = NULL;
    int frame = 0;
};

#endif // WALL__H_
