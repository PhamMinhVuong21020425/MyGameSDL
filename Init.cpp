#include "Init.h"

//Starts up SDL and creates window
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "The Virus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 255, 0, 0, 0 );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) //Kiem tra xem so bit cua anh co phai PNG khong
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

                //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

            }
        }
    }

    return success;
}

void waitUntilEnterPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_WaitEvent(&e) != 0 && ( (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer, SDL_Texture* gTexture)
{


    //Free loaded image
    SDL_DestroyTexture( gTexture );
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture( std::string path, SDL_Renderer* gRenderer )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

void welcome(SDL_Renderer* gRenderer)
{
    SDL_Texture *gBkgroundTexture = loadTexture("image/Bkground.png",gRenderer);
    SDL_RenderCopy(gRenderer,gBkgroundTexture,NULL,&FullScreen);

    int w, h;
    SDL_Rect desRect;
    SDL_Color fg = { 50, 205, 50};
    TTF_Font* font = TTF_OpenFont("SuperMario256.ttf", 62);

    SDL_Surface *surface = TTF_RenderText_Solid(font, "The Virus", fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    desRect.x = 30;
    desRect.y = 20;
    desRect.w = w;
    desRect.h = h;
    SDL_RenderCopy(gRenderer, texture, NULL, &desRect);

    fg = {0,0,0};
    font = TTF_OpenFont("lazy.ttf", 28);
    surface = TTF_RenderText_Solid(font, "PRESS ENTER TO START", fg);
    texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    desRect.x = 65;
    desRect.y = 80;
    desRect.w = w;
    desRect.h = h;
    SDL_RenderCopy(gRenderer, texture, NULL, &desRect);

    SDL_RenderPresent(gRenderer);

    waitUntilEnterPressed();
}

void GameOver(SDL_Renderer* gRenderer)
{
    SDL_Texture *GameOverTexture = loadTexture("image/gameOver.png", gRenderer);
    SDL_RenderCopy(gRenderer, GameOverTexture, NULL, &FullScreen);
    SDL_RenderPresent(gRenderer);
    waitUntilEnterPressed();
    SDL_DestroyTexture(GameOverTexture);
}
