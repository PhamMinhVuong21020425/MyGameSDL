#include "TileMap.h"

TileMap::TileMap(SDL_Renderer* &gRenderer)
{
    desRect = {0, 0, coefficient, coefficient};

    solidTexture = loadTexture("image/solid.png", gRenderer);

    defenceTexture = loadTexture("image/defence.png", gRenderer);
}

void TileMap::renderTiles( SDL_Texture* &texture, const int &x, const int &y, const SDL_Rect* clip, SDL_Renderer* &gRenderer )
{
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, w, h };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopy( gRenderer, texture, clip, &renderQuad );
}

void TileMap::drawMap(SDL_Renderer* &gRenderer)
{

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tile[i][j] == 1)
            {
                renderTiles(defenceTexture, j * coefficient, i * coefficient, &desRect, gRenderer );
            }
            else
            {
                renderTiles(solidTexture, j * coefficient, i * coefficient, &desRect, gRenderer );
            }
        }
    }
}

TileMap::~TileMap()
{
    free();

    SDL_DestroyTexture(solidTexture);
    solidTexture = NULL;

    SDL_DestroyTexture(defenceTexture);
    defenceTexture = NULL;
}

