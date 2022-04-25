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

                IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) //Kiem tra xem so bit cua anh co phai PNG khong
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() != 0 )
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
        if ( SDL_WaitEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
                return;
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                return;
        }
        SDL_Delay(100);
    }
}

bool checkInside(SDL_Rect &a, const int &x, const int &y)
{
    if(x < a.x || y < a.y || x > a.x + a.w || y > a.y + a.h) return false;
    return true;
}

void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer)
{
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

SDL_Texture* loadTexture( const std::string &path, SDL_Renderer* &gRenderer )
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
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

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

SDL_Rect renderTextTexture(SDL_Renderer* &gRenderer, const std::string &fontName,
                           const std::string &content, const int &fontSize,
                           const SDL_Color &fcolor, const int &x, const int &y)
{
    TTF_Font* font = TTF_OpenFont(fontName.c_str(), fontSize);

    SDL_Surface *surface = TTF_RenderText_Solid(font, content.c_str(), fcolor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);
    surface = NULL;

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect desRect = {x, y, w, h};
    SDL_RenderCopy(gRenderer, texture, NULL, &desRect);

    TTF_CloseFont(font);
    font = NULL;
    SDL_DestroyTexture(texture);
    texture = NULL;

    return desRect;
}

void setBackgroundTexture( const std::string &path, SDL_Renderer* &gRenderer )
{
    SDL_Rect FullScreen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Texture *texture = loadTexture(path.c_str(), gRenderer);
    SDL_RenderCopy(gRenderer, texture, NULL, &FullScreen);
    SDL_DestroyTexture(texture);
    texture = NULL;
}

bool welcome(SDL_Renderer* &gRenderer)
{
    setBackgroundTexture("image/Bkground.png", gRenderer);

    SDL_Color fcolor = { 50, 200, 50 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", "The Virus", 62, fcolor, 30, 20 );

    fcolor = {0,0,0};
    renderTextTexture(gRenderer, "lazy.ttf", "PRESS ENTER TO START", 28, fcolor, 65, 80 );

    fcolor = {0, 190, 0};
    SDL_Rect StartRect = renderTextTexture(gRenderer, "SuperMario256.ttf", "PLAY", 40, fcolor, SCREEN_WIDTH - 150, 25 );
    SDL_RenderPresent(gRenderer);

    fcolor = {250, 0, 0};
    SDL_Rect ExitRect = renderTextTexture(gRenderer, "SuperMario256.ttf", "EXIT", 40, fcolor, SCREEN_WIDTH - 150, 70 );
    SDL_RenderPresent(gRenderer);

    SDL_Event e;
    while(true)
    {
        if ( SDL_WaitEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
                return 0;
            else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                return 1;
            if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if(checkInside(StartRect, x, y) == true)
                {
                    switch(e.type)
                    {
                    case SDL_MOUSEBUTTONDOWN:
                        return 1;
                    default:
                        break;
                    }
                }
                if(checkInside(ExitRect, x, y) == true)
                {
                    switch(e.type)
                    {
                    case SDL_MOUSEBUTTONDOWN:
                        return 0;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void renderScore(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES)
{
    std::stringstream ss;
    ss.str("");
    ss << "Score: " << score;

    SDL_Color fcolor = { 90, 0, 255 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 28, fcolor, 10, 50);

    fcolor = { 10, 160, 50 };
    ss.str("");
    ss << "Covid: " << NUM_COVID_SCORES;

    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 28, fcolor, SCREEN_WIDTH - 170, 50);
}

void GameOver(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES)
{
    setBackgroundTexture("image/gameOver.png", gRenderer);

    std::stringstream ss;
    ss.str("");
    ss << "Total score: " << score + NUM_COVID_SCORES * 5;

    SDL_Color fcolor = { 150, 0, 255 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 46, fcolor, 420, 80);

    SDL_RenderPresent(gRenderer);
    waitUntilEnterPressed();
}
