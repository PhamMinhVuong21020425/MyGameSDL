#include "Init.h"
#include "LTexture.h"
#include "CharacterMove.h"
#include "Virus.h"
#include "Collision.h"
#include "TileMap.h"

int main( int argc, char* args[] )
{
    //create rand seed
    srand((unsigned int)time(NULL));

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Start up SDL and create window
    if( !init( gWindow, gRenderer) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        Mix_Music *gMusic = Mix_LoadMUS("sound/cutesong.mp3");
        if( gMusic == NULL ) printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        Mix_PlayMusic( gMusic, -1 );

        Uint32 score = 0;
        welcome(gRenderer);
        TileMap GameMap;
        GameMap.loadTiles(gRenderer);

        character chr;
        chr.loadFromFile("image/Sprite.png", gRenderer);

        Virus LeftVirus[NUM_VIRUS];
        Virus *virus = new Virus;
        virus = LeftVirus;

        Virus RightVirus[NUM_VIRUS];
        Virus *gVirus = new Virus;
        gVirus = RightVirus;

        for(int i = 0; i < NUM_VIRUS; i++)
        {
            (virus + i)->loadFromFile("image/CovidOther.png", gRenderer);
            (gVirus + i)->loadFromFile("image/CovidRed.png", gRenderer);
            (gVirus + i)->setPos(SCREEN_WIDTH + rand()%300, 0);
        }
        //Main loop flag
        bool quit = false;
        bool gameOver = false;

        //Event handler
        SDL_Event e;

        Uint32 startTime = SDL_GetTicks();

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT ) quit = true;

                //Handle input for character
                chr.handleEvent( e, gMusic );
            }

            chr.move();

            for(int i = 0; i < NUM_VIRUS; i++)
            {
                SDL_Rect wall = { 0,0,50,SCREEN_HEIGHT};
                (virus+i)->move(wall,chr.mColliders,gameOver);

                SDL_Rect wallRToL = {SCREEN_WIDTH,0,50,SCREEN_HEIGHT};
                (gVirus+i)->move(wallRToL,chr.mColliders,gameOver);
            }

            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
            SDL_RenderClear( gRenderer );

            //Draw map
            GameMap.drawMap(gRenderer);

            //Render object
            for(int i = 0; i < NUM_VIRUS; i++)
            {
                (virus+i)->renderVirus(gRenderer);
                (gVirus + i)->renderVirus(gRenderer);
            }

            chr.renderCharacter( gRenderer );

            score = (SDL_GetTicks() - startTime) / 100;
            renderScore(gRenderer,score);

            //Update screen
            SDL_RenderPresent( gRenderer );

            if(gameOver == true)
            {
                SDL_Delay(1000);
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                GameOver(gRenderer,score);
                Mix_FreeMusic( gMusic );
                gMusic = NULL;
                quit = true;
            }
        }
        if(virus != nullptr) virus = nullptr;
        if(gVirus != nullptr) gVirus = nullptr;
    }

    //Free resources and close SDL
    close(gWindow, gRenderer);

    return 0;
}
