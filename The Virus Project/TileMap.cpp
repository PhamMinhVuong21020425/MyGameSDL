#include "TileMap.h"

TileMap::TileMap()
{
    desRect->x = 0;
    desRect->y = 0;
    desRect->w = coefficient;
    desRect->h = coefficient;
}

void TileMap::loadTiles(SDL_Renderer* &gRenderer)
{
    grassTexture.loadFromFile("image/solid.png", gRenderer);
    defenceTexture.loadFromFile("image/defence.png", gRenderer);
    defenceSideTexture.loadFromFile("image/defenceSide.png", gRenderer);
}

void TileMap::drawMap(SDL_Renderer* &gRenderer)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (tile[i][j] == 0)
                grassTexture.render(j * coefficient, i * coefficient, desRect, gRenderer);

            if (tile[i][j] == 1)
                defenceTexture.render(j * coefficient, i * coefficient, desRect, gRenderer);

            if(tile[i][j] == 9)
                defenceSideTexture.render(j * coefficient, i * coefficient, desRect, gRenderer);
        }
    }

}

TileMap::~TileMap()
{
    grassTexture.free();
    defenceTexture.free();
    defenceSideTexture.free();
    desRect = NULL;
}

