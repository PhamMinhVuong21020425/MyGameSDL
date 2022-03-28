#include "Init.h"
#include "LTexture.h"
#include "CharacterMove.h"
#include "Virus.h"
#include "Collision.h"
#include "TileMap.h"

int main( int argc, char* argv[] )
{
    //create rand seed
    srand((int)time(NULL));

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //The window renderer
    SDL_Renderer* gRenderer = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;

    //Start up SDL and create window
    if( !init( gWindow, gRenderer) )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        Mix_Music *gMusic = Mix_LoadMUS("sound/cutesong.mp3");
        if( gMusic == NULL )
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		Mix_PlayMusic( gMusic, -1 );

        welcome(gRenderer);
        TileMap GameMap;

        character chr;
        Virus virus;
        SDL_Rect wall = {600,0,50,SCREEN_HEIGHT};

        SDL_Rect gSpriteClips[ ANIMATION_FRAMES ];
        SDL_Rect gVirusClips[2];

        chr.loadCharacter(gRenderer);
        virus.loadVirus(gRenderer);

        //Set sprite clips character
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 166;
        gSpriteClips[0].w = 55; //165
        gSpriteClips[0].h = 83;//332

        gSpriteClips[1].x = 55;
        gSpriteClips[1].y = 166;
        gSpriteClips[1].w = 55;
        gSpriteClips[1].h = 83;

        gSpriteClips[2].x = 110;
        gSpriteClips[2].y = 166;
        gSpriteClips[2].w = 55;
        gSpriteClips[2].h = 83;

        //Set sprite clips Virus
        gVirusClips[0].x = 0;
        gVirusClips[0].y = 0;
        gVirusClips[0].w = 52;
        gVirusClips[0].h = 56;

        gVirusClips[1].x = 52;
        gVirusClips[1].y = 0;
        gVirusClips[1].w = 52;
        gVirusClips[1].h = 56;

        //Main loop flag
        bool quit = false;
        bool gameOver = false;
        //Event handler
        SDL_Event e;

        int frChr = 0, frVirus = 0;
        bool checkMove;

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT ) quit = true;

                //Handle Music
                else if( e.type == SDL_KEYDOWN )
                {
                    switch( e.key.keysym.sym )
                    {
                    case SDLK_m:
                        //If there is no music playing
                        if( Mix_PlayingMusic() == 0 )
                        {
                            //Play the music
                            Mix_PlayMusic( gMusic, -1 );
                        }
                        //If music is being played
                        else
                        {
                            //If the music is paused
                            if( Mix_PausedMusic() == 1 )
                            {
                                //Resume the music
                                Mix_ResumeMusic();
                            }
                            //If the music is playing
                            else
                            {
                                //Pause the music
                                Mix_PauseMusic();
                            }
                        }
                        break;

                    case SDLK_0:
                        //Stop the music
                        Mix_HaltMusic();
                        break;
                    }
                }

                //Handle input for character
                chr.handleEvent( e, checkMove );
            }


            virus.move(wall);
            chr.move(virus.Covid, gameOver);


            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 0);
            SDL_RenderClear( gRenderer );

            //Draw map
            GameMap.loadTiles(gRenderer);
            GameMap.drawMap(gRenderer);

            SDL_Rect* currentClip = &gSpriteClips[frChr/9];
            chr.renderCharacter(gRenderer, currentClip);

            SDL_Rect* virusClip = &gVirusClips[frVirus/11];
            virus.renderVirus(gRenderer, virusClip);

            //Update screen
            SDL_RenderPresent( gRenderer );

            if(checkMove == true) frChr++;
            else while(frChr/9 < 1)frChr++;
            if(frChr/9 >= ANIMATION_FRAMES) frChr = 0;

            frVirus++;
            if(frVirus/11 >= 2) frVirus = 0;

            if(gameOver == true)
            {
                GameOver(gRenderer);
                Mix_FreeMusic( gMusic );
	            gMusic = NULL;
                quit = true;
            }
        }
    }

    //Free resources and close SDL
    close(gWindow, gRenderer, gTexture);

    return 0;
}
