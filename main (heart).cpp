#include "Init.h"
#include "LTexture.h"
#include "TileMap.h"
#include "Collision.h"
#include "CharacterMove.h"
#include "Virus.h"
#include "Timer.h"

//Viet ham xu li thoi gian
//Viet cach xu li de an mang trai tim

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

        int heart = 3;
        SDL_Texture *heartTexture = loadTexture("image/heart.png", gRenderer);

        int NUM_COVID_SCORES = 0;
        Uint32 SCORE = 0;

        welcome(gRenderer);
        TileMap GameMap(gRenderer);

        Wall newWall;
        int wall_X = SCREEN_WIDTH / 2 + 25, wall_Y = SCREEN_HEIGHT / 2 - 20;
        newWall.createWall(gRenderer);

        character chr;
        chr.loadFromFile("image/Sprite.png", gRenderer);

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
            (gVirus + i)->setPos(SCREEN_WIDTH + rand() % 300, 0);
        }

        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;

        Uint32 startTime = SDL_GetTicks();

        Uint32 HeartTime = SDL_GetTicks();
        SDL_Rect HeartRect = {rand() % (SCREEN_WIDTH - 60) + 10, rand() % 2000 + 50, 30, 30};

        //While application is running
        while( !quit )
        {
            bool gameOver = false;

            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT ) quit = true;

                //Handle input for character
                chr.handleEvent( e, gMusic );
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
                    default:
                        break;
                    }
                }
            }

            newWall.wallCollider = {wall_X, wall_Y - 3, 20, 42};
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
                (virus+i)->renderVirus(gRenderer);
                (gVirus + i)->renderVirus(gRenderer);
            }

            chr.renderCharacter( gRenderer );

            if(destroyWall == true)
            {
                NUM_COVID_SCORES++;
                wall_X = -100;
                wall_Y = -1000;
            }

            newWall.renderWall(gRenderer, wall_X, wall_Y);

            SCORE = (SDL_GetTicks() - startTime) / 1000;
            renderScore(gRenderer, SCORE, NUM_COVID_SCORES);

            if(gameOver == true)
            {
                heart--;
                SDL_Delay(1000);
            }

            //Handle heart for character
            if(checkCollisionRect(chr.mColliders, HeartRect) == true)
            {
                Mix_Chunk* SoundHeart = Mix_LoadWAV("sound/winter.wav");
                Mix_PlayChannel(-1, SoundHeart, 0);
                SoundHeart = NULL;
                heart++;
                HeartRect = {-100, -100, 0, 0};
                if(heart > 3) heart = 3;
            }

            SDL_Rect sourceRectHeart = {0, 0, 30, 30};// cat ra mot phan cua anh goc

            for(int i = 1; i <= heart; i++)
            {
                SDL_Rect desRect = {10 + 30*(i - 1), 80, 30, 30};// hien thi anh vua cat ra man hinh voi kich thuoc cua desRect
                SDL_RenderCopy(gRenderer, heartTexture, &sourceRectHeart, &desRect);
            }

            if((SDL_GetTicks() - HeartTime) / 1000 >= 3)
            {
                HeartRect = {rand() % (SCREEN_WIDTH - 60) + 10, rand() % 3000 + 50, 30, 30};
                HeartTime = SDL_GetTicks();
            }

            SDL_RenderCopyEx(gRenderer, heartTexture, &sourceRectHeart, &HeartRect,
                             pow(-1, SCORE % 2) * (SDL_GetTicks() - startTime)/10, NULL, SDL_FLIP_NONE);

            //Update screen
            SDL_RenderPresent( gRenderer );

            //Game Over
            if(heart == 0)
            {
                SDL_Delay(1000);
                Mix_FreeMusic( gMusic );
                gMusic = NULL;

                Mix_Chunk* EndGame = Mix_LoadWAV("sound/End-of-game.wav");
                if ( EndGame == NULL ) printf ( "Error loaded End Game sound!\n" );
                Mix_PlayChannel(-1, EndGame, 0);
                EndGame = NULL;

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                GameOver(gRenderer, SCORE, NUM_COVID_SCORES);

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
