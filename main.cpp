#include "include.h"
#include "load_image.h"

int main(int argc, char* argv[])
{
    initSDL(window, renderer);

    bool isQuit = false;
    /*
    while(!isQuit)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
                isQuit = true;
        }

    }
   */
    SDL_RenderClear(renderer);
    SDL_Texture* bkground = IMG_LoadTexture("image//daybien.png", renderer);
    SDL_RenderCopy(renderer, bkground, NULL, NULL);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);

    return 0;
}
