#include "wall.h"

Wall::Wall()
{
    frWall = 0;
    for(int i = 0; i < FRAME_WALL; i++)
    {
        clipWall[i].x = i*40;
        clipWall[i].y = 0;
        clipWall[i].w = 40;
        clipWall[i].h = 20;
    }
}

Wall::~Wall()
{
    free();
}

void Wall::createWall(SDL_Renderer* &gRenderer)
{
   texture = loadTexture("image/wall.png", gRenderer);
}

void Wall::renderWall(SDL_Renderer* &gRenderer, const int &x, const int &y)
{
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, w, h };

    SDL_Rect *clip = &clipWall[frWall/10];

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, texture, clip, &renderQuad, 90.0, NULL, SDL_FLIP_VERTICAL);

     frWall++;
     if(frWall/10 >= FRAME_WALL)frWall = 0;
}

void Wall::destroyWall(SDL_Renderer* &gRenderer)
{

}
