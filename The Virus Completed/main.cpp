#include "Init.h"
#include "BaseFunction.h"
#include "LTexture.h"
#include "TileMap.h"
#include "CharacterMove.h"
#include "Virus.h"
#include "wall.h"
#include "Heart.h"

int main( int argc, char* args[] )
{
    //create rand seed
    srand((unsigned int)time(NULL));

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Background music
    Mix_Music *gMusic = NULL;

    //Start up SDL and create window
    if( !init( gWindow, gRenderer) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        gMusic = Mix_LoadMUS("sound/BackgroundMusic.mp3");
        if(gMusic == NULL) printf( "Failed to load beat music! SDL_Mixer Error: %s\n", Mix_GetError() );
        Mix_PlayMusic( gMusic, -1 );

Restart:
        //Mix_ResumeMusic();
        int NUM_COVID_SCORES = 0;
        Uint32 SCORE = 0;

        if(welcome(gRenderer) == true)
        {
            TileMap GameMap(gRenderer);

            Wall newWall;
            int wall_X = SCREEN_WIDTH / 2 + 25, wall_Y = SCREEN_HEIGHT / 2 - 20;
            newWall.createWall(gRenderer);

            character chr;
            chr.loadFromFile("image/Sprite.png", gRenderer);

            const int NUM_VIRUS = 6;

            Virus LeftVirus[NUM_VIRUS];
            Virus *virus = new Virus();
            virus = LeftVirus;

            Virus RightVirus[NUM_VIRUS];
            Virus *gVirus = new Virus();
            gVirus = RightVirus;

            for(int i = 0; i < NUM_VIRUS; i++)
            {
                (virus + i)->loadFromFile("image/CovidOther.png", gRenderer);
                if(i % 3 == 0)(gVirus + i)->loadFromFile("image/Covid.png", gRenderer);
                else (gVirus + i)->loadFromFile("image/CovidRed.png", gRenderer);
                (gVirus + i)->setPos(SCREEN_WIDTH + rand() % 200, 0);
            }

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            Uint32 startTime = SDL_GetTicks();
            Uint32 HeartTime = SDL_GetTicks();
            Heart HeartOfChacracter( gRenderer );

            //While application is running
            while( !quit )
            {
                bool gameOver = false, pause = false;

                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT ) quit = true;

                    //Handle input for character
                    chr.handleEvent( e, gMusic );

                    //Handle wall
                    if(e.type == SDL_KEYDOWN)
                    {
                        switch(e.key.keysym.sym)
                        {
                        case SDLK_a:
                            wall_X = chr.getPosX() - 20;
                            wall_Y = chr.getPosY() + 15;
                            break;
                        case SDLK_d:
                            wall_X = chr.getPosX() + 45;
                            wall_Y = chr.getPosY() + 15;
                            break;
                        case SDLK_p:
                            pause = true;
                            break;
                        default:
                            break;
                        }
                    }
                }

                newWall.wallCollider = {wall_X, wall_Y, 20, 38};
                chr.move(newWall.wallCollider);
                bool destroyWall = false;

                for(int i = 0; i < NUM_VIRUS; i++)
                {
                    (virus+i)->move(newWall.wallCollider, chr.mColliders, gameOver, destroyWall);
                    (gVirus+i)->move(newWall.wallCollider, chr.mColliders, gameOver, destroyWall);
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0, 191, 255, 0);
                SDL_RenderClear( gRenderer );

                //Draw map
                GameMap.drawMap(gRenderer);

                //Render object
                for(int i = 0; i < NUM_VIRUS; i++)
                {
                    (virus + i)->renderVirus(gRenderer);
                    (gVirus + i)->renderVirus(gRenderer);
                }

                if(destroyWall == true)
                {
                    NUM_COVID_SCORES++;
                    wall_X = -1000;
                    wall_Y = -1000;
                }

                //Render wall
                newWall.renderWall(gRenderer, wall_X, wall_Y);

                SCORE = (SDL_GetTicks() - startTime) / 1000;
                renderScore(gRenderer, SCORE, NUM_COVID_SCORES);

                HeartOfChacracter.handleHeart(chr.mColliders, HeartTime);
                HeartOfChacracter.renderHeart( gRenderer );

                if(gameOver == false)chr.renderCharacter( gRenderer );
                else
                {
                    chr.renderEffect(gRenderer);
                    SDL_RenderPresent(gRenderer);

                    HeartOfChacracter.heart--;
                    SDL_Delay(600);
                }

                //Handle pause
                Uint32 pauseTime = SDL_GetTicks();
                if(pause == true)
                {
                    SDL_Rect fillRect = {500, 285, 305, 85};
                    SDL_SetRenderDrawColor(gRenderer, 0, 240, 0, 255);
                    SDL_RenderFillRect(gRenderer, &fillRect);

                    SDL_SetRenderDrawColor(gRenderer, 0, 10, 255, 255);
                    for(int i = 0; i <= 2; i ++)
                    {
                        fillRect = {500 - i, 285 - i, 305 + 2*i, 85 + 2*i};
                        SDL_RenderDrawRect(gRenderer, &fillRect);
                    }

                    SDL_Color fcolor = {255,0,69};
                    renderTextTexture(gRenderer, "SuperMario256.ttf", "PAUSE", 32, fcolor, 600, 300 );

                    fcolor = {0, 0, 0};
                    renderTextTexture(gRenderer, "lazy.ttf", "PRESS ENTER TO RESUME", 25, fcolor, 515, 335 );

                    SDL_RenderPresent( gRenderer );
                    waitUntilEnterPressed();
                    startTime += (SDL_GetTicks() - pauseTime);
                }

                //Update screen
                SDL_RenderPresent( gRenderer );

                //Game Over
                if(HeartOfChacracter.heart == 0)
                {
                    SDL_Delay(1000);
                    //Mix_PauseMusic();

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);

                    GameOver(gRenderer, SCORE, NUM_COVID_SCORES);
                    quit = true;
                }
            }
            if(virus != nullptr) virus = nullptr;
            if(gVirus != nullptr) gVirus = nullptr;
goto Restart;
        }
    }

    //Free resources and close SDL
    close(gWindow, gRenderer, gMusic);
    return 0;
}
