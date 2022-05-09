#ifndef WALL__H_
#define WALL__H_

#include "Init.h"
#include "BaseFunction.h"
#include "LTexture.h"

class Wall : public LTexture
{
public:
    static const int FRAME_WALL = 4;
    SDL_Rect wallCollider = {SCREEN_WIDTH / 2 + 10, SCREEN_HEIGHT / 2 - 10, 20, 40};
    Wall();
    ~Wall();
    void createWall(SDL_Renderer* &gRenderer);
    void renderWall(SDL_Renderer* &gRenderer, const int &x, const int &y);

private:
    SDL_Texture *texture = NULL;
    SDL_Rect clipWall[FRAME_WALL];
    int frWall;

};

#endif // WALL__H_
