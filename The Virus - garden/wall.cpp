#include "wall.h"

Wall::Wall()
{
    frWall = 0;
    for(int i = 0; i < FRAME_WALL; i++)
    {
        clipWall[i].x = 0;
        clipWall[i].y = i*40;
        clipWall[i].w = 20;
        clipWall[i].h = 40;
    }
}

Wall::~Wall()
{
    free();
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Wall::createWall(SDL_Renderer* &gRenderer)
{
    texture = loadTexture("image/wall.png", gRenderer);
}

void Wall::renderWall(SDL_Renderer* &gRenderer, const int &x, const int &y)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, 20, 40 };

    SDL_Rect *clip = &clipWall[frWall/15];

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, texture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);

    frWall++;
    if(frWall/15 >= FRAME_WALL)frWall = 0;
}
