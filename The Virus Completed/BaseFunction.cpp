#include "BaseFunction.h"

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

bool checkCollisionRect(SDL_Rect &a, SDL_Rect &b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )return false;

    if( topA >= bottomB )return false;

    if( rightA <= leftB )return false;

    if( leftA >= rightB )return false;

    //If none of the sides from A are outside B
    return true;
}

bool checkInside(SDL_Rect &a, const int &x, const int &y)
{
    if(x < a.x || y < a.y || x > a.x + a.w || y > a.y + a.h) return false;
    return true;
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
    while( true )
    {
        SDL_RenderClear( gRenderer );

        setBackgroundTexture("image/Bkground.png", gRenderer);

        SDL_Color fcolor = { 50, 200, 50 };
        renderTextTexture(gRenderer, "SuperMario256.ttf", "The Virus", 62, fcolor, 30, 20 );

        fcolor = {0,0,0};
        renderTextTexture(gRenderer, "lazy.ttf", "PRESS ENTER TO START", 28, fcolor, 65, 80 );

        fcolor = {0, 190, 0};
        SDL_Rect StartRect = renderTextTexture(gRenderer, "SuperMario256.ttf", "PLAY", 40, fcolor, SCREEN_WIDTH - 150, 25 );

        fcolor = {250, 0, 0};
        SDL_Rect ExitRect = renderTextTexture(gRenderer, "SuperMario256.ttf", "EXIT", 40, fcolor, SCREEN_WIDTH - 150, 70 );

        SDL_Event e;

        if ( SDL_WaitEvent( &e ) != 0 )
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
                    case SDL_MOUSEMOTION:
                        fcolor = {0, 190, 0};
                        renderTextTexture(gRenderer, "arial.ttf", ">", 35, fcolor, SCREEN_WIDTH - 180, 20 );
                        break;
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
                    case SDL_MOUSEMOTION:
                        fcolor = {250, 0, 0};
                        renderTextTexture(gRenderer, "arial.ttf", ">", 35, fcolor, SCREEN_WIDTH - 180, 65 );
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        return 0;
                    default:
                        break;
                    }
                }
            }
        }
        SDL_RenderPresent(gRenderer);
    }
}

void renderScore(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES)
{
    std::stringstream ss;
    ss.str("");
    ss << "Score: " << score;

    SDL_Color fcolor = { 90, 0, 255 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 28, fcolor, 10, 50);

    ss.str("");
    ss << "Covid: " << NUM_COVID_SCORES;

    fcolor = { 10, 160, 50 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 28, fcolor, SCREEN_WIDTH - 170, 50);

    std::ifstream fi("HighScore.txt");
    Uint32 highScore;
    fi >> highScore;
    ss.str("");
    ss << "Record: " << highScore;

    fcolor = { 255, 0, 0 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 28, fcolor, SCREEN_WIDTH - 195, 80);
}

void GameOver(SDL_Renderer* &gRenderer, Uint32 &score, const int &NUM_COVID_SCORES)
{
    setBackgroundTexture("image/gameOver.png", gRenderer);

    std::stringstream ss;
    ss.str("");
    std::ifstream fi("HighScore.txt");
    Uint32 totalScore = score + NUM_COVID_SCORES * 5;
    Uint32 highScore;
    fi >> highScore;
    if(totalScore > highScore)
    {
        highScore = totalScore;
        std::ofstream fo("HighScore.txt");
        fo << highScore;
        ss << " High score: " << totalScore;

        Mix_Chunk *HighSound = Mix_LoadWAV("sound/HighScore.wav");
        if(HighSound == NULL) printf("Error loaded High Score sound!\n");
        Mix_PlayChannel(-1, HighSound, 0);
        HighSound = NULL;
    }
    else
    {
        ss << "Total score: " << totalScore;

        Mix_Chunk* EndGame = Mix_LoadWAV("sound/End-of-game.wav");
        if(EndGame == NULL) printf("Error loaded End Game sound!\n");
        Mix_PlayChannel(-1, EndGame, 0);
        EndGame = NULL;
    }

    SDL_Color fcolor = { 150, 0, 255 };
    renderTextTexture(gRenderer, "SuperMario256.ttf", ss.str().c_str(), 46, fcolor, 420, 80);

    SDL_RenderPresent(gRenderer);
    SDL_Delay(3000);
}
